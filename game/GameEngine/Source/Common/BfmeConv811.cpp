// Slot 13 of the message stream returns the appended message; the boolean
// argument goes through ILT 0x000032AB -> 0x0008AB90, the matched
// GameMessage::appendBooleanArgument.
class GameMessage
{
public:
	void appendBooleanArgument(bool b);
};

class BfmeObjEGE
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual GameMessage *bfmeGet13EGE(int id);
};

class BfmeObj2EGE
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual void bfmeV43();
	virtual void bfmeV44();
	virtual void bfmeV45();
	virtual void bfmeV46();
	virtual void bfmeV47();
	virtual void bfmeV48();
	virtual void bfmeV49();
	virtual void bfmeV50();
	virtual void bfmeV51();
	virtual void bfmeV52();
	virtual void bfmeV53();
	virtual void bfmeV54();
	virtual void bfmeV55();
	virtual void bfmeV56();
	virtual void bfmeV57();
	virtual void bfmeVirt58EGE();
};

// The global at retail 0x012ED5EC is MessageStream *TheMessageStream, defined
// once in game/GameEngine/Source/Common/MessageStream.cpp (class declared by
// Common/MessageStream.h).  BfmeObjEGE above stays as this TU's local view of
// the pointee, so the two uses cast.
class MessageStream;

extern MessageStream *TheMessageStream;

// The global at retail 0x012F148C is InGameUI *TheInGameUI, defined once in
// game/GameEngine/Source/GameClient/InGameUI.cpp.  Only the linked name may be
// referenced here; BfmeObj2EGE above stays as this TU's local view of the
// pointee, so the uses cast.
class InGameUI;

extern InGameUI *TheInGameUI;

void bfmeGoEGEa()
{
	GameMessage *r = ((BfmeObjEGE *)TheMessageStream)->bfmeGet13EGE(0x3eb);
	r->appendBooleanArgument(true);
	((BfmeObj2EGE *)TheInGameUI)->bfmeVirt58EGE();
}

struct BfmeNodeEGF
{
	unsigned char m_bfmeHead[8];
	BfmeNodeEGF *m_bfmeNext;
	unsigned char m_bfmePad[0x14];
	int m_bfmeFrame;
};

// ILT 0x0003D3B6 -> 0x0026E5F0, matched under this address-derived view of
// the same subobject (BfmeConv1786.cpp).
class BfmeOwnerQF
{
public:
	char bfmeLinkedQF();
};

class BfmeSubEGF
{
public:
	bool bfmeAskEGFa();

	unsigned char m_bfmeHead[4];
	BfmeNodeEGF *m_bfmeList;
	unsigned char m_bfmePad[8];
	void *m_bfmeOwner;
};

// Retail 0x0026E5A0: the EGF query walks at most 100 entries and reports
// whether one has a frame other than the invalid sentinel.  The two leading
// guards are the BFME subobject's list and owner fields at +0x04 and +0x10.
bool BfmeSubEGF::bfmeAskEGFa()
{
	BfmeNodeEGF *node = m_bfmeList;
	if (node == 0)
		return false;
	if (m_bfmeOwner == 0)
		return false;

	unsigned int i = 0;
	int invalidFrame = 0x7fffffff;
	do
	{
		if (i++ >= 100)
			return false;
		if (node->m_bfmeFrame != invalidFrame)
			return true;
		node = node->m_bfmeNext;
	}
	while (node != 0);
	return false;
}

struct BfmeThingEGF
{
	bool bfmeGoEGFa();
	bool bfmeGoEGFb();
	unsigned char m_bfmeHeadA[0x140];
	BfmeSubEGF *m_bfmeP;
	unsigned char m_bfmeHeadB[0x94];
	int m_bfmeState;
};

bool BfmeThingEGF::bfmeGoEGFa()
{
	switch (m_bfmeState)
	{
	case 1:
	case 4:
		{
			BfmeSubEGF *p = m_bfmeP;
			if (p && p->bfmeAskEGFa())
				return true;
		}
		break;
	}
	return false;
}

bool BfmeThingEGF::bfmeGoEGFb()
{
	switch (m_bfmeState)
	{
	case 1:
	case 4:
		{
			BfmeSubEGF *p = m_bfmeP;
			if (p && ((BfmeOwnerQF *)p)->bfmeLinkedQF())
				return true;
		}
		break;
	}
	return false;
}



void bfmeGoEGEb()
{
	GameMessage *r = ((BfmeObjEGE *)TheMessageStream)->bfmeGet13EGE(0x3eb);
	r->appendBooleanArgument(true);
	((BfmeObj2EGE *)TheInGameUI)->bfmeVirt58EGE();
}
