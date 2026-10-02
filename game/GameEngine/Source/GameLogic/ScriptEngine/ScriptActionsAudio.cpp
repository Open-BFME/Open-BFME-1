// cl: /DNDEBUG /MD /EHsc
// readable body of ?doSpeechPlay@ScriptActions@@IAEXABVAsciiString@@_N@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The three actions that build an AudioEventRTS on the stack and hand it to the
// audio subsystem:
//
//   0x002EE950  doSpeechPlay                              addAudioEvent
//   0x002F4360  doMusicTrackChange           MUSIC_SET_TRACK, arm 102
//   0x002F44E0  Rva002F44E0AudioPushMusicAction::execute   AUDIO_PUSH_MUSIC, arm 450
//
// All three fill the same 0x70-byte event, set the logical-audio flag and the
// local player's index on it, and queue it. The two music bodies are twins that
// differ only in how they start the track -- one calls slot 27 before building
// the event, the other hands the finished event to slot 25.
//
// One global here is one object: this TU used to spell the audio pointer at
// 0x012ED668 under two names, and retail has just the one --
//   TheAudio (0x012ED668), an AudioManager*;
// so the two music bodies drive the same vftable as the speech body, and the
// music entries are slot 25 (+0x64) setMusicEvent and slot 27 (+0x6C)
// startMusic on AudioManager above.

typedef bool Bool;
typedef int Int;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// The 0x70-byte event, dispatch-only: the retail constructor supplies the vptr
// and no vtable is emitted here. Counting from the object base, the vptr is at
// +0x00, the uninterruptable flag at +0x43 and the music tail at +0x64, +0x68
// and +0x6C. The speech file had counted the same flag from +0x00 with no vptr
// modelled, which lands it in the same place and says something different about
// the object; this states the vptr once and keeps every field where its body
// reads it.
//
// The two constructors are two ILTs, not two readings of one: the ObjectID form
// is 0x00025306 and the Int form 0x0001EC13.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, ObjectID owner);
	AudioEventRTS(const AsciiString &name, Int owner);
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio(Bool logical);
	void setPlayerIndex(Int index);
	void setUninterruptable(Bool uninterruptable)
	{
		m_uninterruptable = uninterruptable;
	}

	unsigned char m_beforeUninterruptable[0x3f];
	Bool m_uninterruptable;
	unsigned char m_beforeMusicFields[0x64 - 0x44];
	Int m_musicStackValue;
	Int m_musicPlayCount;
	AsciiString m_scriptName;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_beforeIndex[0x24];
	Int m_playerIndex;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }

	unsigned char m_beforeLocalPlayer[0x0c];
	Player *m_localPlayer;
};

// The music bodies read the same object the speech body does -- the retail
// global at 0x012ED748 is ThePlayerList -- so they share the PlayerList type
// above and the reference mangles to ?ThePlayerList@@3PAVPlayerList@@A.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
// The music entries below slot 17 are the same object too: the reference
// mangles to ?TheAudio@@3PAVAudioManager@@A, which is the one name retail
// carries for 0x012ED668.
class AudioManager
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
	virtual void slot26() = 0;
	virtual void startMusic(Int first, Int second, Int third) = 0;
};

class ScriptEngine
{
};

class BFMEScriptEngineFlagLookup
{
public:
	AsciiString joinRva0033DB00(AsciiString name);
};

extern PlayerList *ThePlayerList;
extern AudioManager *TheAudio;
extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSpeechPlay(const AsciiString &speechName, Bool allowOverlap);
	void doMusicTrackChange(const AsciiString &trackName, Bool fadeout,
		Bool logicalAudio, Int playCount, const AsciiString &scriptName,
		Int stackValue);
};

class Rva002F44E0AudioPushMusicAction
{
public:
	void execute(const AsciiString &trackName, Bool fadeout, Bool logicalAudio,
		Int playCount, const AsciiString &scriptName, Int stackValue);
};

void ScriptActions::doSpeechPlay(const AsciiString &speechName, Bool allowOverlap)
{
	AudioEventRTS speech(speechName, INVALID_OBJECT_ID);
	speech.setIsLogicalAudio(true);
	speech.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	speech.setUninterruptable(!allowOverlap);
	TheAudio->addAudioEvent(&speech);
}

// ?doMusicTrackChange@ScriptActions@@IAEXABVAsciiString@@_N1H0H@Z
void ScriptActions::doMusicTrackChange(const AsciiString &trackName,
	Bool fadeout, Bool logicalAudio, Int playCount,
	const AsciiString &scriptName, Int stackValue)
{
	Int fadein = !fadeout;
	TheAudio->startMusic(0, stackValue, fadein);

	if (playCount < 1 && playCount != -1)
		playCount = 1;

	AudioEventRTS event(trackName, 0);
	event.setIsLogicalAudio(logicalAudio);
	event.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	event.m_musicStackValue = stackValue;
	event.m_musicPlayCount = playCount;

	if (scriptName.isNotEmpty())
	{
		event.m_scriptName =
			((BFMEScriptEngineFlagLookup *)TheScriptEngine)->joinRva0033DB00(scriptName);
	}

	TheAudio->addAudioEvent(&event);
}

void Rva002F44E0AudioPushMusicAction::execute(const AsciiString &trackName,
	Bool fadeout, Bool logicalAudio, Int playCount,
	const AsciiString &scriptName, Int stackValue)
{
	if (playCount < 1 && playCount != -1)
		playCount = 1;

	AudioEventRTS event(trackName, 0);
	event.setIsLogicalAudio(logicalAudio);
	event.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	event.m_musicStackValue = stackValue;
	event.m_musicPlayCount = playCount;

	if (scriptName.isNotEmpty())
	{
		event.m_scriptName =
			((BFMEScriptEngineFlagLookup *)TheScriptEngine)->joinRva0033DB00(scriptName);
	}

	int fadein = !fadeout;
	TheAudio->setMusicEvent(&event, fadein);
}
