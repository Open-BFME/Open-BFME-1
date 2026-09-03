// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x007409A0: copy-assignment of a 0x14-byte record. On this != other,
// assign the AsciiString at +0xC from a by-value getName(), then copy the
// 12-byte POD at +0 and the trailing dword at +0x10.

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase &other);

private:
	StringBase(const StringBase &other);
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct Pod3
{
	unsigned a;
	unsigned b;
	unsigned c;
};

class Rva007409A0
{
public:
	Rva007409A0 &operator=(const Rva007409A0 &other);
	AsciiString getName() const;

private:
	Pod3 m_pod;
	AsciiString m_name;
	unsigned m_10;
};

// ??4Rva007409A0@@QAEAAV0@ABV0@@Z
Rva007409A0 &Rva007409A0::operator=(const Rva007409A0 &other)
{
	if (this != &other)
	{
		m_name = other.getName();
		m_pod = other.m_pod;
		m_10 = other.m_10;
	}
	return *this;
}
