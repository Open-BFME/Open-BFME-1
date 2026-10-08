// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Identity and ABI: targets/game/reverse/identity_evidence/002b5cc0-update.md.

#include <vector>
#include "ascii_string.h"
#include "../../../command_source_type.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Weapon;
enum WeaponSlotType;
class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum AICommandType
{
	AICMD_NO_COMMAND = -1,
	AICMD_MOVE_TO_POSITION = 0x00
};

struct DamageInfo
{
	char m_bfme_body[0x5C];
};

struct AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType commandSource );
	~AICommandParms();

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const Team *m_team;
	std::vector<Coord3D> m_coords;
	const Waypoint *m_waypoint;
	const PolygonTrigger *m_polygon;
	int m_intValue;
	DamageInfo m_damage;
	const CommandButton *m_commandButton;
	Path *m_path;
};

class AICommandParmsStorage
{
public:
	void reconstitute( AICommandParms &parms ) const;
	unsigned char m_payload[0xa0];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
	void aiIdle( CommandSourceType cmdSource );
	void aiAttackObject(Object *target, int maxShots, CommandSourceType cmdSource);
};

template <int N> class BitFlags
{
	unsigned int m_bits[ ( N + 31 ) / 32 ];
};
typedef BitFlags<320> ModelConditionFlags;

class Rva00170C70BitSet : public ModelConditionFlags
{
public:
	Rva00170C70BitSet( void *init, unsigned int bit );
};
class BfmeI1166 : public ModelConditionFlags
{
public:
	BfmeI1166( int init, unsigned int bit1, unsigned int bit2 );
};

enum ModelConditionFlagType
{
	MODELCONDITION_PACKING = 0x5D,
	MODELCONDITION_UNPACKING = 0x5F,
	MODELCONDITION_DEPLOYED = 0x63
};

typedef Int ObjectID;

class AudioEventRTS
{
public:
	AudioEventRTS( const AudioEventRTS &that );
	~AudioEventRTS();
	void setObjectID( UnsignedInt objID );
	void *m_vptr;
	char m_payload[0x6c];
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40();
	virtual UnsignedInt addAudioEvent( const AudioEventRTS *eventToAdd );
};
extern AudioManager *TheAudio;

#include "../../../../Common/Thing/GameLogicObjectLookup.h"
struct Rva002B5CC0GameLogicFrame
{
	char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheBfmeGameLogic;
#define TheGameLogic TheBfmeGameLogic

class Drawable
{
public:
	void setAnimationLoopDuration( UnsignedInt numFrames );
	const AudioEventRTS *getPerUnitSound( const AsciiString &soundName ) const;
};

class Object
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual Drawable *getDrawable() const;

	ObjectID getID() const { return m_id; }
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);
	const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this)+0x38); }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	void clearAndSetModelConditionFlags( const ModelConditionFlags &clr, const ModelConditionFlags &set );
	void clearModelConditionFlags( const ModelConditionFlags &clr );

	char m_unmodelled_004[0x74 - 4];
	ObjectID m_id;
	char m_afterID[0x344 - 0x78];
	unsigned int m_privateStatus;
};

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_MAIN = 0
};

class ModuleData;
class DeployStyleAIUpdateModuleData
{
public:
	char m_unmodelled_000[0x64];
	UnsignedInt m_unpackTime;
	UnsignedInt m_packTime;
	Bool m_resetTurretBeforePacking;
	Bool m_turretsFunctionOnlyWhenDeployed;
	Bool m_turretsMustCenterBeforePacking;
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
#define UPDATE_SLEEP(n) ((UpdateSleepTime)(n))
class Rva002B5CC0UpdateInterface
{
public:
	virtual UpdateSleepTime update()=0;
	virtual unsigned int getDisabledTypesToProcess() const=0;
	unsigned int m_field14, m_field18, m_field1c;
};
class StateMachine
{
public:
	Object *getGoalObject();
};
struct BfmeThing960
{
	int getResult(int index);
};
class Weapon
{
public:
	Bool isGoalPosWithinAttackRange(const Object *source, const Coord3D *goal, const Object *target, const Coord3D *targetPos, float extra) const;
	Bool isWithinAttackRange(const Object *source, const Object *target, int extra=0) const;
};
class UpdateModuleBase
{
public:
	virtual ~UpdateModuleBase();
	const ModuleData *m_moduleData;
	Object *m_object;
	void *m_field0c;
};

class AIUpdateInterface : public UpdateModuleBase, public Rva002B5CC0UpdateInterface, public AICommandInterface
{
public:
	Object *getObject() const { return m_object; }
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretEnabled( WhichTurretType tur, Bool enabled );
	void recenterTurret( WhichTurretType tur );
	Bool isTurretInNaturalPosition(WhichTurretType tur) const;
	Object *getNextMoodTarget(Bool force, Bool hunt);
	Bool bfmeBlocksFormationRefresh();
	virtual UpdateSleepTime update();
	Object *getTurretTargetObject(WhichTurretType tur) { return reinterpret_cast<Object *>(reinterpret_cast<BfmeThing960 *>(this)->getResult(tur)); }
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
	Bool isMoving() { return bfmeBlocksFormationRefresh(); }
	Bool isWaitingForPath() const { return m_waitingForPath; }
	void *getPath() const { return m_path; }
	char m_unmodelled_024[0x30 - 0x24];
	StateMachine *m_stateMachine;
	char m_unmodelled_034[0x140 - 0x34];
	void *m_path;
	char m_unmodelled_144[0x31e - 0x144];
	Bool m_waitingForPath;
	char m_unmodelled_31f[0x340 - 0x31f];
};

enum DeployStateTypes
{
	READY_TO_MOVE,
	DEPLOY,
	READY_TO_ATTACK,
	UNDEPLOY,
	ALIGNING_TURRETS
};

class DeployStyleAIUpdate : public AIUpdateInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms );
	virtual UpdateSleepTime update();

	UnsignedInt getUnpackTime() const { return getDeployStyleAIUpdateModuleData()->m_unpackTime; }
	UnsignedInt getPackTime() const { return getDeployStyleAIUpdateModuleData()->m_packTime; }
	Bool doTurretsHaveToCenterBeforePacking() const { return getDeployStyleAIUpdateModuleData()->m_turretsMustCenterBeforePacking; }
	Bool doTurretsFunctionOnlyWhenDeployed() const { return getDeployStyleAIUpdateModuleData()->m_turretsFunctionOnlyWhenDeployed; }
	const DeployStyleAIUpdateModuleData *getDeployStyleAIUpdateModuleData() const
	{
		return (const DeployStyleAIUpdateModuleData *)m_moduleData;
	}

private:
	void setMyState( DeployStateTypes stateID );

	AICommandParmsStorage m_lastOutsideCommand;
	Bool m_hasOutsideCommand;
	DeployStateTypes m_state;
	UnsignedInt m_frameToWakeForDeploy;
	UnsignedInt m_designatedTargetID;
	UnsignedInt m_attackObjectID;
	Coord3D m_position;
	Bool m_isAttackMultiple;
	Bool m_isAttackObject;
	Bool m_isAttackPosition;
	Bool m_isGuardingPosition;
	Bool m_overriddenAttack;
};

// The visible state transition preserves retail inlining and the empty EH states.
// ?setMyState@DeployStyleAIUpdate@@AAEXW4DeployStateTypes@@@Z
inline void DeployStyleAIUpdate::setMyState( DeployStateTypes stateID )
{
	m_state = stateID;
	Object *self = getObject();
	Drawable *draw = self->getDrawable();
	switch( stateID )
	{
		case DEPLOY:
		{
			aiIdle( CMD_FROM_AI );
			self->clearAndSetModelConditionFlags( Rva00170C70BitSet( 0, MODELCONDITION_PACKING ),
				Rva00170C70BitSet( 0, MODELCONDITION_UNPACKING ) );
			m_frameToWakeForDeploy = getUnpackTime();
			if( draw )
			{
				draw->setAnimationLoopDuration( m_frameToWakeForDeploy );
				const AudioEventRTS *soundToPlayPtr = draw->getPerUnitSound( "Deploy" );
				if( soundToPlayPtr )
				{
					AudioEventRTS soundToPlay = *soundToPlayPtr;
					soundToPlay.setObjectID( self->getID() );
					TheAudio->addAudioEvent( &soundToPlay );
				}
			}
			m_frameToWakeForDeploy += reinterpret_cast<const Rva002B5CC0GameLogicFrame *>(TheGameLogic)->m_frame;
			break;
		}
		case UNDEPLOY:
		{
			aiIdle( CMD_FROM_AI );
			self->clearAndSetModelConditionFlags( BfmeI1166( 0, MODELCONDITION_UNPACKING, MODELCONDITION_DEPLOYED ),
				Rva00170C70BitSet( 0, MODELCONDITION_PACKING ) );
			m_frameToWakeForDeploy = getPackTime();
			if( draw )
			{
				draw->setAnimationLoopDuration( m_frameToWakeForDeploy );
				const AudioEventRTS *soundToPlayPtr = draw->getPerUnitSound( "Undeploy" );
				if( soundToPlayPtr )
				{
					AudioEventRTS soundToPlay = *soundToPlayPtr;
					soundToPlay.setObjectID( self->getID() );
					TheAudio->addAudioEvent( &soundToPlay );
				}
			}
			m_frameToWakeForDeploy += reinterpret_cast<const Rva002B5CC0GameLogicFrame *>(TheGameLogic)->m_frame;

			if( doTurretsFunctionOnlyWhenDeployed() )
			{
				WhichTurretType tur = getWhichTurretForCurWeapon();
				if( tur != TURRET_INVALID )
					setTurretEnabled( tur, false );
			}
			break;
		}
		case READY_TO_MOVE:
		{
			m_frameToWakeForDeploy = 0;
			if( m_hasOutsideCommand )
			{
				AICommandParms parms( AICMD_NO_COMMAND, CMD_FROM_AI );
				m_lastOutsideCommand.reconstitute( parms );
				aiDoCommand( &parms );
			}
			self->clearModelConditionFlags( Rva00170C70BitSet( 0, MODELCONDITION_PACKING ) );
			break;
		}
		case READY_TO_ATTACK:
		{
			m_frameToWakeForDeploy = 0;
			if( !m_isAttackMultiple && m_hasOutsideCommand )
			{
				AICommandParms parms( AICMD_NO_COMMAND, CMD_FROM_AI );
				m_lastOutsideCommand.reconstitute( parms );
				aiDoCommand( &parms );
			}
			self->clearAndSetModelConditionFlags( Rva00170C70BitSet( 0, MODELCONDITION_UNPACKING ),
				Rva00170C70BitSet( 0, MODELCONDITION_DEPLOYED ) );
			if( doTurretsFunctionOnlyWhenDeployed() )
			{
				WhichTurretType tur = getWhichTurretForCurWeapon();
				if( tur != TURRET_INVALID )
					setTurretEnabled( tur, true );
			}
			break;
		}
		case ALIGNING_TURRETS:
		{
			m_frameToWakeForDeploy = 0;
			WhichTurretType tur = getWhichTurretForCurWeapon();
			if( tur != TURRET_INVALID )
				recenterTurret( tur );
			break;
		}
	}
}

// ?update@DeployStyleAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DeployStyleAIUpdate::update( void )
{
	Object *self = getObject();
	Weapon *weapon = self->getCurrentWeapon();
	Bool inRange = false;
	Object *designatedTarget = 0;
	Bool isAttacking = false;
	if( weapon )
	{
		if( m_isAttackPosition )
		{
			inRange = weapon->isGoalPosWithinAttackRange( self, self->getPosition(), 0, &m_position, 0.0f );
			isAttacking = true;
		}
		else if( m_isAttackObject )
		{
			designatedTarget = TheGameLogic->findObjectByID( m_attackObjectID );
			if( designatedTarget && designatedTarget->isEffectivelyDead() )
			{
				designatedTarget = 0;
			}
			if( designatedTarget )
			{
				inRange = weapon->isWithinAttackRange( self, designatedTarget );
				isAttacking = true;
			}
		}
		else if( m_isAttackMultiple )
		{
			Bool newTarget = false;

			WhichTurretType tur = getWhichTurretForCurWeapon();
			if( tur != TURRET_INVALID )
			{
				designatedTarget = getTurretTargetObject( tur );
			}
			else
			{
				designatedTarget = getGoalObject();
			}
			if( !designatedTarget )
			{
				designatedTarget = TheGameLogic->findObjectByID( m_designatedTargetID );
			}
			if( designatedTarget && designatedTarget->isEffectivelyDead() )
			{
				designatedTarget = getNextMoodTarget( true, false );
				newTarget = true;
			}
			if( !designatedTarget && m_isGuardingPosition )
			{
				designatedTarget = getNextMoodTarget( false, false );
				if( designatedTarget )
				{
					inRange = weapon->isWithinAttackRange( self, designatedTarget );
					isAttacking = true;
					if( inRange )
					{
						aiAttackObject( designatedTarget, 0x7fffffff, CMD_FROM_AI );
						m_overriddenAttack = true;
						m_designatedTargetID = designatedTarget->getID();
					}
					else
					{
						designatedTarget = 0;
					}
				}
				else
				{
					designatedTarget = 0;
				}
			}
			else if( designatedTarget )
			{
				inRange = weapon->isWithinAttackRange( self, designatedTarget );
				isAttacking = true;
				m_designatedTargetID = designatedTarget->getID();
				if( m_overriddenAttack && newTarget && inRange )
				{
					aiAttackObject( designatedTarget, 0x7fffffff, CMD_FROM_AI );
				}
			}
			else
			{
				m_designatedTargetID = 0;
			}
		}
	}
	Bool remainDeployed = m_isGuardingPosition && !designatedTarget && !isMoving() && !isWaitingForPath();
	UnsignedInt now = reinterpret_cast<const Rva002B5CC0GameLogicFrame *>(TheGameLogic)->m_frame;
	switch( m_state )
	{
		case READY_TO_MOVE:
			if( remainDeployed || (inRange && isAttacking) )
			{
				setMyState( DEPLOY );
			}
			break;
		case READY_TO_ATTACK:
			if( !remainDeployed && (!inRange && isAttacking || !isAttacking && (isWaitingForPath() || getPath())) )
			{
				WhichTurretType tur = getWhichTurretForCurWeapon();
				if( tur != TURRET_INVALID )
				{
					if( doTurretsHaveToCenterBeforePacking() )
					{
						setMyState( ALIGNING_TURRETS );
						break;
					}
				}
				setMyState( UNDEPLOY );
			}
			else if( !designatedTarget && m_overriddenAttack && m_hasOutsideCommand )
			{

				AICommandParms parms( AICMD_NO_COMMAND, CMD_FROM_AI );
				m_lastOutsideCommand.reconstitute( parms );
 				aiDoCommand(&parms);
			}
			break;
		case DEPLOY:
			if( m_frameToWakeForDeploy != 0 && now >= m_frameToWakeForDeploy)
			{
				setMyState( READY_TO_ATTACK );
				if( m_isAttackMultiple && inRange && isAttacking && designatedTarget )
				{
					aiAttackObject( designatedTarget, 0x7fffffff, CMD_FROM_AI );
					m_overriddenAttack = true;
				}
			}
			break;
		case UNDEPLOY:
			if( m_frameToWakeForDeploy != 0 && now >= m_frameToWakeForDeploy)
			{
				setMyState( READY_TO_MOVE );
			}
			break;
		case ALIGNING_TURRETS:
		{
			WhichTurretType tur = getWhichTurretForCurWeapon();
			if( tur != TURRET_INVALID )
			{
				if( isTurretInNaturalPosition( tur ) )
				{
					setMyState( UNDEPLOY );
				}
			}
			break;
		}
	}
	UpdateSleepTime mine = UPDATE_SLEEP_FOREVER;
	switch( m_state )
	{
		case READY_TO_ATTACK:
		case READY_TO_MOVE:
			mine = UPDATE_SLEEP_FOREVER;
			break;
		case DEPLOY:
		case UNDEPLOY:
			mine = m_frameToWakeForDeploy > now ? UPDATE_SLEEP(m_frameToWakeForDeploy - now) : UPDATE_SLEEP_NONE;
			aiIdle( CMD_FROM_AI );
			break;
		case ALIGNING_TURRETS:
			mine = UPDATE_SLEEP_NONE;
			aiIdle( CMD_FROM_AI );
			break;
	}
	UpdateSleepTime ret = AIUpdateInterface::update();
	return (mine < ret) ? mine : ret;
}
