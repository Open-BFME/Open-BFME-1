// cl: /DNDEBUG /MD /EHsc
// AIChargeTargetState::onEnter, retail RVA 0x0017ECB0.
// The state vtable at 0x00C9AE70 names this class through its adjacent
// literal, and slot +0x10 resolves to the retail body converted here.

typedef unsigned int AudioHandle;
typedef unsigned int ObjectID;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
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
	AudioEventRTS(const AudioEventRTS &source); // ILT 0x00047B27
	~AudioEventRTS();                            // ILT 0x00026F35

	void setObjectID(ObjectID id);              // ILT 0x00019A6A
	void setPlayerIndex(int index);              // ILT 0x0003AC88

private:
	unsigned char m_unmodelled[0x70];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;
};

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:?setObjectID@AudioEventRTS@@QAEXI@Z=?j_00019a6a@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPlayerIndex@AudioEventRTS@@QAEXH@Z=?j_0003ac88@@YAXXZ")
#pragma comment(linker, "/alternatename:?getPerUnitSound@ThingTemplate@@QBEPBVAudioEventRTS@@ABVAsciiString@@@Z=?j_0000fd44@@YAXXZ")

class Player
{
public:
	int getPlayerIndex() const
	{
		return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x24);
	}
};

class AIUpdateInterface;

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

	void setWeaponLock(int weaponSlot, int lockType); // ILT 0x0003EEBE
	Player *getControllingPlayer() const;             // ILT 0x00020824

	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const unsigned char *>(this) + 0x74);
	}

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const unsigned char *>(this) + 0x38);
	}

	AIUpdateInterface *getAI() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(reinterpret_cast<const unsigned char *>(this) + 0x204);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject(); // ILT 0x0000E570

	unsigned char m_unmodelled[0x10];
	Object *m_owner;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

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
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event) = 0; // vtable +0x44
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ=?j_00021e27@@YAXXZ")

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class AIChargeTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	unsigned char m_statePrefix[0x18];
	StateMachine *m_machine;
	unsigned char m_goalPrefix[0x04];
	Coord3D m_goalPosition;
	unsigned char m_moveFields[0x1c];
	bool m_adjustDestinations;
};

// ?onEnter@AIChargeTargetState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIChargeTargetState::onEnter()
{
	StateMachine *machine = m_machine;
	Object *source = machine->m_owner;
	AIUpdateInterface *ai = source->getAI();
	Object *victim = machine->getGoalObject();
	if (!ai || !victim)
		return STATE_FAILURE;

	{
		m_adjustDestinations = false;
		m_goalPosition = *victim->getPosition();
		source->setWeaponLock(0, 1);

		if (source->getTemplate())
		{
			const AudioEventRTS *event;
			{
				AsciiString soundName("VoiceStartCharging");
				event = source->getTemplate()->getPerUnitSound(soundName);
			}
			if (event)
			{
				AudioEventRTS sound(*event);
				sound.setObjectID(source->getID());
				if (source->getControllingPlayer())
					sound.setPlayerIndex(source->getControllingPlayer()->getPlayerIndex());
				(*reinterpret_cast<AudioManager **>(0x012ED668))->addAudioEvent(&sound);
			}
		}
	}

	return AIInternalMoveToState::onEnter();
}
