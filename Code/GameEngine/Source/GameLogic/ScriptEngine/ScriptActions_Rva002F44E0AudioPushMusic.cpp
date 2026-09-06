// cl: /DNDEBUG /MD /EHsc
// Retail 0x002F44E0: BFME AUDIO_PUSH_MUSIC action body.
// The six stack arguments and the AudioEventRTS tail are anchored by the
// action-table arm 450 and the retail stores at +0x6C/+0x70.

typedef bool Bool;
typedef int Int;

template <typename T>
struct BfmeStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_data[1];
};

template <typename T>
class StringBase
{
    friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &that);
	void set(const StringBase &that);
	void releaseBuffer();

protected:
	BfmeStringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() { StringBase<char>::releaseBuffer(); }

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	Bool isNotEmpty() const
	{
		return m_data != 0 && m_data->m_length != 0;
	}
};

// The BFME object retains the ZH event prefix and adds the music tail at
// +0x64, +0x68, and +0x6C.  This declaration is dispatch-only; it emits no
// vtable in this TU.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, Int owner);
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio(Bool logical);
	void setPlayerIndex(Int index);

	unsigned char m_beforeMusicFields[0x60];
	Int m_musicStackValue;
	Int m_musicPlayCount;
	AsciiString m_scriptName;
};

class ClientSubsystem
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void addAudioEvent(AudioEventRTS *event) = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void setMusicEvent(AudioEventRTS *event, Int fadein) = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_beforeIndex[0x24];
	Int m_playerIndex;
};

class Rva005655C0PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

	unsigned char m_beforeLocalPlayer[0x0c];
	Player *m_localPlayer;
};

class ScriptEngine
{
};

class BFMEScriptEngineFlagLookup
{
public:
	AsciiString joinRva0033DB00(AsciiString name);
};

extern ClientSubsystem *TheAudioClientUpdate;
extern Rva005655C0PlayerList *g_rva005655C0PlayerList;
extern ScriptEngine *TheScriptEngine;

class Rva002F44E0AudioPushMusicAction
{
public:
	void execute(const AsciiString &trackName, Bool fadeout, Bool logicalAudio,
		Int playCount, const AsciiString &scriptName, Int stackValue);
};

void Rva002F44E0AudioPushMusicAction::execute(const AsciiString &trackName,
	Bool fadeout, Bool logicalAudio, Int playCount,
	const AsciiString &scriptName, Int stackValue)
{
	if (playCount < 1 && playCount != -1)
		playCount = 1;

	AudioEventRTS event(trackName, 0);
	event.setIsLogicalAudio(logicalAudio);
	event.setPlayerIndex(g_rva005655C0PlayerList->getLocalPlayer()->getPlayerIndex());
	event.m_musicStackValue = stackValue;
	event.m_musicPlayCount = playCount;

	if (scriptName.isNotEmpty())
	{
		event.m_scriptName =
			((BFMEScriptEngineFlagLookup *)TheScriptEngine)->joinRva0033DB00(scriptName);
	}

	int fadein = !fadeout;
	TheAudioClientUpdate->setMusicEvent(&event, fadein);
}
