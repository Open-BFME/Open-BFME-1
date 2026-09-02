// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, ObjectID objectID);
	virtual ~AudioEventRTS();

private:
	unsigned char m_pad04[0x6c];
};

class BfmeAudioPairState
{
public:
	BfmeAudioPairState();
	~BfmeAudioPairState();

private:
	AsciiString m_firstName;
	AsciiString m_secondName;
	AudioEventRTS m_firstEvent;
	AudioEventRTS m_secondEvent;
};

extern AsciiString TheBfmeCrateNameDefault;

BfmeAudioPairState::BfmeAudioPairState() :
	m_firstName(),
	m_secondName(),
	m_firstEvent(TheBfmeCrateNameDefault, INVALID_OBJECT_ID),
	m_secondEvent(TheBfmeCrateNameDefault, INVALID_OBJECT_ID)
{
}

BfmeAudioPairState::~BfmeAudioPairState()
{
}
