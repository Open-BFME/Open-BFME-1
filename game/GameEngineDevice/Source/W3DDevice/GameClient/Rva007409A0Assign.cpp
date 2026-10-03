// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x007409A0: copy-assignment of a 0x14-byte record. On this != other,
// assign the AsciiString at +0xC from a by-value getName(), then copy the
// 12-byte POD at +0 and the trailing dword at +0x10.

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

private:
	Pod3 m_pod;
	AsciiString m_name;
	unsigned m_10;
};

void j_00022386(void);
typedef AsciiString (Rva007409A0::*Rva007409A0GetNameCall)(void) const;
union Rva007409A0GetNameThunk
{
	void (*jThunk)(void);
	Rva007409A0GetNameCall getName;
};

// ??4Rva007409A0@@QAEAAV0@ABV0@@Z
Rva007409A0 &Rva007409A0::operator=(const Rva007409A0 &other)
{
	if (this != &other)
	{
		Rva007409A0GetNameThunk getName;
		getName.jThunk = &j_00022386;
		m_name = (const_cast<Rva007409A0 &>(other).*getName.getName)();
		m_pod = other.m_pod;
		m_10 = other.m_10;
	}
	return *this;
}
