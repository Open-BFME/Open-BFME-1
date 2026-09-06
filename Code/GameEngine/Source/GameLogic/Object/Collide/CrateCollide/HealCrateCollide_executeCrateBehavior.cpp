// cl: /DNDEBUG /MD /EHsc
// Zero Hour's HealCrateCollide behavior adapted to BFME's object and audio
// ABI. This TU models only the slices used by the retail body. Copied from
// the landed twin (difflib ratio 0.942 against retail @ 0x00217C10):
// Code/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ShroudCrateCollide_executeCrateBehavior.cpp
// (retail 0x00218690, ?executeCrateBehavior@ShroudCrateCollide@@MAE_NPAVObject@@@Z).
// Differences proved by tools/dis_retail.py on both bodies:
//   - Player::healAllObjects() (direct, non-virtual call) instead of
//     TheShroudManager->revealMapForPlayer(cratePlayer->getPlayerIndex())
//   - MiscAudio::m_crateHeal at offset 0x850 (before m_crateShroud, which
//     sits at 0x8c0 in the twin) instead of m_crateShroud
//   - AudioEventRTS::setPosition(other->getPosition()) -- an ADDRESS
//     (retail "add esi,0x38", no dereference) -- instead of
//     setObjectID(other->getID()) which loads a scalar field by value

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void healAllObjects();

private:
	char m_bfmeHead[0x24];
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
	const Coord3D *getPosition() const { return &m_position; }

private:
	char m_bfmeHead[0x38];
	Coord3D m_position;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);
	~AudioEventRTS();
	void setPosition(const Coord3D *pos);

private:
	char m_bfmeBody[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
struct MiscAudio
{
	char m_bfmeHead[0x850];
	AudioEventRTS m_crateHeal;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual const MiscAudio *getMiscAudio() const = 0;
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealCrateCollide.h
class HealCrateCollide
{
protected:
	virtual Bool executeCrateBehavior(Object *other);
};

Bool HealCrateCollide::executeCrateBehavior(Object *other)
{
	Player *cratePlayer = other->getControllingPlayer();
	cratePlayer->healAllObjects();

	AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateHeal;
	soundToPlay.setPosition(other->getPosition());
	TheAudio->addAudioEvent(&soundToPlay);

	return true;
}
