#ifndef KEY_READER_H
#define KEY_READER_H

#include <string>
#include <fstream>
#include <vector>

/// Helper class to read and load ASE files
/// Open file in binary mode and store into a vector buffer,
/// use it's methods to advance through the buffer and get it's values
class KeyReader
{
public:
	/// Initialize KeyReader object, and store file data into buffer.
	KeyReader(const std::string &fileName);
	KeyReader(const std::vector<char> &buffer);
	virtual ~KeyReader();

	/// Is end of file/buffer.
	bool IsEOF() const;

	/// Get size of buffer.
	size_t GetSize() const;

	/// Get key string starting with '*'.
	char *GetKey();

	/// Get int value.
	int GetInteger();

	/// Get float value.
	float GetFloat();

	/// Get string value(wrapped between '' or "").
	std::string GetString();

	KeyReader *GetBlock();

private:
	/// Advance through the buffer and find for "words".
	char *GetWords();

private:
	std::string m_FileName;
	std::ifstream m_File;
	size_t m_Offset;
	size_t m_StartOffset;
	std::vector<char> m_Buffer;
};

#endif
