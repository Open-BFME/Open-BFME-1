// cl: /DNDEBUG /MD /EHs-c- /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x00743BF0 (180 bytes), a __thiscall taking one AsciiString.  It
// walks the singly linked named entries hanging off TheTacticalView+0x80 and,
// for the first whose name compares equal, clears the receiver's byte at
// +0x44 and hands the entry to the receiver's vtable slot 24 with 300 and
// zeroes.  No caller, vtable slot or declaration names the receiver or the
// method, so both keep the address.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

struct Rva00743BF0Entry
{
	Rva00743BF0Entry *m_next;
	AsciiString m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
	Rva00743BF0Entry *getRva00743BF0Entries() const { return m_entries80; }

private:
	unsigned char m_pad00[0x80];
	Rva00743BF0Entry *m_entries80;
};

extern View *TheTacticalView;

class Rva00743BF0Owner
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(Int first, Rva00743BF0Entry *entry, Int frames, Int fourth,
		Int fifth, Int sixth);

	void rva00743BF0(const AsciiString &name);

private:
	unsigned char m_pad04[0x44 - 0x04];
	Bool m_flag44;
};

// ?rva00743BF0@Rva00743BF0Owner@@QAEXABVAsciiString@@@Z
void Rva00743BF0Owner::rva00743BF0(const AsciiString &name)
{
	Rva00743BF0Entry *entry;
	for (entry = TheTacticalView->getRva00743BF0Entries(); entry != 0;
		entry = entry->m_next)
	{
		if (entry->m_name.compare(name) == 0)
			break;
	}

	if (entry != 0)
	{
		m_flag44 = false;
		v24(0, entry, 300, 0, 0, 0);
	}
}
