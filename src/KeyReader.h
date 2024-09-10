#pragma once

#include <string>
#include <fstream>
#include <vector>

/// Helper class to read and load ASE files.
/// Use it's methods to advance through the file/buffer and get it's values.
class KeyReader
{
public:
	/// Initialize KeyReader object from a file.
	KeyReader(const std::string &fileName);

	/// Initialize KeyReader object from a char buffer.
	KeyReader(const char *lpData, size_t size);

	/// Destructor
	virtual ~KeyReader();

	/// Is end of file/buffer.
	bool IsEOF() const;

	/// Get size of buffer.
	size_t GetSize() const;

	/// Get buffer.
	char *Get() const;

	/// Read line from file
	std::string ReadLine();

	/// Read block from file
	std::string ReadBlock();

	/// Get key string starting with '*'.
	char *GetKey();

	/// Advance through the buffer and search for "words".
	std::string GetWord();

	/// Get int value.
	int GetInteger();

	/// Get float value.
	float GetFloat();

	/// Get string value(wrapped between '' or "").
	std::string GetString();

	/// Get a new KeyReader, containing the data of a inner block(wrapped between {})
	KeyReader *GetBlock();

private:
	/// Advance through the buffer and search for "words".
	char *GetWords();

	/// Close file.
	void Close();

	/// Release buffer.
	void Release();

private:
	std::ifstream m_File;
	size_t m_Offset;
	size_t m_StartOffset;

	size_t m_BufferSize;
	char *m_lpBuffer;
};
