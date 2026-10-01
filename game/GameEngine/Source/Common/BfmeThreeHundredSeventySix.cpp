// cl: /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Precompiled
#include "game_type.h"

struct BfmeClockYD
{
	unsigned char m_bfmeHead[0x3c];
	int m_bfmeNow;
};

class GameLogic;

// The retail global at 0x012F0898 is EA's GameLogic *TheGameLogic; this TU
// reads it through a local view holding only the frame stamp.
extern GameLogic *TheGameLogic;

struct AudioEventInfoRef
{
	void *m_bfmeData;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventInfoRef &eventInfo, ObjectID ownerID);
	~AudioEventRTS();
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
	virtual int addAudioEvent(const AudioEventRTS *event);
};

typedef int (__fastcall *AudioEventCall)(ClientSubsystem *, const AudioEventRTS *, const AudioEventRTS *);

struct ClientSubsystemVtable
{
	void *m_bfmeSlots[17];
	AudioEventCall addAudioEvent;
};

extern ClientSubsystem *TheAudioClientUpdate;

class GateOpenAndCloseBehavior
{
public:
	void playSound();
};

struct BfmeSoundSetYD
{
	unsigned char m_bfmeHead[0x18];
	AudioEventInfoRef m_bfmeEventName;
	unsigned char m_bfmeGap[4];
	AudioEventInfoRef m_bfmeEventNameTwo;
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
	BfmeOwnerYD *owner = m_bfmeOwner;
	switch (what)
	{
	case 0:
		if (soundSet->m_bfmeEventName.m_bfmeData != 0)
		{
			ObjectID ownerID = owner->m_bfmeOwnerID;
			AudioEventRTS event(soundSet->m_bfmeEventName, ownerID);
			ClientSubsystem *audio = TheAudioClientUpdate;
			ClientSubsystemVtable *vtable = *(ClientSubsystemVtable **)audio;
			m_bfmeAudioHandle = vtable->addAudioEvent(audio, &event, &event);
		}
		goto setNotPlaying;
	case 2:
		if (soundSet->m_bfmeEventNameTwo.m_bfmeData != 0)
		{
			ObjectID ownerID = owner->m_bfmeOwnerID;
			AudioEventRTS event(soundSet->m_bfmeEventNameTwo, ownerID);
			ClientSubsystem *audio = TheAudioClientUpdate;
			ClientSubsystemVtable *vtable = *(ClientSubsystemVtable **)audio;
			m_bfmeAudioHandle = vtable->addAudioEvent(audio, &event, &event);
		}
	setNotPlaying:
		m_bfmePlaying = false;
		break;
	case 1:
	case 3:
		if (!m_bfmePlaying)
			reinterpret_cast<GateOpenAndCloseBehavior *>(this)->playSound();
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
	m_bfmeStamp = ((BfmeClockYD *)TheGameLogic)->m_bfmeNow;
}
