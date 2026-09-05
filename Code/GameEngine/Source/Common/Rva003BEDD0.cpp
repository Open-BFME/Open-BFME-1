// cl: /DNDEBUG /MD /Ireference/shims/stringinline
//
// Address-derived: walks the circular list whose header pointer sits at +0xC0.
// Each node carries UnicodeString + two dwords at +8; type==2 and type==1
// are counted, then compared as fractions of the visit count against 0.75f.

#include "StringInline.h"
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

struct Rva003BEDD0Item
{
	UnicodeString name;
	int extra;
	int type;
 // Reconstruction shaping: the intrinsic emits no instruction, but preserves
 // retail's extra-field store before the type-field load. Not an upstream claim.
 Rva003BEDD0Item(const Rva003BEDD0Item &x) : name(x.name)
 {
     extra = x.extra;
     _WriteBarrier();
     type = x.type;
 }
};

struct Rva003BEDD0Node
{
	Rva003BEDD0Node *next;
	Rva003BEDD0Node *prev;
	Rva003BEDD0Item item;
};

class Rva003BEDD0
{
public:
	int classify();

	char m_pad00[ 0xC0 ];
	Rva003BEDD0Node *m_header;
};

int Rva003BEDD0::classify()
{
	int count1 = 0;
	int count2 = 0;
	int total = 0;
	for( Rva003BEDD0Node *node = m_header->next; node != m_header; node = node->next )
	{
		Rva003BEDD0Item tmp = node->item;
		if( tmp.type == 2 )
			++count2;
		else if( tmp.type == 1 )
			++count1;
		++total;
	}
	if ((float)count2 / (float)total >= 0.75f) return 2;
	if ((float)(count1 + count2) / (float)total >= 0.75f) return 1;
	return 0;
}
