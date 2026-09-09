// ?groupIdle@AIGroup@@QAEXH@Z
// partial score=0.86 date=2026-09-09
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupIdle, retail 0x00155B90, 414 bytes.
//
// The retail body is the BFME command-source idle walk, not the similarly
// named Player or AIPlayer helpers.  Its list is the STLport sentinel at
// AIGroup+0x04; the member object is the node payload at +0x08.  The named
// GameLogicDispatch and ScriptActions callers use this same AIGroup method.
// The callback passed to contained buildings is the already matched
// bfmeGoBUA body at 0x00155B60 (ILT 0x0000894A), so this TU only declares it.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_0003add7();

static NameKeyType nameKeyViaIlt( const char *name )
{
	typedef NameKeyType (NameKeyGenerator::*NameKeyCall)( const char * );
	union
	{
		void *asVoid;
		NameKeyCall asMember;
	} nameKeyCast;
	nameKeyCast.asVoid = (void *)j_0003add7;
	return (TheNameKeyGenerator->*nameKeyCast.asMember)( name );
}

#define NAMEKEY(name) nameKeyViaIlt(name)

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unreconstructed_000[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue( int low, int high, const char *file, int line );

class AIUpdateModuleData
{
public:
	char m_unreconstructed_000[0x20];
	UnsignedInt m_autoAcquireEnemiesWhenIdle;
};

class AICommandInterface
{
public:
	void aiIdle( CommandSourceType commandSource );
};

extern void j_00024d70();

static void aiIdleViaIlt( AICommandInterface *commands, CommandSourceType commandSource )
{
	typedef void (AICommandInterface::*AIIdleCall)( CommandSourceType );
	union
	{
		void *asVoid;
		AIIdleCall asMember;
	} aiIdleCast;
	aiIdleCast.asVoid = (void *)j_00024d70;
	(commands->*aiIdleCast.asMember)( commandSource );
}

// The BFME AIUpdateInterface has its module-data pointer at +0x04, the
// AICommandInterface secondary surface at +0x20, and the player-idle marker at
// +0x33A.  The latter is independently laid out by aiDoCommand's converted
// sibling in AIUpdateInterfaceCommandDispatch.cpp.
class AIUpdateInterface
{
public:
	char m_unreconstructed_000[4];
	AIUpdateModuleData *m_moduleData;
	char m_unreconstructed_008[0x20 - 0x08];
	AICommandInterface m_commands;
	char m_unreconstructed_021[0x33A - 0x21];
	unsigned char m_field33a;

	Bool canAutoAcquire() const
	{
		return m_moduleData->m_autoAcquireEnemiesWhenIdle != 0;
	}

	Bool canAutoAcquireWhileStealthed() const
	{
		return m_moduleData->m_autoAcquireEnemiesWhenIdle & 0x02;
	}
};

extern void j_00006ece();

static void setNextMoodCheckTimeViaIlt( AIUpdateInterface *ai, UnsignedInt frame )
{
	typedef void (AIUpdateInterface::*SetMoodFrameCall)( UnsignedInt );
	union
	{
		void *asVoid;
		SetMoodFrameCall asMember;
	} setMoodFrameCast;
	setMoodFrameCast.asVoid = (void *)j_00006ece;
	(ai->*setMoodFrameCast.asMember)( frame );
}

class StealthUpdateModuleData
{
public:
	char m_unreconstructed_000[8];
	UnsignedInt m_stealthDelay;
};

class StealthUpdate
{
public:
	char m_unreconstructed_000[4];
	StealthUpdateModuleData *m_moduleData;

	UnsignedInt getStealthDelay() const
	{
		return m_moduleData->m_stealthDelay;
	}
};

struct BfmeOwnerBUA;
extern void bfmeGoBUA( BfmeOwnerBUA *owner, void **what );

typedef void (*ContainIterateFunc)( BfmeOwnerBUA *owner, void **what );

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void iterateContained( ContainIterateFunc func, void *userData, Bool reverse );
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void orderSlavesToGoIdle( CommandSourceType commandSource );
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	UnsignedInt getStatusBits() const { return m_statusBits; }
	ContainModuleInterface *getContain() const { return m_contain; }
	StealthUpdate *findUpdateModule( NameKeyType key );
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;

private:
	char m_unreconstructed_000[0x90];
	UnsignedInt m_statusBits;
	char m_unreconstructed_094[0x1FC - 0x94];
	ContainModuleInterface *m_contain;
	char m_unreconstructed_200[4];
	AIUpdateInterface *m_ai;
};

extern void j_00044201();

static SpawnBehaviorInterface *getSpawnBehaviorInterfaceViaIlt( const Object *obj )
{
	typedef SpawnBehaviorInterface *(Object::*GetSpawnBehaviorCall)() const;
	union
	{
		void *asVoid;
		GetSpawnBehaviorCall asMember;
	} getSpawnBehaviorCast;
	getSpawnBehaviorCast.asVoid = (void *)j_00044201;
	return (obj->*getSpawnBehaviorCast.asMember)();
}

enum
{
	OBJECT_STATUS_STEALTHED = 0x00008000,
	OBJECT_STATUS_DETECTED = 0x00020000,
	OBJECT_STATUS_CAN_STEALTH = 0x00040000
};

#define BitTest(value, mask) (((value) & (mask)) != 0)

class AIGroup
{
public:
	void groupIdle( Int commandSource );

private:
	char m_unreconstructed_000[4];
	std::list<Object *> m_memberList;
};

void AIGroup::groupIdle( Int cmdSource )
{
	std::list<Object *>::iterator i;
	for ( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *obj = *i;
		if ( obj == 0 )
			continue;

		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if ( ai )
		{
			aiIdleViaIlt( &ai->m_commands, (CommandSourceType)cmdSource );

			if ( cmdSource == CMD_FROM_PLAYER )
				ai->m_field33a = 1;

			if ( cmdSource == CMD_FROM_PLAYER &&
				BitTest( obj->getStatusBits(), OBJECT_STATUS_CAN_STEALTH ) &&
				ai->canAutoAcquire() )
			{
				if ( !BitTest( obj->getStatusBits(), OBJECT_STATUS_STEALTHED ) &&
					!BitTest( obj->getStatusBits(), OBJECT_STATUS_DETECTED ) )
				{
					if ( !ai->canAutoAcquireWhileStealthed() )
					{
						static NameKeyType key_StealthUpdate = NAMEKEY( "StealthUpdate" );
						StealthUpdate *stealth = (StealthUpdate *)obj->findUpdateModule( key_StealthUpdate );
						if ( stealth )
						{
							UnsignedInt stealthFrames = stealth->getStealthDelay();
							UnsignedInt randomFrames = GetGameLogicRandomValue(
								0, 5,
								"F:\\bfme\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIGroup.cpp",
								0x951 );
							setNextMoodCheckTimeViaIlt(
								ai, TheGameLogic->getFrame() + stealthFrames + randomFrames );
						}
					}
				}
			}
		}
		else
		{
			ContainModuleInterface *contain = obj->getContain();
			if ( contain )
				contain->iterateContained( bfmeGoBUA, (void *)&cmdSource, true );
		}

		SpawnBehaviorInterface *spawnInterface = getSpawnBehaviorInterfaceViaIlt( obj );
		if ( spawnInterface )
			spawnInterface->orderSlavesToGoIdle( (CommandSourceType)cmdSource );
	}
}
