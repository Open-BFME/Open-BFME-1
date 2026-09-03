// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS name-helper, retail 0x000B2610, 100B.
// Thin ctors at 0xB2D90 / 0xB2F00 / 0xB4440 / 0xB45E0 / 0xB4780 call this
// via ILT 0x0004A86D after stamping the vftable and zeroing strings.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class AsciiString
{
public:
	void set(const AsciiString &other);

	static const AsciiString TheEmptyString;

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
	void bind(const AsciiString &name);
	void clear(void)
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}

	Counted *m_ptr;
};

class AudioEventRTS
{
public:
	void initFromName(const AsciiString &name);
	void commonInit(void);

private:
	void *m_vftable;
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
};

// ?initFromName@AudioEventRTS@@QAEXABVAsciiString@@@Z
void AudioEventRTS::initFromName(const AsciiString &name)
{
	commonInit();
	if (name.m_data)
	{
		m_eventName.set(*reinterpret_cast<const AsciiString *>(name.m_data + 8));
		m_eventInfo.bind(name);
	}
	else
	{
		m_eventName.set(AsciiString::TheEmptyString);
		m_eventInfo.clear();
	}
}
