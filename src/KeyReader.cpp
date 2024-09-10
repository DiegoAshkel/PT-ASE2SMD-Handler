#include "KeyReader.h"
#include <stdexcept>
#include <iostream>

KeyReader::KeyReader(const std::string &fileName)
	: m_Offset(0ull), m_StartOffset(0ull), m_BufferSize(0ull), m_lpBuffer(nullptr)
{
	m_File.open(fileName);
	if (!m_File.is_open())
	{
		std::string message = "Can't open file: ";
		message += fileName;

		std::cerr << message << std::endl;

		throw std::exception(message.c_str());
	}
}

KeyReader::KeyReader(const char *lpData, size_t size)
	: m_Offset(0ull), m_StartOffset(0ull), m_BufferSize(size + 1)
{
	m_lpBuffer = new char[m_BufferSize];

	std::copy_n(lpData, size, m_lpBuffer);

	// Ensure the buffer is null terminated.
	m_lpBuffer[size] = 0;
}

KeyReader::~KeyReader()
{
	m_Offset = 0ull;
	m_StartOffset = 0ull;
	m_BufferSize = 0ull;

	Close();
	Release();
}

bool KeyReader::IsEOF() const
{
	// If KeyReader has a file, return file EOF.
	if (m_File.is_open())
	{
		return m_File.eof();
	}

	// Else, return end of buffer.
	return (m_Offset >= m_BufferSize);
}

size_t KeyReader::GetSize() const
{
	return m_BufferSize;
}

char *KeyReader::Get() const
{
	return m_lpBuffer;
}

std::string KeyReader::ReadLine()
{
	// Release buffer
	Release();

	// Read line from file
	std::string str;
	str.reserve(256);
	std::getline(m_File, str);

	// Allocate new buffer
	size_t length = str.length();
	m_BufferSize = length + 1;
	m_lpBuffer = new char[m_BufferSize];

	// Copy line to buffer
	std::copy(str.begin(), str.begin() + length, m_lpBuffer);
	m_lpBuffer[length] = 0;
	m_Offset = 0ull;

	return str;
}

std::string KeyReader::ReadBlock()
{
	bool isBlock = false;

	// get opening brace.
	char *pBuffer = GetWords();
	if (pBuffer && pBuffer[0] == '{')
	{
		isBlock = true;

		delete[] pBuffer;
		pBuffer = nullptr;
	}

	std::string str;
	str.reserve(1024);

	// If there is no opening brace, return empty string.
	if (!isBlock)
	{
		return str;
	}

	int blockLevel = 0;

	// advance through the buffer.
	while (!IsEOF())
	{
		// Read new line if needed
		if (m_Offset >= m_BufferSize)
		{
			ReadLine();

			str += "\r\n";
		}

		// if there is another opening brace, it's entering a new block(inner block).
		if (m_lpBuffer[m_Offset] == '{')
		{
			blockLevel++;
		}
		else if (m_lpBuffer[m_Offset] == '}')
		{
			// if the current block level is zero, it's the end of the block.
			if (blockLevel == 0)
				break;

			// if not, just leave the inner block.
			blockLevel--;
		}

		str += m_lpBuffer[m_Offset++];
	}

	return str;
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

std::string KeyReader::GetWord()
{
	std::string str;

	char *pBuffer = GetWords();
	if (pBuffer)
	{
		str.append(pBuffer);

		delete[] pBuffer;
		pBuffer = nullptr;
	}

	return str;
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
		float value = std::atof(pBuffer);

		delete[] pBuffer;
		pBuffer = nullptr;

		return value;
	}

	return 0.000f;
}

std::string KeyReader::GetString()
{
	std::string str;

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
	if (m_lpBuffer[m_StartOffset] == '\"' || // ""
		m_lpBuffer[m_StartOffset] == '\'')	 // ''
	{
		delim = m_lpBuffer[m_StartOffset];
		m_Offset = ++m_StartOffset;
	}

	// check if it has a string delimiter
	if (!delim)
	{
		return str;
	}

	// append char till the end of the string " or '
	while ((m_Offset < m_BufferSize) &&
		   m_lpBuffer[m_Offset] != delim)
	{
		if (m_lpBuffer[m_Offset] == '\r' ||
			m_lpBuffer[m_Offset] == '\n' ||
			m_lpBuffer[m_Offset] == '\0')
			break;

		str += m_lpBuffer[m_Offset++];
	}

	return str;
}

KeyReader *KeyReader::GetBlock()
{
	std::string str = ReadBlock();
	size_t length = str.length();
	if (length <= 0)
		return nullptr;

	return new KeyReader(str.c_str(), length);
}

void KeyReader::Release()
{
	if (m_lpBuffer)
	{
		delete[] m_lpBuffer;
		m_lpBuffer = nullptr;
	}
}

char *KeyReader::GetWords()
{
	if (m_File.is_open())
	{
		if (!m_lpBuffer ||
			(m_Offset >= m_BufferSize))
		{
			ReadLine();
		}
	}

	// Increase offset till it finds the first char that is no tab or space
	while ((m_Offset < m_BufferSize) &&
		   (m_lpBuffer[m_Offset] == '\t' ||
			m_lpBuffer[m_Offset] == ' '))
	{
		m_Offset++;
	}

	// sets starting offset of "word"
	m_StartOffset = m_Offset;

	std::string str;
	str.reserve(64);

	// Increase offset while it didn't find the end of "word" (no tab, space, cr, lf, or zero)
	while ((m_Offset < m_BufferSize) &&
		   (m_lpBuffer[m_Offset] != '\t' && // TAB
			m_lpBuffer[m_Offset] != ' '))	// SPACE
	{
		if (m_lpBuffer[m_Offset] == '\r' ||
			m_lpBuffer[m_Offset] == '\n' ||
			m_lpBuffer[m_Offset] == '\0')
			break;

		str += m_lpBuffer[m_Offset++];
	}

	// sets ending offset of "word"
	m_Offset++;

	// get "word" length and return null if it's zero or less
	size_t length = str.length();
	if (length <= 0)
		return nullptr;

	char *lpBuffer = new char[length + 1];

	std::copy(str.begin(), str.begin() + length, lpBuffer);
	lpBuffer[length] = 0;

	str.clear();

	return lpBuffer;
}

void KeyReader::Close()
{
	if (m_File.is_open())
	{
		m_File.close();
	}
}
