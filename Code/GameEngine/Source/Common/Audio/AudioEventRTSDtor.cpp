// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS virtual destructor, retail 0x000B31F0, 162B.
// ILT 0x00026F35. Stores vftable 0x01081D40 and releases the AsciiStrings at
// +0x6C +0x1C +0x18 +0x14, the refcounted info at +8, then the filename at +4.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class Counted
{
public:
	virtual ~Counted();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class CountedPtr
{
public:
	~CountedPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Counted *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

private:
	AsciiString m_filenameToLoad;	// +0x04
	CountedPtr m_eventInfo;			// +0x08
	unsigned int m_playingHandle;	// +0x0C
	unsigned int m_killThisHandle;	// +0x10
	AsciiString m_eventName;		// +0x14
	AsciiString m_attackName;		// +0x18
	AsciiString m_decayName;		// +0x1C
	char m_pad20[0x6C - 0x20];
	AsciiString m_tail;				// +0x6C
};

// ??1AudioEventRTS@@UAE@XZ
AudioEventRTS::~AudioEventRTS()
{
}
