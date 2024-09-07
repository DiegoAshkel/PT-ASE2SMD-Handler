#include "KeyReader.h"
#include <exception>
#include <iostream>

KeyReader::KeyReader(const std::string &fileName)
	: m_Offset(0), m_StartOffset(0), m_Buffer()
{
	Close();

	// open the file:
	m_file.open(fileName, std::ios::binary);

	// check if it's open
	if (!m_file.is_open())
	{
		std::string message = "Can't open file: ";
		message += fileName;

		throw std::exception(message.c_str());
	}

	// Stop eating new lines in binary mode!!!
	m_file.unsetf(std::ios::skipws);

	// calculate file size
	m_file.seekg(0, std::ios::end);
	size_t length = m_file.tellg();
	m_file.seekg(0, std::ios::beg);

	// reserve enough mem for our file buffer
	m_Buffer.reserve(length + 1);

	// store file to our buffer
	m_Buffer.insert(m_Buffer.begin(), std::istream_iterator<char>(m_file), std::istream_iterator<char>());

	Close();
}

KeyReader::~KeyReader()
{
	Close();
}

bool KeyReader::IsEOF() const
{
	return (m_Offset + 1) >= m_Buffer.size();
}

size_t KeyReader::GetSize() const
{
	return m_Buffer.size();
}

char *KeyReader::GetKey()
{
	char *pBuffer = GetWords();

	if (pBuffer)
	{
		if (pBuffer[0] == '*')
			return pBuffer;

		delete[] pBuffer;
		pBuffer = nullptr;
	}

	return nullptr;
}

int KeyReader::GetInteger()
{
	char *pBuffer = GetWords();

	if (pBuffer)
	{
		int value = std::atoi(pBuffer);

		delete[] pBuffer;
		pBuffer = nullptr;

		return value;
	}

	return 0;
}

float KeyReader::GetFloat()
{
	char *pBuffer = GetWords();

	if (pBuffer)
	{
		int value = std::atof(pBuffer);

		delete[] pBuffer;
		pBuffer = nullptr;

		return value;
	}

	return 0.000f;
}

std::string KeyReader::GetString()
{
	std::string str = "";

	// get "word"
	char *pBuffer = GetWords();
	if (!pBuffer)
	{
		return str;
	}

	delete[] pBuffer;
	pBuffer = nullptr;

	char delim = 0;

	// get it's string delimiter
	if (m_Buffer[m_StartOffset] == '\"' || // ""
		m_Buffer[m_StartOffset] == '\'')   // ''
	{
		delim = m_Buffer[m_StartOffset];
		m_Offset = ++m_StartOffset;
	}

	// check if it has a string delimiter
	if (!delim)
	{
		return str;
	}

	// append char till the end of the string" or '
	while (!IsEOF() &&
		   m_Buffer[m_Offset] != delim)
	{
		if (m_Buffer[m_Offset] == '\r' ||
			m_Buffer[m_Offset] == '\n' ||
			m_Buffer[m_Offset] == '\0')
			break;

		str += m_Buffer[m_Offset];
		m_Offset++;
	}

	return str;
}

char *KeyReader::GetWords()
{
	size_t start = 0, end = 0;

	// Increase offset till it finds the first char that is no tab or space
	while (!IsEOF() &&
		   (m_Buffer[m_Offset] == '\t' || // TAB
			m_Buffer[m_Offset] == ' '))	  // SPACE
	{
		m_Offset++;
	}

	// sets starting offset of "word"
	start = m_Offset;
	m_StartOffset = m_Offset;

	// Increase offset while it didn't find the end of "word" (no tab, space, cr, lf, or zero)
	while (!IsEOF() &&
		   (m_Buffer[m_Offset] != '\t' && // TAB
			m_Buffer[m_Offset] != ' '))	  // SPACE
	{
		if (m_Buffer[m_Offset] == '\r' ||
			m_Buffer[m_Offset] == '\n' ||
			m_Buffer[m_Offset] == '\0')
			break;

		m_Offset++;
	}

	// sets ending offset of "word"
	end = m_Offset++;

	// get "word" length and return null if it's zero or less
	size_t length = end - start;
	if (length <= 0)
		return nullptr;

	// alloc buffer for "word"
	char *pBuffer = new char[length + 1];

	// copy "word" for our buffer
	std::copy(&m_Buffer[start], &m_Buffer[end], pBuffer);

	// puts a zero at it's end
	pBuffer[length] = 0;

	return pBuffer;
}

void KeyReader::Close()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
}
