// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Open-BFME: ScriptActions::doPlaySoundEffectAtTeam, retail 0x002FD280, 242 bytes.
//
// executeAction (0x00303BF0) reaches this body through ILT 0x00026A94 from
// jump-table arm 509, and the action template registered at index 509 is
// PLAY_SOUND_EFFECT_AT_TEAM ("Play sound ... as though coming from a member
// of ..."). Its two string parameters are the sound and the team name.

#include "StringInline.h"

typedef int Int;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

// Retail's KindOf name table (VA 0x012AA068) puts HORDE at index 0x6C.
enum KindOfType
{
	KINDOF_HORDE = 108
};

class Object;

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;	// ILT 0x0003251F
};

// The horde member the event is played from comes out of slot 61 (+0xF4);
// its meaning is not proven, so the slot keeps its offset as its name.
class HordeContainInterface
{
public:
#define HORDE_SLOT(N) virtual void slot##N() = 0;
	HORDE_SLOT(00) HORDE_SLOT(01) HORDE_SLOT(02) HORDE_SLOT(03)
	HORDE_SLOT(04) HORDE_SLOT(05) HORDE_SLOT(06) HORDE_SLOT(07)
	HORDE_SLOT(08) HORDE_SLOT(09) HORDE_SLOT(10) HORDE_SLOT(11)
	HORDE_SLOT(12) HORDE_SLOT(13) HORDE_SLOT(14) HORDE_SLOT(15)
	HORDE_SLOT(16) HORDE_SLOT(17) HORDE_SLOT(18) HORDE_SLOT(19)
	HORDE_SLOT(20) HORDE_SLOT(21) HORDE_SLOT(22) HORDE_SLOT(23)
	HORDE_SLOT(24) HORDE_SLOT(25) HORDE_SLOT(26) HORDE_SLOT(27)
	HORDE_SLOT(28) HORDE_SLOT(29) HORDE_SLOT(30) HORDE_SLOT(31)
	HORDE_SLOT(32) HORDE_SLOT(33) HORDE_SLOT(34) HORDE_SLOT(35)
	HORDE_SLOT(36) HORDE_SLOT(37) HORDE_SLOT(38) HORDE_SLOT(39)
	HORDE_SLOT(40) HORDE_SLOT(41) HORDE_SLOT(42) HORDE_SLOT(43)
	HORDE_SLOT(44) HORDE_SLOT(45) HORDE_SLOT(46) HORDE_SLOT(47)
	HORDE_SLOT(48) HORDE_SLOT(49) HORDE_SLOT(50) HORDE_SLOT(51)
	HORDE_SLOT(52) HORDE_SLOT(53) HORDE_SLOT(54) HORDE_SLOT(55)
	HORDE_SLOT(56) HORDE_SLOT(57) HORDE_SLOT(58) HORDE_SLOT(59)
	HORDE_SLOT(60)
#undef HORDE_SLOT
	virtual Object *slotF4() = 0;	// slot 61, +0xF4
};

// BFME's ContainModuleInterface: getHordeContainInterface is slot 26 (+0x68).
class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(N) virtual void slot##N() = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25)
#undef CONTAIN_SLOT
	virtual HordeContainInterface *getHordeContainInterface() = 0;	// +0x68
};

// BFME's Object keeps its ID at +0x74 and its contain module at +0x1FC.
class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }

	unsigned char m_unreconstructed_00[0x74];
	ObjectID m_id;								// +0x74
	unsigned char m_unreconstructed_78[0x1fc - 0x78];
	ContainModuleInterface *m_contain;			// +0x1FC
};

class Team
{
public:
	Object *getFirstItemIn_TeamMemberList() const;	// ILT 0x0003FD41
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_unreconstructed_00[0x24];
	Int m_playerIndex;							// +0x24
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

	unsigned char m_unreconstructed_00[0x0c];
	Player *m_local;							// +0x0C
};

// BFME's audio event is 0x70 bytes; ScriptActions.cpp names the same view.
class BfmeAudioEventRTS
{
public:
	BfmeAudioEventRTS(const AsciiString &name, ObjectID owner);	// ILT 0x0003961C
	~BfmeAudioEventRTS();										// ILT 0x00026F35
	void setPlayerIndex(Int index);								// ILT 0x0003AC88

	unsigned char m_unreconstructed_00[0x70];
};

// BFME's Audio vtable puts addAudioEvent at slot 17.
class AudioManager
{
public:
#define AUDIO_SLOT(N) virtual void slot##N() = 0;
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16)
#undef AUDIO_SLOT
	virtual void addAudioEvent(BfmeAudioEventRTS *event) = 0;	// +0x44
};

// BFME's ScriptEngine puts getTeamNamed at slot 17 and takes the name by value
// with an extra Bool.
class ScriptEngine
{
public:
#define SCRIPT_SLOT(N) virtual void slot##N() = 0;
	SCRIPT_SLOT(00) SCRIPT_SLOT(01) SCRIPT_SLOT(02) SCRIPT_SLOT(03)
	SCRIPT_SLOT(04) SCRIPT_SLOT(05) SCRIPT_SLOT(06) SCRIPT_SLOT(07)
	SCRIPT_SLOT(08) SCRIPT_SLOT(09) SCRIPT_SLOT(10) SCRIPT_SLOT(11)
	SCRIPT_SLOT(12) SCRIPT_SLOT(13) SCRIPT_SLOT(14) SCRIPT_SLOT(15)
	SCRIPT_SLOT(16)
#undef SCRIPT_SLOT
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;	// +0x44
};

extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;
extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
	void doPlaySoundEffectAtTeam(const AsciiString &sound, const AsciiString &team);
};

// ?doPlaySoundEffectAtTeam@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doPlaySoundEffectAtTeam(const AsciiString &sound, const AsciiString &team)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (!theTeam)
		return;

	Object *obj = theTeam->getFirstItemIn_TeamMemberList();
	if (!obj)
		return;

	// A horde plays the sound from the member its contain module hands back.
	if (obj->isKindOf(KINDOF_HORDE) && obj->getContain())
	{
		HordeContainInterface *horde = obj->getContain()->getHordeContainInterface();
		if (horde)
		{
			Object *member = horde->slotF4();
			if (member)
				obj = member;
		}
	}

	BfmeAudioEventRTS audioEvent(sound, obj->getID());
	audioEvent.setPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheAudio->addAudioEvent(&audioEvent);
}
