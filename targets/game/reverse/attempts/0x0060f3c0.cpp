// ?d_0060f3c0@@YAXXZ
// partial score=0.95 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The LivingWorldManager plays a queued Living World audio event, drops the
// queued name, marks LivingWorldLogic as active, and clears its pending flag.

extern "C" __declspec(dllimport) int __stdcall bfmeLockVGP(int *refCount);

class BfmeStringData
{
public:
	virtual ~BfmeStringData();

	int m_refCount;

	void Release_Ref()
	{
		if (bfmeLockVGP(&m_refCount) <= 0)
			delete this;
	}
};

class AsciiString
{
public:
	AsciiString() : m_data(0)
	{
	}

	AsciiString(const AsciiString &other) : m_data(other.m_data)
	{
	}

	~AsciiString()
	{
	}

	bool isEmpty() const
	{
		return m_data == 0;
	}

	void clear()
	{
		if (m_data)
		{
			m_data->Release_Ref();
			m_data = 0;
		}
	}

	private:
	BfmeStringData *m_data;
};

enum LivingWorldID
{
	INVALID_LIVING_WORLD_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, LivingWorldID ownerID);
	void destroyAudioEventRTS();
	~AudioEventRTS()
	{
		destroyAudioEventRTS();
	}

private:
	unsigned char m_padding[0x70];
};

class ClientSubsystem
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03)
	SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11)
	SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16)
	virtual void addAudioEvent(AudioEventRTS *event);
#undef SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

struct LivingWorldLogicSub
{
	unsigned char m_padding[0x10];
	unsigned char m_active;
};

class CampaignObject
{
public:
	unsigned char m_padding[0x28];
	LivingWorldLogicSub *m_sub;
};

extern CampaignObject *TheLivingWorldLogic;

class BfmeLivingWorldManager
{
public:
	void playSound();
	AsciiString &soundName()
	{
		return *reinterpret_cast<AsciiString *>(&m_soundName);
	}

private:
	unsigned char m_padding[0x238];
	BfmeStringData *m_soundName;
	LivingWorldID m_soundOwner;
	unsigned char m_padding240[0x54];
	unsigned char m_soundPending;
};

// ?playSound@BfmeLivingWorldManager@@QAEXXZ
void BfmeLivingWorldManager::playSound()
{
	AsciiString &soundName = *reinterpret_cast<AsciiString *>(&m_soundName);
	if (m_soundName)
	{
		AudioEventRTS event(soundName, m_soundOwner);
		ClientSubsystem *audio = TheAudioClientUpdate;
		audio->addAudioEvent(&event);
		soundName.clear();
	}

	TheLivingWorldLogic->m_sub->m_active = 1;
	m_soundPending = 0;
}
