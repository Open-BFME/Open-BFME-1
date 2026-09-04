// ?bfmeFinish@Glo012F1028Sub@@AAEXPAVGlo012F1028Item@@H@Z
// partial score=0.96 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Dedicated TU for Glo012F1028Sub::bfmeFinish so the three matched
// siblings in Glo012F1028Sub_bfmeNotify.cpp keep their codegen.

typedef int Int;

class Glo012F1028Item
{
public:
	char m_bfmeHead[0x08];
	void *m_bfmeName;
	char m_bfmePayloadHead[0x28 - 0x0C];
	int m_bfmePayload;
	char m_bfmeGapA[0xA8 - 0x2C];
	unsigned char m_bfmeActive;			// +0xA8
	char m_bfmeGapA2[0xB4 - 0xA9];
	void *m_bfmeValue;					// +0xB4
};

class Rva003BAD00Owner
{
public:
	void notify0C(const AsciiString &key, int a, int b);	// ILT 0x0000B316
	void notify04(const AsciiString &key, int a);		// ILT 0x00027287
};

class GlobalData
{
public:
	char m_pad[0x94];
	void *m_livingWorldCampaign;				// +0x94
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
	void bfmeFinish(Glo012F1028Item *item, Int flag);

	char m_bfmeHead[0x04];
	Glo012F1028Holder *m_bfmeHolder;			// +0x04
};

// ?bfmeFinish@Glo012F1028Sub@@AAEXPAVGlo012F1028Item@@H@Z
void Glo012F1028Sub::bfmeFinish(Glo012F1028Item *item, Int flag)
{
	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)m_bfmeHolder + 0x40);

	bfmeBegin(item);
	if (!item->m_bfmeActive)
		return;

	if ((unsigned char)flag)
	{
		void *text = TheWritableGlobalData->m_livingWorldCampaign;
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
