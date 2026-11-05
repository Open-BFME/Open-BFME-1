// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: retail 0x002157C0 (295 bytes; ret at +0x126, int3 at +0x127),
// beside the structure-body rubble refresh at 0x00215650 it calls. Same
// owner view as BfmeOwnFCB::bfmeAfterFCB (Object at +8, ID at +0xE4): when an
// object is attached, walk the list returned by TheGameLogic's 0x00383090
// getter for the entry whose name (+0x84) equals the module data's name
// (+0x5C), copy that entry's transform (+8) onto the object, take its +0x74
// value, then refresh the rubble state. No named caller identifies the class
// or the method, so both names are address-derived.
//
// Shape note measured against retail: the +0x74 value is read into a local
// before the store; storing the field directly swaps the entry pointer and
// the compared length between EBX and EBP.

#include "ascii_string.h"

// AsciiString::compare(const AsciiString &), expanded in place.  Calling the
// member emits a ?compare@AsciiString@@QBEHABV1@@Z COMDAT that is not retail's
// 0x0005FEB0 body.  The buffer pointer is the string's first word; its length
// is the unsigned short at +4 and the characters start at +8.
struct AsciiCompareView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
};

static __forceinline int asciiCompare( const AsciiString &left, const AsciiString &right )
{
	const AsciiCompareView &s = reinterpret_cast<const AsciiCompareView &>(right);
	const AsciiCompareView &t = reinterpret_cast<const AsciiCompareView &>(left);
	int thatLen = s.m_data ? s.m_data->length : 0;
	const char *thatData = s.m_data ? &s.m_data->data[0] : (const char *)"";
	int thisLen = t.m_data ? t.m_data->length : 0;
	const char *thisData = t.m_data ? &t.m_data->data[0] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = memcmp(thisData, thatData, n);
	if (c != 0)
		return c;
	return thisLen - thatLen;
}

class Matrix3D;

class Thing
{
public:
	void rva00132200( const Matrix3D *transform );
};

struct Rva002157C0Data
{
	char m_gap00[ 0x5c ];
	AsciiString field5c;
};

struct Rva002157C0Entry
{
	char m_gap00[ 0x74 ];
	int field74;
	char m_gap78[ 0xc ];
	AsciiString field84;
	Rva002157C0Entry *next;
};

class Gen_00383090
{
public:
	int m();
};

class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();
};

class Rva00215650Module
{
public:
	void rva00215650();
};

class Rva002157C0Owner
{
public:
	void refresh();

	void *m_vtable;
	Rva002157C0Data *m_data;
	Thing *m_object;
	char m_gap0C[ 0xd8 ];
	int fieldE4;
};

void Rva002157C0Owner::refresh()
{
	Thing *obj = m_object;
	if ( obj )
	{
		Rva002157C0Data *md = m_data;
		Rva002157C0Entry *entry = (Rva002157C0Entry *)( (Gen_00383090 *)TheGameLogic )->m();
		AsciiString name;
		for ( ; entry; entry = entry->next )
		{
			name = entry->field84;
			if ( asciiCompare( name, md->field5c ) == 0 )
			{
				obj->rva00132200( (const Matrix3D *)&entry->m_gap00[ 8 ] );
				int value = entry->field74;
				fieldE4 = value;
				( (BfmeOwnFCB *)this )->bfmeAfterFCB();
				break;
			}
		}
		( (Rva00215650Module *)this )->rva00215650();
		( (BfmeOwnFCB *)this )->bfmeAfterFCB();
	}
}
