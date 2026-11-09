// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x007409A0: copy-assignment of a 0x14-byte record. On this != other,
// assign the AsciiString at +0xC from a by-value getName(), then copy the
// 12-byte POD at +0 and the trailing dword at +0x10.
//
// Retail 0x00740A40 (123 bytes, thiscall, ret 4) fills the same 0x14-byte
// record from a Waypoint: it calls Waypoint::getName through ILT 0x0001026C
// (body 0x000EE6D0), assigns the result to +0xC through StringBase<char>::set,
// then copies the waypoint location (+0xC Coord3D) to +0 and the dword at
// waypoint +4 to +0x10, returning this.

#include "string_base.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	AsciiString getName(void) const;					// ILT 0x0001026C -> 0x000EE6D0

	unsigned char m_unmodelled_000[0x04];
	unsigned m_id;							// +0x04
	unsigned char m_unmodelled_008[0x04];				// +0x08 name
	Coord3D m_location;									// +0x0C
};

class Rva007409A0
{
public:
	Rva007409A0 &operator=(const Rva007409A0 &other);
	Rva007409A0 *rva00740A40(const Waypoint *waypoint);

private:
	Coord3D m_pod;
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

// ?rva00740A40@Rva007409A0@@QAEPAV1@PBVWaypoint@@@Z
Rva007409A0 *Rva007409A0::rva00740A40(const Waypoint *waypoint)
{
	m_name = waypoint->getName();
	m_pod = waypoint->m_location;
	m_10 = waypoint->m_id;
	return this;
}
