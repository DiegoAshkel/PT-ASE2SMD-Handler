#ifndef KEY_READER_H
#define KEY_READER_H

#include <string>
#include <fstream>
#include <vector>

class KeyReader
{
public:
	KeyReader(const std::string &fileName);
	virtual ~KeyReader();

	bool IsEOF() const;
	size_t GetSize() const;

	char *GetKey();
	int GetInteger();
	float GetFloat();
	std::string GetString();

private:
	char *GetWords();

	void Close();

private:
	std::ifstream m_file;
	std::vector<char> m_Buffer;
	size_t m_Offset;
	size_t m_StartOffset;
};

#endif
