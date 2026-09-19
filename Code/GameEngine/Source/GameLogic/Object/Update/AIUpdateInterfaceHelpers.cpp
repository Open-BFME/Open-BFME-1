// cl: /DNDEBUG /MD /EHsc
// readable body of ?setGoalPositionClipped@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body of ?getLastCommandSource@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Open-BFME: the AIUpdateInterface members that compile with exceptions on --
// the goal and path helpers the command handlers call into, the two small
// queries, and the one private command handler that lives on this side of the
// flag line.
//
//   ?getCurLocomotorSpeed@   0x0026EC30,  29 bytes
//   ?setQueueForPathTime@    0x0026ECA0,  83 bytes
//   ?computeQuickPath@       0x002712D0, 154 bytes
//   ?setGoalPositionClipped@ 0x00273DE0, 334 bytes
//   ?privateGetHealed@       0x0027DE10,  50 bytes
//   ?getLastCommandSource@   0x0027F460,   4 bytes
//   ?notifyVictimIsDead@     0x0027F470,   1 byte
//
// Five files' worth of AIUpdateInterface, and each described a different class.
// Two of them (privateGetHealed, setQueueForPathTime) had the real shape:
// AIUpdateInterface derives from UpdateModule and AICommandInterface in that
// order, which is why `lea ecx,[esi+0x20]` reaches aiEnter -- UpdateModule is
// exactly 0x20 bytes wide, so the second base starts there and the class's own
// fields start at +0x24. The other three declared a flat class with the vptr
// and then counted from +0x04, which lands every field on the same absolute
// offset by accident of arithmetic and says nothing about where the bases are.
// One layout below, with the bases named.
//
// computeQuickPath's BfmeVirtualSlots<122> is what pins setLocomotorGoalNone to
// its retail vtable slot, so it is declared first and UpdateModule contributes
// no virtual of its own; the rest of the virtuals here are past it and their
// slots are not evidence of anything.
//
// The pointer at +0x1CC is the one real disagreement, and it is a union rather
// than a mistake. setGoalPositionClipped reads it as a Locomotor and asks it for
// the preferred height at +0x44; getCurLocomotorSpeed reads it as another
// AIUpdateInterface and asks that for a formation movement speed, handing it the
// same m_object. The second is the weaker account -- but the class a callee is
// spelled on is part of its mangled name, so respelling it would repoint the
// call. Both spellings stay, on one word, until a caller settles it. (The
// exceptions-off command handlers in AIUpdateInterfacePrivateCommands.cpp read
// the same word a third way, as an opaque object they call set() on with
// m_object as the argument.)
//
// One more offset lands twice here: computeQuickPath's m_isBlockedAndStuck at
// +0x326 is the same byte the command handlers clear on every order.

typedef bool Bool;
typedef float Real;

#pragma warning(disable : 4716)

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

template <class T>
inline const T &max( const T &left, const T &right )
{
	return left > right ? left : right;
}

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum KindOfType
{
	KINDOF_AIRCRAFT = 0x0C
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID	= 0,
	UPDATE_SLEEP_NONE		= 1,				// retail: cmp edi,1 / jl
	UPDATE_SLEEP_FOREVER	= 0x3fffffff
};

#define UPDATE_SLEEP(numFrames)				((UpdateSleepTime)(numFrames))

extern "C" const float g_zeroLocomotorSpeed;

extern void __cdecl operator delete(void *block);
extern void j_0000ca68();
extern void j_0001e6fa();
extern void j_00025d56();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool bfmeIsKindOf( KindOfType type ) const;
	Bool isSignificantlyAboveTerrain() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	Real getPreferredHeight() const { return m_preferredHeight; }

private:
	unsigned char m_unmodelled_00[ 0x44 ];
	Real m_preferredHeight;						// Locomotor+0x44
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	void bfmeSetGoalPosition( const Coord3D *position );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
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
	virtual void getExtent( Region3D *extent );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled_00[ 0x1BC ];
	Real m_partitionCellSize;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	bool canGetHealedAt( const Object *obj, const Object *healDepot, CommandSourceType cmdSource );	///< ILT 0x0001B090
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame( void ) const { return m_frame; }

private:
	char m_unreconstructed_00[0x3c];
	unsigned int m_frame;						///< retail this+0x3c
};

class Path
{
public:
	~Path();
};

class Pathfinder
{
public:
	void removeGoal(Object *object);
	Path *getAircraftPath(const Object *object, const Coord3D *destination);
};

class AI
{
public:
	char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;
extern ActionManager *TheActionManager;			///< retail 0x012ED700
extern GameLogic *TheGameLogic;					///< retail 0x012F0898
extern AI *TheAI;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiEnter( Object *obj, CommandSourceType cmdSource );	///< ILT 0x000442A1

private:
	char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BfmeVirtualSlots<122>
{
public:
	Object *getObject( void ) const { return m_obj; }

protected:
	UpdateSleepTime getWakeFrame( void ) const;								///< ILT 0x000176C5
	void setWakeFrame( Object *obj, UpdateSleepTime whenToWakeUp );			///< ILT 0x000157DA -> 0x002B2040

	char m_unreconstructed_04[4];
	Object *m_obj;								///< retail this+0x08
	char m_unreconstructed_0c[0x20 - 0x0c];		///< brings UpdateModule to 0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	virtual void setLocomotorGoalNone() = 0;	///< vtable slot 122
	virtual CommandSourceType getLastCommandSource() const;
	virtual void notifyVictimIsDead();

	Bool computeQuickPath( const Coord3D *destination );
	Real getCurLocomotorSpeed();
	Real getFormationMovementSpeed( Object *object );
	void setQueueForPathTime( int frames );
	void setGoalPositionClipped( const Coord3D *position, CommandSourceType cmdSource );

protected:
	virtual void privateGetHealed( Object *healDepot, CommandSourceType cmdSource );

	// The class's own fields, past UpdateModule (0x20) and AICommandInterface (4).
	char m_unmodelled_24[0x30 - 0x24];
	StateMachine *m_stateMachine;				// +0x30
	char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;		// +0x48
	char m_unmodelled_4C[0x140 - 0x4C];
	Path *m_path;								// +0x140
	char m_unmodelled_144[0x17C - 0x144];
	int m_queueForPathFrame;					// +0x17C
	char m_unmodelled_180[0x1CC - 0x180];

	// One word, two accounts -- see the note at the top of this file.
	union
	{
		Locomotor *m_curLocomotor;				// +0x1CC, setGoalPositionClipped
		AIUpdateInterface *m_locomotorController;	// +0x1CC, getCurLocomotorSpeed
	};

	char m_unmodelled_1D0[0x1D8 - 0x1D0];
	int m_locomotorGoalType;					// +0x1D8
	Coord3D m_locomotorGoalData;				// +0x1DC
	char m_unmodelled_1E8[0x31E - 0x1E8];
	unsigned char m_waitingForPath;				// +0x31E
	unsigned char m_isAttackPath;				// +0x31F
	char m_unmodelled_320[0x326 - 0x320];
	unsigned char m_isBlockedAndStuck;			// +0x326
	char m_unmodelled_327[0x330 - 0x327];
	bool m_isInUpdate;							// +0x330
};

// ?getCurLocomotorSpeed@AIUpdateInterface@@QAEMXZ
Real AIUpdateInterface::getCurLocomotorSpeed()
{
	if (m_locomotorController != 0)
		return m_locomotorController->getFormationMovementSpeed(getObject());

	return g_zeroLocomotorSpeed;
}

// ?setQueueForPathTime@AIUpdateInterface@@QAEXH@Z
// The Zero Hour body unchanged, with SLEEPY_AI on. It is here rather than in
// AIUpdate.cpp -- which carries the real body and 34 matched rows -- because
// that TU compiles it to within two operands of retail and both are class
// offsets its shim gets wrong: m_isInUpdate lands at +0x216 instead of +0x330,
// and getObject() reads +0x0c instead of +0x08. Correcting either means editing
// reference/shims/aiupdatelayout, which is compiled into that whole TU.
void AIUpdateInterface::setQueueForPathTime( int frames )
{
	if (frames >= UPDATE_SLEEP_NONE && getWakeFrame() > UPDATE_SLEEP(frames))
	{
		if (m_isInUpdate)
		{
			// we're changing this while in our own update (probably via a move state).
			// just do nothing, since update will calculate the correct sleep behavior at the end.
		}
		else
		{
			setWakeFrame(getObject(), UPDATE_SLEEP(frames));
		}
	}
	m_queueForPathFrame = frames ? (TheGameLogic->getFrame() + frames) : 0;
}

// ?computeQuickPath@AIUpdateInterface@@QAE_NPBUCoord3D@@@Z
// Retail falls out of the function without setting a return value, which is
// what the disabled 4716 above is for.
Bool AIUpdateInterface::computeQuickPath(const Coord3D *destination)
{
	Object *object = getObject();

	typedef void (Pathfinder::*RemoveGoalCall)(Object *);
	union
	{
		void *asVoid;
		RemoveGoalCall asMember;
	} removeGoalCast;
	removeGoalCast.asVoid = (void *)j_00025d56;
	(TheAI->m_pathfinder->*removeGoalCast.asMember)(object);

	Path *oldPath = m_path;
	if (oldPath != 0)
	{
		typedef void (Path::*DestroyCall)();
		union
		{
			void *asVoid;
			DestroyCall asMember;
		} destroyCast;
		destroyCast.asVoid = (void *)j_0000ca68;
		(oldPath->*destroyCast.asMember)();
		operator delete(oldPath);
	}

	m_path = 0;
	m_waitingForPath = false;
	m_isBlockedAndStuck = false;
	m_isAttackPath = false;
	setLocomotorGoalNone();

	typedef Path *(Pathfinder::*GetAircraftPathCall)(const Object *, const Coord3D *);
	union
	{
		void *asVoid;
		GetAircraftPathCall asMember;
	} getAircraftPathCast;
	getAircraftPathCast.asVoid = (void *)j_0001e6fa;
	m_path = (TheAI->m_pathfinder->*getAircraftPathCast.asMember)(object, destination);
	if (m_path != 0)
	{
		m_locomotorGoalType = 4;
		m_locomotorGoalData = *destination;
	}
}

// ?setGoalPositionClipped@AIUpdateInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
void AIUpdateInterface::setGoalPositionClipped( const Coord3D *position, CommandSourceType cmdSource )
{
	if( position )
	{
		Coord3D clipped = *position;
		if( cmdSource == CMD_FROM_PLAYER )
		{
			Real fudge = TheWritableGlobalData->m_partitionCellSize * 0.5f;
			Object *object = getObject();
			if( object->bfmeIsKindOf( KINDOF_AIRCRAFT ) &&
				object->isSignificantlyAboveTerrain() && m_curLocomotor )
			{
				fudge = max( fudge, m_curLocomotor->getPreferredHeight() );
			}

			Region3D mapRegion;
			TheTerrainLogic->getExtent( &mapRegion );
			if( clipped.x < mapRegion.lo.x + fudge )
				clipped.x = mapRegion.lo.x + fudge;
			if( clipped.x > mapRegion.hi.x - fudge )
				clipped.x = mapRegion.hi.x - fudge;
			if( clipped.y < mapRegion.lo.y + fudge )
				clipped.y = mapRegion.lo.y + fudge;
			if( clipped.y > mapRegion.hi.y - fudge )
				clipped.y = mapRegion.hi.y - fudge;
		}
		m_stateMachine->bfmeSetGoalPosition( &clipped );
	}
	else
	{
		m_stateMachine->bfmeSetGoalPosition( 0 );
	}
}

// ?privateGetHealed@AIUpdateInterface@@MAEXPAVObject@@W4CommandSourceType@@@Z
// Get healed at the heal depot. The Zero Hour body unchanged, and the one
// private command handler compiled with exceptions on -- its eighteen siblings
// are in AIUpdateInterfacePrivateCommands.cpp under /MD alone.
//
// Callee pins, both resolved through their incremental-link thunks rather than
// taken on the packet's word:
//
//   0x0001B090 -> body 0x000C5140, canGetHealedAt. 185 bytes, and it sits in the
//     same block as 0x000C4240, which the sweep independently reads as
//     ActionManager::canFireWeaponAtLocation -- one compiland, one class.
//   0x000442A1 -> body 0x000D89C0, aiEnter. It reserves 0x9c of stack, pushes
//     0x17, calls a constructor on that buffer, stores the Object* argument into
//     it at +0x18, and then calls through vtable slot 0 -- which is
//     `AICommandParms parms(AICMD_ENTER, cmdSource); parms.m_obj = obj;
//     aiDoCommand(&parms);` and nothing else.
void AIUpdateInterface::privateGetHealed( Object *healDepot, CommandSourceType cmdSource )
{

  // sanity, if we can't get healed from here get outta here
	if( TheActionManager->canGetHealedAt( getObject(), healDepot, cmdSource ) == false )
		return;

	// enter the heal dest for healing
	aiEnter( healDepot, cmdSource );

}

// ?getLastCommandSource@AIUpdateInterface@@UBE?AW4CommandSourceType@@XZ
CommandSourceType AIUpdateInterface::getLastCommandSource() const
{
	return m_lastCommandSource;
}

// ?notifyVictimIsDead@AIUpdateInterface@@UAEXXZ
void AIUpdateInterface::notifyVictimIsDead()
{
}
