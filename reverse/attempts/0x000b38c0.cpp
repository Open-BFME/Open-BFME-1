// ?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z
// partial score=0.97 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::setEventName, retail 0x000B38C0, 140 bytes.
// Named by the byte-true call in Code/GameEngine/Source/Common/INI/ini.cpp
// (?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z).

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int compare(const AsciiString &other) const;
	AsciiString &operator=(const AsciiString &other);
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

class AudioEventInfo : public Counted
{
};

class CountedPtr
{
public:
	void clear(void)
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = 0;
		}
	}

	AudioEventInfo *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	void setEventName(AsciiString name);

private:
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;		// +0x08
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;	// +0x14
};

// ?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z
void AudioEventRTS::setEventName(AsciiString name)
{
	register AsciiString *const eventName = reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(this) + 0x14);
	if (name.compare(*eventName) != 0)
	{
		m_eventInfo.clear();
		*eventName = name;
	}
}
