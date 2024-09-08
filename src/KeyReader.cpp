#include "KeyReader.h"
#include <exception>
#include <iostream>

KeyReader::KeyReader(const std::string &fileName)
	: m_Offset(0ull), m_StartOffset(0ull), m_Buffer()
{
	// store filename
	m_FileName = fileName;

	// open the file:
	m_File.open(fileName, std::ios::binary);

	// check if it's open
	if (!m_File.is_open())
	{
		std::string message = "Can't open file: ";
		message += fileName;

		std::cerr << message << std::endl;

		std::exception ex(message.c_str());

		throw ex;
	}

	// Stop eating new lines in binary mode!!!
	m_File.unsetf(std::ios::skipws);

	// calculate file size
	m_File.seekg(0, std::ios::end);
	size_t length = m_File.tellg();
	m_File.seekg(0, std::ios::beg);

	// reserve enough mem for our file buffer
	m_Buffer.reserve(length + 1);

	// store file to our buffer
	m_Buffer.insert(m_Buffer.begin(), std::istream_iterator<char>(m_File), std::istream_iterator<char>());

	m_File.close();
}

KeyReader::KeyReader(const std::vector<char> &buffer)
	: m_Offset(0ull), m_StartOffset(0ull), m_Buffer(buffer)
{
}

KeyReader::~KeyReader()
{
	if (m_File.is_open())
	{
		m_File.close();
	}

	m_FileName.clear();
	m_Offset = 0ull;
	m_StartOffset = 0ull;
	m_Buffer.clear();
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

	std::vector<char> vBuffer = m_Buffer;

	// append char till the end of the string" or '
	while (!IsEOF() &&
		   vBuffer[m_Offset] != delim)
	{
		if (vBuffer[m_Offset] == '\r' ||
			vBuffer[m_Offset] == '\n' ||
			vBuffer[m_Offset] == '\0')
			break;

		str += vBuffer[m_Offset];
		m_Offset++;
	}

	return str;
}

KeyReader *KeyReader::GetBlock()
{
	bool isBlock = false;

	char *pBuffer = GetWords();
	if (pBuffer && pBuffer[0] == '{')
	{
		isBlock = true;

		delete[] pBuffer;
		pBuffer = nullptr;
	}

	if (!isBlock)
	{
		return nullptr;
	}

	size_t start = m_Offset;
	int blockLevel = 0;

	while (!IsEOF())
	{
		if (m_Buffer[m_Offset] == '{')
		{
			blockLevel++;
		}
		else if (m_Buffer[m_Offset] == '}')
		{
			if (blockLevel == 0)
				break;

			blockLevel--;
		}

		m_Offset++;
	}

	size_t end = m_Offset;

	size_t length = end - start;
	if (length <= 0)
		return nullptr;

	std::vector<char> vBuffer;
	vBuffer.reserve(length);
	vBuffer.insert(vBuffer.begin(), m_Buffer.begin() + start, m_Buffer.begin() + end);

	std::cout << "vBuffer: " << std::string(vBuffer.data()) << std::endl;

	KeyReader *reader = new KeyReader(vBuffer);

	return reader;
}

char *KeyReader::GetWords()
{
	std::vector<char> vBuffer = m_Buffer;

	size_t start = 0,
		   end = 0;

	// Increase offset till it finds the first char that is no tab or space
	while (!IsEOF() &&
		   (vBuffer[m_Offset] == '\t' || // TAB
			vBuffer[m_Offset] == ' '))	 // SPACE
	{
		m_Offset++;
	}

	// sets starting offset of "word"
	start = m_Offset;
	m_StartOffset = m_Offset;

	// Increase offset while it didn't find the end of "word" (no tab, space, cr, lf, or zero)
	while (!IsEOF() &&
		   (vBuffer[m_Offset] != '\t' && // TAB
			vBuffer[m_Offset] != ' '))	 // SPACE
	{
		if (vBuffer[m_Offset] == '\r' ||
			vBuffer[m_Offset] == '\n' ||
			vBuffer[m_Offset] == '\0')
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
	std::copy(&vBuffer[start], &vBuffer[end], pBuffer);

	// puts a zero at it's end
	pBuffer[length] = 0;

	return pBuffer;
}
