#include "BinaryWriter.h"

namespace Shared
{
	BinaryWriter::BinaryWriter(size_t ExpectedSize)
		: m_Offset(0)
	{
		m_Buffer.reserve(ExpectedSize);
	}

	BinaryWriter &BinaryWriter::operator<<(bool Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(char Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(unsigned char Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(short Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(unsigned short Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(int Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(unsigned int Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(long Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(unsigned long Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(long long Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(unsigned long long Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(float Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(double Var)
	{
		Write(m_Buffer.size(), &Var, sizeof(Var));
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(const char *Var)
	{
		Write(m_Buffer.size(), Var, strlen(Var) + 1); // Include null terminator
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(const std::string &Var)
	{
		Write(m_Buffer.size(), Var.c_str(), Var.size() + 1); // Include null terminator
		return *this;
	}

	BinaryWriter &BinaryWriter::operator<<(const std::pair<const void *, size_t> &Var)
	{
		Write(m_Buffer.size(), Var.first, Var.second);
		return *this;
	}

	void BinaryWriter::InsertAt(size_t Where, bool Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, char Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, unsigned char Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, short Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, unsigned short Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, int Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, unsigned int Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, long Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, unsigned long Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, long long Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, unsigned long long Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, float Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, double Var)
	{
		Write(Where, &Var, sizeof(Var));
	}

	void BinaryWriter::InsertAt(size_t Where, const char *Var)
	{
		Write(Where, Var, strlen(Var) + 1);
	}

	void BinaryWriter::InsertAt(size_t Where, const std::string &Var)
	{
		Write(Where, Var.c_str(), Var.size() + 1);
	}

	void BinaryWriter::InsertAt(size_t Where, const std::pair<const void *, size_t> &Var)
	{
		Write(Where, Var.first, Var.second);
	}

	/// Get the internal memory buffer.
	const unsigned char *BinaryWriter::Get() const
	{
		return m_Buffer.data();
	}

	/// Get the size of the buffer.
	size_t BinaryWriter::GetSize() const
	{
		return m_Buffer.size();
	}

	size_t BinaryWriter::GetOffset() const
	{
		return m_Offset;
	}

	void BinaryWriter::Reserve(size_t Size)
	{
		m_Buffer.resize(GetSize() + Size);
	}

	void BinaryWriter::Write(size_t Where, const void *Buffer, size_t Size)
	{
		if (Where + Size > m_Buffer.size())
		{
			m_Buffer.resize(Where + Size);
		}

		std::memcpy(&m_Buffer[Where], Buffer, Size);

		m_Offset = Where + Size;
	}
}
