#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace Shared
{
	// static_assert(std::string::npos == ~0i64);

	/// Simple binary writer.
	class BinaryWriter
	{
	public:
		/// Constructs with defined buffer size (Default = 64).
		BinaryWriter(size_t ExpectedSize = 64);

		BinaryWriter &operator<<(bool Var);
		BinaryWriter &operator<<(char Var);
		BinaryWriter &operator<<(unsigned char Var);
		BinaryWriter &operator<<(short Var);
		BinaryWriter &operator<<(unsigned short Var);
		BinaryWriter &operator<<(int Var);
		BinaryWriter &operator<<(unsigned int Var);
		BinaryWriter &operator<<(long Var);
		BinaryWriter &operator<<(unsigned long Var);
		BinaryWriter &operator<<(long long Var);
		BinaryWriter &operator<<(unsigned long long Var);
		BinaryWriter &operator<<(float Var);
		BinaryWriter &operator<<(double Var);
		BinaryWriter &operator<<(const char *Var);
		BinaryWriter &operator<<(const std::string &Var);
		BinaryWriter &operator<<(const std::pair<const void *, size_t> &Var);

		void InsertAt(size_t Where, bool Var);
		void InsertAt(size_t Where, char Var);
		void InsertAt(size_t Where, unsigned char Var);
		void InsertAt(size_t Where, short Var);
		void InsertAt(size_t Where, unsigned short Var);
		void InsertAt(size_t Where, int Var);
		void InsertAt(size_t Where, unsigned int Var);
		void InsertAt(size_t Where, long Var);
		void InsertAt(size_t Where, unsigned long Var);
		void InsertAt(size_t Where, long long Var);
		void InsertAt(size_t Where, unsigned long long Var);
		void InsertAt(size_t Where, float Var);
		void InsertAt(size_t Where, double Var);
		void InsertAt(size_t Where, const char *Var);
		void InsertAt(size_t Where, const std::string &Var);
		void InsertAt(size_t Where, const std::pair<const void *, size_t> &Var);

		/// Get the internal memory buffer.
		const unsigned char *Get() const;

		/// Get the size of the buffer.
		size_t GetSize() const;

		/// Get the current offset of the buffer.
		size_t GetOffset() const;

		/// Reserve more bytes to the buffer
		void Reserve(size_t Size);

	private:
		void Write(size_t Where, const void *Buffer, size_t Size);

	private:
		std::vector<unsigned char> m_Buffer;
		size_t m_Offset;
	};
}
