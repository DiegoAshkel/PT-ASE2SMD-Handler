#include "KeyReader.h"

KeyReader::KeyReader(const std::string &fileName)
	: m_Offset(0)
{
	Close();

	m_file.open(fileName);

	m_file.seekg(0, std::ios::end);
	size_t length = m_file.tellg();

	m_file.seekg(0, std::ios::beg);

	m_Buffer.reserve(length + 1);

	m_file >> m_Buffer.data();
}

KeyReader::~KeyReader()
{
	Close();
}

char *KeyReader::GetKey()
{
	char *pBuffer = GetWords();

	if (pBuffer[0] == '*')
		return pBuffer;

	return nullptr;
}

int KeyReader::GetInteger()
{
	char *pBuffer = GetWords();

	return std::atoi(pBuffer);
}

float KeyReader::GetFloat()
{
	char *pBuffer = GetWords();

	return std::atof(pBuffer);
}

std::string KeyReader::GetString()
{
	// " or '
	while (m_Buffer[m_Offset] != 34)
	{
		m_Offset++;
	}

	char *pBuffer = &m_Buffer[++m_Offset];

	// " or '
	while (m_Buffer[m_Offset] != 34)
	{
		if (m_Buffer[m_Offset] == '\r' ||
			m_Buffer[m_Offset] == '\n' ||
			m_Buffer[m_Offset] == 0)
			break;

		m_Offset++;
	}

	pBuffer[++m_Offset] = 0;

	return std::string(pBuffer);
}

char *KeyReader::GetWords()
{
	// SPACE or TAB
	while (m_Buffer[m_Offset] == 9 ||
		   m_Buffer[m_Offset] == 32)
	{
		m_Offset++;
	}

	char *pBuffer = &m_Buffer[m_Offset];

	// SPACE or TAB
	while (m_Buffer[m_Offset] != 9 ||
		   m_Buffer[m_Offset] != 32)
	{
		if (m_Buffer[m_Offset] == '\r' ||
			m_Buffer[m_Offset] == '\n')
			break;

		m_Offset++;
	}

	pBuffer[++m_Offset] = 0;

	return pBuffer;
}

void KeyReader::Close()
{
	if (m_file.is_open())
	{
		m_file.close();
	}
}
