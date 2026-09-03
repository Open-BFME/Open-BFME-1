// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class AsciiString;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, ObjectID owner);
	~AudioEventRTS();
	void setIsLogicalAudio(Bool logical);
	void setPlayerIndex(int index);
	void setUninterruptable(Bool uninterruptable)
	{
		m_uninterruptable = uninterruptable;
	}

	unsigned char m_beforeUninterruptable[0x43];
	Bool m_uninterruptable;
	unsigned char m_afterUninterruptable[0x70 - 0x44];
};

class Player
{
public:
	int getPlayerIndex() const
	{
		return m_playerIndex;
	}

	unsigned char m_beforeIndex[0x24];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return m_localPlayer;
	}

	unsigned char m_beforeLocalPlayer[0x0c];
	Player *m_localPlayer;
};

class AudioManager
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual void addAudioEvent(AudioEventRTS *event);
};

extern PlayerList *ThePlayerList;
extern AudioManager *TheAudio;

class ScriptActions
{
protected:
	void doSpeechPlay(const AsciiString &speechName, Bool allowOverlap);
};

void ScriptActions::doSpeechPlay(const AsciiString &speechName, Bool allowOverlap)
{
	AudioEventRTS speech(speechName, INVALID_OBJECT_ID);
	speech.setIsLogicalAudio(true);
	speech.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	speech.setUninterruptable(!allowOverlap);
	TheAudio->addAudioEvent(&speech);
}
