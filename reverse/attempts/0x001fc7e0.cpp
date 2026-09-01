// ?bfmeSetYD@BfmeThingYD@@QAEXH@Z
// partial score=0.85 date=2026-09-01
struct BfmeClockYD
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

extern BfmeClockYD *g_bfmeClockYD;

class AsciiString
{
public:
	void *m_bfmeData;
};

enum ObjectID
{
	BFME_OBJECT_ID_UNUSED = 0
};

class BfmeAudioEventRTS
{
public:
	BfmeAudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	~BfmeAudioEventRTS();
	unsigned char m_bfmeTail[0x70];
};

class ClientSubsystem
{
public:
	virtual void bfmeUnused00();
	virtual void bfmeUnused01();
	virtual void bfmeUnused02();
	virtual void bfmeUnused03();
	virtual void bfmeUnused04();
	virtual void bfmeUnused05();
	virtual void bfmeUnused06();
	virtual void bfmeUnused07();
	virtual void bfmeUnused08();
	virtual void bfmeUnused09();
	virtual void bfmeUnused10();
	virtual void bfmeUnused11();
	virtual void bfmeUnused12();
	virtual void bfmeUnused13();
	virtual void bfmeUnused14();
	virtual void bfmeUnused15();
	virtual void bfmeUnused16();
	virtual int addAudioEvent(const BfmeAudioEventRTS *event);
};

extern ClientSubsystem *TheAudioClientUpdate;

struct BfmeSoundSetYD
{
	unsigned char m_bfmeHead[0x18];
	AsciiString m_bfmeEventName;
	unsigned char m_bfmeGap[4];
	AsciiString m_bfmeEventNameTwo;
};

struct BfmeOwnerYD
{
	unsigned char m_bfmeHead[0x74];
	ObjectID m_bfmeOwnerID;
};

class BfmeThingYD
{
public:
	virtual void bfmeSpareYDa0();
	virtual void bfmeSpareYDa1();
	virtual void bfmeSpareYDa2();
	virtual void bfmeSpareYDa3();
	virtual void bfmeSpareYDa4();
	virtual void bfmeSpareYDa5();
	virtual bool bfmeAskTwoYD();
	virtual void bfmeSpareYDb0();
	virtual void bfmeSpareYDb1();
	virtual void bfmeSpareYDb2();
	virtual bool bfmeAskOneYD();
	void bfmeStepYD();
	void bfmeSetYD(int what);
	void bfmeStopYD();
	void bfmeGoYD();
	unsigned char m_bfmePrefix[4];
	BfmeSoundSetYD *m_bfmeSoundSet;
	BfmeOwnerYD *m_bfmeOwner;
	unsigned char m_bfmeHead[0x18];
	int m_bfmeMode;
	unsigned char m_bfmeGapMode[4];
	bool m_bfmeFlag;
	unsigned char m_bfmeGapOne[3];
	int m_bfmeCount;
	unsigned char m_bfmeGapTwo[4];
	int m_bfmeStamp;
	unsigned char m_bfmeGapThree[4];
	int m_bfmeAudioHandle;
	bool m_bfmePlaying;
};

void BfmeThingYD::bfmeSetYD(int what)
{
	if (m_bfmeMode == what)
		return;

	BfmeSoundSetYD *soundSet = m_bfmeSoundSet;
	switch (what)
	{
	case 0:
		if (soundSet->m_bfmeEventName.m_bfmeData != 0)
		{
			BfmeAudioEventRTS event(soundSet->m_bfmeEventName, m_bfmeOwner->m_bfmeOwnerID);
			ClientSubsystem *audio = TheAudioClientUpdate;
			m_bfmeAudioHandle = audio->addAudioEvent(&event);
		}
		m_bfmePlaying = false;
		break;
	case 2:
		if (soundSet->m_bfmeEventNameTwo.m_bfmeData != 0)
		{
			BfmeAudioEventRTS event(soundSet->m_bfmeEventNameTwo, m_bfmeOwner->m_bfmeOwnerID);
			ClientSubsystem *audio = TheAudioClientUpdate;
			m_bfmeAudioHandle = audio->addAudioEvent(&event);
		}
		m_bfmePlaying = false;
		break;
	case 1:
	case 3:
		if (!m_bfmePlaying)
			bfmeStopYD();
		break;
	}

	m_bfmeMode = what;
}

void BfmeThingYD::bfmeGoYD()
{
	if (!bfmeAskOneYD())
		return;
	if (!bfmeAskTwoYD())
		return;
	bfmeStepYD();
	bfmeSetYD(2);
	m_bfmeFlag = false;
	m_bfmeCount = 0;
	m_bfmeStamp = g_bfmeClockYD->m_bfmeNow;
}
