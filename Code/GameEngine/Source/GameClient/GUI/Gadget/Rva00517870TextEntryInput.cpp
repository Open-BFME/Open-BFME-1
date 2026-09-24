// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail calls the CRT iswalnum import, not wchar.h's inline iswctype wrapper.
#define _WCTYPE_INLINE_DEFINED
#include "unicode_string.h"

struct Rva00517870StringData
{
	int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
};

class GameWindow
{
public:
	void *winGetUserData();
};

struct Rva00517870EntryData
{
	char m_pad00[0x1c];
	unsigned short m_1c;
	unsigned short m_1e;
};

extern UnicodeString GadgetTextEntryGetText(GameWindow *window);
extern void j_00003df0();

class Rva00517870Owner
{
public:
	int rva00517870(unsigned int message, unsigned int data1,
		unsigned int data2);

private:
	char m_pad00[8];
	GameWindow *m_entry;
};

int Rva00517870Owner::rva00517870(unsigned int message, unsigned int data1,
	unsigned int data2)
{
	if (message == 0x19)
	{
		unsigned short ch = (unsigned short)data1;
		if (ch == ',' || ch == ':' || ch == ';')
			return 1;
		Rva00517870EntryData *entry =
			(Rva00517870EntryData *)m_entry->winGetUserData();
		if (entry->m_1e == entry->m_1c)
		{
			GameWindow *window = m_entry;
			UnicodeString text = GadgetTextEntryGetText(window);
			Rva00517870StringData *str =
				*(Rva00517870StringData **)&text;
			int length = str ? (int)str->m_length : 0;
			if (length >= 12 && iswalnum((unsigned short)data1))
				return 1;
		}
	}
	typedef int (Rva00517870Owner::*Fallback)(
		unsigned int, unsigned int, unsigned int);
	union { void (*raw)(); Fallback member; } route;
	route.raw = ::j_00003df0;
	return (this->*route.member)(message, data1, data2);
}
