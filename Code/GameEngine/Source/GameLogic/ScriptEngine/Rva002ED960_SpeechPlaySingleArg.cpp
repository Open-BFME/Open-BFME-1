// cl: /DNDEBUG /MD /EHsc
// Fuzzy-twin lane: near-twin of ?doSpeechPlay@ScriptActions@@IAEXABVAsciiString@@_N@Z
// (Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSpeechPlay.cpp,
// retail 0x002EE950) -- same AudioEventRTS/PlayerList/Player/AudioManager
// field layout (ThePlayerList read at the same VA 0x012ED748, confirmed by
// the pin note on reverse/symbols.csv:10765) and the same four callees
// (ctor 0x00025306, setIsLogicalAudio 0x00008206, setPlayerIndex 0x0003AC88,
// dtor 0x00026F35), but "ret 4" proves only ONE stack parameter (the
// AsciiString&) instead of the twin's two, and there is no call that could
// be setUninterruptable -- so this sibling always constructs with the
// default uninterruptable flag and never takes an allowOverlap argument.
// Real name/class unknown (identity not provable from the callee set
// alone): landed under an address-derived TAG per IDENTITY POLICY.

typedef bool Bool;

class AsciiString;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, ObjectID owner);
	~AudioEventRTS();
	void setIsLogicalAudio(Bool logical);
	void setPlayerIndex(int index);

	unsigned char m_pad[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
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

// retail cleans one stack dword on return ("ret 4") with no explicit `this`
// use in the body -- a non-static member function (thiscall: this in ecx,
// one by-ref stack arg popped by the callee), not a free function.
class Rva002ED960Owner
{
public:
	void playSpeech(const AsciiString &speechName);
};

// ?playSpeech@Rva002ED960Owner@@QAEXABVAsciiString@@@Z -- address-derived TAG, identity unresolved
void Rva002ED960Owner::playSpeech(const AsciiString &speechName)
{
	AudioEventRTS speech(speechName, INVALID_OBJECT_ID);
	speech.setIsLogicalAudio(true);
	speech.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent(&speech);
}
