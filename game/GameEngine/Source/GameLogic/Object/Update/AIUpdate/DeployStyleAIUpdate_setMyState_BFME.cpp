// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// DeployStyleAIUpdate::setMyState(DeployStateTypes), retail RVA 0x002B5800
// (941 bytes; the five-entry jump table follows at 0x002B5BB0).  Identity: the
// Generals one-argument setMyState, case for case (DEPLOY, UNDEPLOY,
// READY_TO_MOVE, READY_TO_ATTACK, ALIGNING_TURRETS); thiscall ret 4 storing the
// state at +0x3E4, called twice from 0x002B5CC0 through its ILT.  BFME changes:
// the drawable is fetched once up front and plays the per-unit Deploy/Undeploy
// sound itself (Drawable::getPerUnitSound), and the restored command is built
// as AICommandParms(AICMD_NO_COMMAND, CMD_FROM_AI).  Module-data offsets are
// the name_oracle field_names witness; member offsets match the matched
// aiDoCommand at 0x002B5600 (storage +0x340, has-command +0x3E0, state +0x3E4).
#include <vector>
#include "ascii_string.h"
#include "../../../command_source_type.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
};

template <int N> class BitFlags
{
	unsigned int m_bits[ ( N + 31 ) / 32 ];
};
typedef BitFlags<320> ModelConditionFlags;

// Single- and two-bit model-condition mask constructors (ILTs 0x0003D424 and
// 0x00004048), under the names their bodies are ledgered with.
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

typedef UnsignedInt ObjectID;

class AudioEventRTS
{
public:
	AudioEventRTS( const AudioEventRTS &that );
	~AudioEventRTS();
	void setObjectID( ObjectID objID );
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

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

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
	void clearAndSetModelConditionFlags( const ModelConditionFlags &clr, const ModelConditionFlags &set );
	void clearModelConditionFlags( const ModelConditionFlags &clr );

	char m_unmodelled_004[0x74 - 4];
	ObjectID m_id;
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
};

class UpdateModuleBase
{
public:
	virtual ~UpdateModuleBase();
	const ModuleData *m_moduleData;
	Object *m_object;
	char m_unmodelled_00c[0x20 - 0xc];
};

class AIUpdateInterface : public UpdateModuleBase, public AICommandInterface
{
public:
	Object *getObject() const { return m_object; }
	WhichTurretType getWhichTurretForCurWeapon() const;
	void setTurretEnabled( WhichTurretType tur, Bool enabled );
	void recenterTurret( WhichTurretType tur );
	char m_unmodelled_024[0x340 - 0x24];
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

	UnsignedInt getUnpackTime() const { return getDeployStyleAIUpdateModuleData()->m_unpackTime; }
	UnsignedInt getPackTime() const { return getDeployStyleAIUpdateModuleData()->m_packTime; }
	Bool doTurretsFunctionOnlyWhenDeployed() const { return getDeployStyleAIUpdateModuleData()->m_turretsFunctionOnlyWhenDeployed; }
	const DeployStyleAIUpdateModuleData *getDeployStyleAIUpdateModuleData() const
	{
		return (const DeployStyleAIUpdateModuleData *)m_moduleData;
	}

private:
	void setMyState( DeployStateTypes stateID );

	AICommandParmsStorage m_lastOutsideCommand;	// +0x340
	Bool m_hasOutsideCommand;					// +0x3E0
	DeployStateTypes m_state;					// +0x3E4
	UnsignedInt m_frameToWakeForDeploy;			// +0x3E8
	char m_unmodelled_3ec[0x400 - 0x3ec];
	Bool m_isAttackMultiple;					// +0x400
};

void DeployStyleAIUpdate::setMyState( DeployStateTypes stateID )
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
			m_frameToWakeForDeploy += TheGameLogic->getFrame();
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
			m_frameToWakeForDeploy += TheGameLogic->getFrame();

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
