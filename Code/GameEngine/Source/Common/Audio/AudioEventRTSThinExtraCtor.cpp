// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: thin AudioEventRTS(name, extra) at 0x000B2D90, 101B.
// Same C++ signature as the inlined 0x000B2CC0 body; this TU calls the
// outlined initFromName helper (ILT 0x0004A86D) after the member zeros.

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString();

private:
	char *m_data;
};

class CountedPtr
{
public:
	CountedPtr() : m_ptr(0) {}
	~CountedPtr();

	void *m_ptr;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	virtual ~AudioEventRTS();
	void initFromName(const AsciiString &eventName);

private:
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	char m_20[8];
	unsigned int m_timeOfDay;
	char m_2C[0x6C - 0x2C];
	AsciiString m_tail;
};

// object-symbol=??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, int extra)
{
	initFromName(eventName);
	m_timeOfDay = static_cast<unsigned int>(extra);
}
