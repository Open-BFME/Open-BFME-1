// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Open-BFME5: Glo012F1028Sub::bfmeNotify, retail 0x003CAD20, 87 bytes. The body
// carried only a machine byte-dump row; the pin naming it went in with
// Glo012F1024Entry::bfmeStep at 0x003A7320, which tail-jumps into it from both
// of its arms.
//
// It walks the pointer vector at +0x30 of the holder it keeps at +4 and gives
// each item three calls: one on itself with the item, one on the item, and one
// on itself again with the item and a zero. All three callees are pinned with
// this body.
//
// The vector is re-read from the holder after every call and the length is
// recomputed at the bottom of each trip, which is what an index loop against a
// live size() gives -- the calls could have grown it. The index and the length
// are compared unsigned.

typedef int Int;
typedef unsigned int UnsignedInt;

class Glo012F1028Item
{
public:
	void bfmeRun(void);					// ILT 0x00006348

	char m_bfmePayloadHead[0x28];
	int m_bfmePayload;
	char m_bfmeHead[0xA8 - 0x2C];
	unsigned char m_bfmeEnabled;			// +0xA8
	char m_bfmeGap[0xB4 - 0xA9];
	void *m_bfmeValue;					// +0xB4
};

class Rva003BAD00Owner
{
public:
	void notify0C(const AsciiString &key, int a, int b);	// ILT 0x0000B316
};

class BfmeItemVector
{
public:
	Int bfmeSize(void) const { return m_bfmeFinish - m_bfmeStart; }

	Glo012F1028Item **m_bfmeStart;				// +0x00
	Glo012F1028Item **m_bfmeFinish;				// +0x04
};

class Glo012F1028Holder
{
public:
	char m_bfmeHead[0x30];
	BfmeItemVector m_bfmeItems;				// +0x30
};

class Glo012F1028Sub
{
public:
	void bfmeNotify(void);

private:
	void bfmeBegin(Glo012F1028Item *item);			// ILT 0x0003BF2F
	void bfmeFinish(Glo012F1028Item *item, Int flag);	// ILT 0x00038910

	char m_bfmeHead[0x04];
	Glo012F1028Holder *m_bfmeHolder;			// +0x04
};

__declspec(noinline) void Glo012F1028Sub::bfmeBegin(Glo012F1028Item *item)
{
	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)m_bfmeHolder + 0x40);
	owner->notify0C(AsciiString("EnemyBordersEffect"),
		(int)&item->m_bfmePayload, 0);
	owner->notify0C(AsciiString("FriendlyBordersEffect"),
		(int)&item->m_bfmePayload, 0);
	owner->notify0C(AsciiString("HilightBordersEffect"),
		(int)&item->m_bfmePayload, 0);
}

// ?bfmeNotify@Glo012F1028Sub@@QAEXXZ
void Glo012F1028Sub::bfmeNotify(void)
{
	BfmeItemVector &items = m_bfmeHolder->m_bfmeItems;

	for (UnsignedInt i = 0; i < (UnsignedInt)items.bfmeSize(); ++i)
	{
		bfmeBegin(items.m_bfmeStart[i]);
		items.m_bfmeStart[i]->bfmeRun();
		bfmeFinish(items.m_bfmeStart[i], 0);
	}
}
