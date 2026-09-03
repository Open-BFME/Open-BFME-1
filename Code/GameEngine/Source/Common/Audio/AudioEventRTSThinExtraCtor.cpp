// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: thin AudioEventRTS constructors that call outlined initFromName
// (ILT 0x0004A86D) after the member zeros.
//   extra       0x000B2D90 101B  (inlined twin 0x000B2CC0)
//   positional  0x000B2F00 133B  (inlined twin 0x000B2E10)

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

struct Coord3D
{
	unsigned int x, y, z;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	AudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int extra);
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
	unsigned int m_objectID;
	int m_ownerType;
	Coord3D m_position;
	unsigned char m_flag40;
	char m_41[0x6C - 0x41];
	AsciiString m_tail;
};

// object-symbol=??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, int extra)
{
	initFromName(eventName);
	m_timeOfDay = static_cast<unsigned int>(extra);
}

// object-symbol=??0AudioEventRTS@@QAE@ABVAsciiString@@PBUCoord3D@@H@Z
AudioEventRTS::AudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int extra)
{
	initFromName(eventName);
	m_position = *positionOfAudio;
	m_ownerType = 0;
	m_timeOfDay = static_cast<unsigned int>(extra);
	m_flag40 = 1;
}
