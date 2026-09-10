// cl: /DNDEBUG /MD /EHsc
// Retail 0x00174A20: the desperate-attack move-state update.  The owner is
// notified of its model condition once, the path-ready branch fills the goal
// position from the path's last node, and a non-continuing internal update
// latches the state flag and plays the unit's VoiceDesperateAttack sound.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned int AudioHandle;
typedef unsigned int ObjectID;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &source);
	~AudioEventRTS();

	void setObjectID(ObjectID id);
	void setPlayerIndex(Int index);

private:
	UnsignedByte m_unmodelled[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;
};

class Player
{
public:
	Int getPlayerIndex() const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x24);
	}
};

class BfmeTeam
{
public:
	Player *bfmeGetControllingPlayer() const;
};

// The AI's stop helper carries no recovered name of its own, so it is reached
// through the address-derived view the ledger already holds for it.
class Rva0026F110
{
public:
	void set();
};

struct Rva00174A20PathNode
{
	UnsignedByte m_pad00[0x0c];
	Coord3D m_position;
};

struct Rva00174A20Path
{
	UnsignedByte m_pad00[8];
	Rva00174A20PathNode *m_lastNode;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
struct AIUpdateInterface
{
	UnsignedByte m_pad00[0x140];
	Rva00174A20Path *m_path;                           // retail this+0x140
	UnsignedByte m_pad144[0x31e - 0x144];
	Bool m_waitingForPath;                             // retail this+0x31E
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
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
	virtual const ThingTemplate *getTemplate() const = 0;

	void notifyModelConditionChanged();
	Bool bfmeGetRecentDamageSource(UnsignedInt *source, UnsignedInt kind) const;

	ObjectID getID() const
	{
		return *(const ObjectID *)((const UnsignedByte *)this + 0x74);
	}

	UnsignedByte m_unreconstructed_004[0x118 - 0x04];
	UnsignedInt m_modelConditionFlags;                 // retail Object+0x118
	UnsignedByte m_unreconstructed_11c[0x204 - 0x11c];
	AIUpdateInterface *m_ai;                           // retail Object+0x204
	UnsignedByte m_unreconstructed_208[0x23c - 0x208];
	BfmeTeam *m_team;                                  // retail Object+0x23C
};

enum { BFME_MODEL_CONDITION_NOTIFIED = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();

	UnsignedByte m_unmodelled[0x10];
	Object *m_owner;                                   // retail this+0x10
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
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event) = 0;  // vtable +0x44
};

extern UnsignedByte g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a();

typedef void (__cdecl *Rva00174A20CritterDesyncLog)(void *, const char *);

static void rva00174A20_log(const char *message)
{
	if (g_012F0239 && g_012ED4FC)
		((Rva00174A20CritterDesyncLog)j_0003a17a)(g_012ED4FC, message);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType update();

protected:
	UnsignedByte m_pad04[0x18];
	StateMachine *m_machine;                           // retail this+0x1C
	UnsignedByte m_pad20[4];
	Coord3D m_goalPosition;                            // retail this+0x24
	UnsignedByte m_pad30[0x1c];
	Bool m_adjustDestinations;                         // retail this+0x4C
	UnsignedByte m_pad4d[7];
	Bool m_checkForPath;                               // retail this+0x54
	UnsignedByte m_pad55[3];
	Bool m_desperateAttackDone;                        // retail this+0x58
};

class Rva00174A20State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

StateReturnType Rva00174A20State::update()
{
	Object *source = m_machine->m_owner;
	UnsignedInt flags = source->m_modelConditionFlags;
	if (!(flags & BFME_MODEL_CONDITION_NOTIFIED))
	{
		source->m_modelConditionFlags = flags | BFME_MODEL_CONDITION_NOTIFIED;
		source->notifyModelConditionChanged();
	}

	AIUpdateInterface *ai = source->m_ai;
	Object *victim = m_machine->getGoalObject();
	if (!victim || (*((UnsignedByte *)victim + 0x344) & 1))
		return STATE_SUCCESS;

	if (m_desperateAttackDone)
		return STATE_SUCCESS;

	if (m_checkForPath)
	{
		AIUpdateInterface *ownerAI = source->m_ai;
		Rva00174A20Path *path = ownerAI->m_path;
		if (path && !ownerAI->m_waitingForPath)
		{
			m_goalPosition = path->m_lastNode->m_position;
			rva00174A20_log("CritterDesync: setAdjustDestination(FALSE) 17");
			m_adjustDestinations = false;
			m_checkForPath = false;
		}
	}

	if (AIInternalMoveToState::update() != STATE_CONTINUE)
	{
		m_desperateAttackDone = true;
		if (ai)
			((Rva0026F110 *)ai)->set();
	}

	UnsignedInt damageSource;
	if (source->bfmeGetRecentDamageSource(&damageSource, 4) == true)
	{
		const ThingTemplate *tmpl = source->getTemplate();
		if (tmpl)
		{
			const AudioEventRTS *event;
			{
				AsciiString soundName("VoiceDesperateAttack");
				event = tmpl->getPerUnitSound(soundName);
			}
			if (event)
			{
				AudioEventRTS sound(*event);
				sound.setObjectID(source->getID());
				if (source->m_team && source->m_team->bfmeGetControllingPlayer())
					sound.setPlayerIndex(source->m_team->bfmeGetControllingPlayer()->getPlayerIndex());
				(*(AudioManager **)0x012ED668)->addAudioEvent(&sound);
			}
		}
		return STATE_SUCCESS;
	}

	return STATE_CONTINUE;
}
