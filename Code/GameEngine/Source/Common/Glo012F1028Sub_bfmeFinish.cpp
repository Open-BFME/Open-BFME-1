// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// Glo012F1028Sub::bfmeFinish, retail 0x003CA7C0, 423 bytes, ret 8. The matched
// Glo012F1028Sub::bfmeNotify (0x003CAD20) calls it through ILT 0x00038910 with
// each item and a zero, right after bfmeBegin (0x003C7010) cleared the same
// three border-effect keys this body sets again.
//
// The second argument is a bool: retail tests it with a byte load
// (`mov al,[esp+20h]; test al,al`). Declared as an int, MSVC 7.1 hands the six
// AsciiString temporaries the incoming item home instead of the flag home and
// every one of them lands four bytes low; as a bool the frame is retail's.
//
// Its own TU so the three matched siblings in Glo012F1028Sub_bfmeNotify.cpp
// keep their codegen.

class Glo012F1028Item
{
public:
	char m_bfmeHead[0x28];
	int m_bfmePayload;					// +0x28
	char m_bfmeGapA[0xA8 - 0x2C];
	unsigned char m_byteA8;				// +0xA8
	char m_bfmeGapA2[0xB4 - 0xA9];
	void *m_bfmeValue;					// +0xB4
};

class Rva003BAD00Owner
{
public:
	void notify0C(const AsciiString &key, int a, int b);	// ILT 0x0000B316
	void notify04(const AsciiString &key, int a);		// ILT 0x00027287
};

// Only the AsciiString at +0x94 (see GlobalDataDestructor.cpp) is read here,
// through its buffer pointer: null or a zero length means empty.
class GlobalData
{
public:
	char m_pad[0x94];
	void *m_s94;						// +0x94
};

extern GlobalData *TheWritableGlobalData;

int __cdecl bfmeCallFHA(void *a, void *b);			// ILT 0x00041164

class Glo012F1028Holder
{
public:
	char m_bfmeHead[0x30];
};

class Glo012F1028Sub
{
private:
	void bfmeBegin(Glo012F1028Item *item);			// ILT 0x0003BF2F
	void bfmeFinish(Glo012F1028Item *item, bool flag);

	char m_bfmeHead[0x04];
	Glo012F1028Holder *m_bfmeHolder;			// +0x04
};

// ?bfmeFinish@Glo012F1028Sub@@AAEXPAVGlo012F1028Item@@_N@Z
void Glo012F1028Sub::bfmeFinish(Glo012F1028Item *item, bool flag)
{
	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)m_bfmeHolder + 0x40);

	bfmeBegin(item);
	if (!item->m_byteA8)
		return;

	if (flag)
	{
		void *text = TheWritableGlobalData->m_s94;
		if (text == 0 || *(unsigned short *)((char *)text + 4) == 0)
		{
			owner->notify0C(AsciiString("HilightBordersEffect"),
				(int)&item->m_bfmePayload, 1);
			owner->notify04(AsciiString("HilightBordersEffect"), 0);
		}
	}

	if (bfmeCallFHA(item->m_bfmeValue, item->m_bfmeValue) == 1)
	{
		owner->notify0C(AsciiString("FriendlyBordersEffect"),
			(int)&item->m_bfmePayload, 1);
		owner->notify04(AsciiString("FriendlyBordersEffect"), 0);
	}
	else
	{
		owner->notify0C(AsciiString("EnemyBordersEffect"),
			(int)&item->m_bfmePayload, 1);
		owner->notify04(AsciiString("EnemyBordersEffect"), 0);
	}
}
