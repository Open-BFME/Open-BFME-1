// ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.0 date=2026-11-12
// cl: /DNDEBUG /MD /EHsc
// AIUpdateInterface::update, retail 0x0027E5A0 (843 bytes).
//
// Identity (BFME 1 evidence): ilt_oracle CONFIRMS
// ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ at this address, its
// ILT 0x00028772 carries that pin, and the matched DeployStyleAIUpdate::update
// (DeployStyleAIUpdate_update_BFME.cpp) calls it as AIUpdateInterface::update.
// The receiver is the +0x10 UpdateModuleInterface subobject. The old lift name
// ??1AnimalAIUpdate@@UAE@XZ is refuted (re_attempts: AnimalAIUpdate's
// destructor is 0x002B2F60).
//
// Shape (BFME 2 donor, Open-BFME-2 76f0baefa6
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceUpdate.cpp,
// BFME 2 0x0026E267): the same stored-command replay, quick/main update
// split, engaged-flag sleep clamp and owner range model condition with
// chooseLocomotorSet. BFME 1 differs: no orders-manager refresh, the
// AI-updating status bit is set and cleared directly (no EH-tracked scope),
// the stored command is flagged by a bool at +0x31C, no lone-unit or
// script-tracker/team tail. Offsets below are read from the retail body;
// member names past the ledger's callees are structural.
#include <string.h>
#include "../../command_source_type.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// TU-local coordinate view; the out-of-line estimate is the matched
// ?GetLengthEstimate2D@Coord3D@@QBEMXZ (0x000C3D10) in WWMath/coord3d.cpp.
// Retail registers no unwind state for the geometry copy live across the
// planar-offset call and this estimate: both are declared non-throwing.
struct Coord3D
{
	Real x, y, z;
	Real GetLengthEstimate2D() const throw();
};

enum AICommandType
{
	AICMD_NO_COMMAND = -1
};

struct DamageInfo
{
	char m_bfme_body[0x5C];
};

// Layout witnessed by the matched AICommandParmsStorage::store/reconstitute;
// the coordinate vector is out-of-line state here (the destructor is the
// matched ??1AICommandParms@@QAE@XZ at 0x000D7330).
struct AICommandParms
{
	AICommandParms( AICommandType cmd, CommandSourceType commandSource );
	~AICommandParms();

	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	class Object *m_obj;
	class Object *m_otherObj;
	const void *m_team;
	void *m_coords[3];
	const void *m_waypoint;
	const void *m_polygon;
	int m_intValue;
	DamageInfo m_damage;
	const void *m_commandButton;
	void *m_path;
};

class AICommandParmsStorage
{
public:
	void reconstitute( AICommandParms &parms ) const;
	unsigned char m_payload[0xa0];
};

template <int NUMBITS>
class BitFlags
{
public:
	__forceinline explicit BitFlags( Int bit )
	{
		memset( m_bits, 0, sizeof( m_bits ) );
		m_bits[bit >> 5] |= 1U << (bit & 31);
	}
	__forceinline UnsignedInt test( Int bit ) const { return m_bits[bit >> 5] & (1U << (bit & 31)); }
	__forceinline void set( Int bit ) { m_bits[bit >> 5] |= 1U << (bit & 31); }
	__forceinline void clear( Int bit ) { m_bits[bit >> 5] &= ~(1U << (bit & 31)); }
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<86> ObjectStatusMaskType;

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_37 = 37,		///< retail Object+0x94 & 0x20
	OBJECT_STATUS_IS_AI_UPDATING = 71,	///< retail Object+0x98 & 0x80
	OBJECT_STATUS_BIT_73 = 73		///< retail Object+0x98 & 0x200
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum CrushSquishTestType
{
	TEST_CRUSH_ONLY,
	TEST_SQUISH_ONLY,
	TEST_CRUSH_OR_SQUISH
};

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};

// The override walk is the matched ?getFinalOverride@Overridable@@QBEPBV1@XZ.
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	__forceinline Bool isKindOf3( Int bit ) const { return (m_kindOfWord3 & (1U << bit)) != 0; }
	char m_unmodelled_008[0xD4 - 0x08];
	UnsignedInt m_kindOfWord3;		///< retail this+0xD4
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if ( !m_value )
			return 0;
		return (const T *)m_value->getFinalOverride();
	}
	const Overridable *m_value;
};

class GeometryInfo
{
public:
	GeometryInfo( const GeometryInfo &that );
	virtual ~GeometryInfo();
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

	Bool m_isSmall;
	char m_unmodelled_005[0x10 - 0x05];
	Real m_boundingCircleRadius;		///< retail this+0x10
	char m_unmodelled_014[0x5C - 0x14];
};

class Thing
{
public:
	virtual ~Thing();
	Bool isKindOf( KindOfType t ) const;
};

class AIUpdateInterface;

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template.operator->(); }
	UnsignedInt testStatus( ObjectStatusTypes bit ) const { return m_status.test( bit ); }
	void setStatus( const ObjectStatusMaskType &mask, Bool set );
	UnsignedInt testModelConditionState( Int bit ) const { return m_modelConditionFlags.test( bit ); }
	void notifyModelConditionChanged();
	__forceinline void setModelConditionState( Int bit )
	{
		if ( !m_modelConditionFlags.test( bit ) )
		{
			m_modelConditionFlags.set( bit );
			notifyModelConditionChanged();
		}
	}
	__forceinline void clearModelConditionState( Int bit )
	{
		if ( m_modelConditionFlags.test( bit ) )
		{
			m_modelConditionFlags.clear( bit );
			notifyModelConditionChanged();
		}
	}
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool crushPolicy( Object *other, CrushSquishTestType test ) const;
	Real getDistanceSquared( const Object *other ) const;
	Coord3D rva001E3E40( const Object *other ) const throw();

	OVERRIDE<ThingTemplate> m_template;	///< retail this+0x04
	char m_unmodelled_008[0x90 - 0x08];
	ObjectStatusMaskType m_status;		///< retail this+0x90
	char m_unmodelled_09C[0xAC - 0x9C];
	GeometryInfo m_geometryInfo;		///< retail this+0xAC
	char m_unmodelled_108[0x110 - 0x108];
	BitFlags<320> m_modelConditionFlags;	///< retail this+0x110
	char m_unmodelled_138[0x1A4 - 0x138];
	UnsignedInt m_flags1A4;			///< retail this+0x1A4
	char m_unmodelled_1A8[0x204 - 0x1A8];
	AIUpdateInterface *m_ai;		///< retail this+0x204
	char m_unmodelled_208[0x214 - 0x208];
	Object *m_rangeOwner;			///< retail this+0x214
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};
extern GameLogic *TheGameLogic;

// ?test@Rva001B3FE0@@QBE_NXZ, retail 0x001B3FE0.
class Rva001B3FE0
{
public:
	Bool test() const;
};

// ?bfmeSyncEGF@BfmeThingEGF@@QAEXXZ, retail 0x00271B40: called on the whole
// AIUpdateInterface when module data +0x54 is set.
class BfmeThingEGF
{
public:
	void bfmeSyncEGF();
};

class StateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual Bool slot12();			///< vtable +0x30
};

struct AIUpdateModuleData
{
	char m_unmodelled_000[0x4C];
	Real m_rangeOwnerRange;			///< retail +0x4C
	LocomotorSetType m_rangeLocomotorSet;	///< retail +0x50
	Bool m_sync;				///< retail +0x54
};

// The primary vtable reaches chooseLocomotorSet at +0x1FC (slot 127).
template <int N> class AIUpdateVSlots : public AIUpdateVSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class AIUpdateVSlots<0>
{
};

class UpdateModuleBase : public AIUpdateVSlots<127>
{
public:
	virtual Bool chooseLocomotorSet( LocomotorSetType wst );
protected:
	const AIUpdateModuleData *m_moduleData;	///< +0x04
	Object *m_object;			///< +0x08
	void *m_field0C;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	UnsignedInt m_field14, m_field18, m_field1C;
};

class AICommandInterface
{
public:
	virtual void aiDoCommand( const AICommandParms *parms ) = 0;
};

class AIUpdateInterface : public UpdateModuleBase, public UpdateModuleInterface, public AICommandInterface
{
public:
	virtual UpdateSleepTime update();

	UpdateSleepTime rva00273F90();		///< retail 0x00273F90 (main update)
	UpdateSleepTime rva0027C250();		///< retail 0x0027C250 (quick update)
	Int rva0027bf60();			///< matched, retail 0x0027BF60

	Object *getObject() const { return m_object; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	Object *getCurrentVictim() const
	{
		if ( m_currentVictimID != 0 )
			return TheGameLogic->findObjectByID( m_currentVictimID );
		return 0;
	}

	char m_unmodelled_024[0x30 - 0x24];
	StateMachine *m_stateMachine;		///< +0x30
	char m_unmodelled_034[0x40 - 0x34];
	Int m_currentVictimID;			///< +0x40
	char m_unmodelled_044[0x140 - 0x44];
	Rva001B3FE0 *m_path;			///< +0x140
	char m_unmodelled_144[0x1D8 - 0x144];
	Int m_mode1D8;				///< +0x1D8
	char m_unmodelled_1DC[0x27C - 0x1DC];
	AICommandParmsStorage m_pendingCommand;	///< +0x27C
	Bool m_hasPendingCommand;		///< +0x31C
};

enum
{
	MODELCONDITION_IN_OWNER_RANGE = 277,	///< retail Object+0x130 & 0x200000
	KINDOF_RANGE_OWNER_WORD3_BIT = 13	///< retail template+0xD4 & 0x2000
};

// ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime AIUpdateInterface::update()
{
	Object *obj = getObject();
	obj->setStatus( ObjectStatusMaskType( OBJECT_STATUS_IS_AI_UPDATING ), true );

	if ( m_hasPendingCommand )
	{
		if ( !(m_path && m_mode1D8 != 0 && m_path->test()) &&
			!(obj->m_flags1A4 & 0x100) &&
			!obj->testStatus( OBJECT_STATUS_BIT_73 ) )
		{
			AICommandParms parms( AICMD_NO_COMMAND, CMD_FROM_AI );
			m_pendingCommand.reconstitute( parms );
			m_hasPendingCommand = false;
			aiDoCommand( &parms );
		}
	}

	Bool quick = getStateMachine()->slot12();
	if ( !quick )
	{
		if ( m_mode1D8 == 2 || m_mode1D8 == 3 || m_mode1D8 == 4 )
			quick = true;
	}

	UpdateSleepTime sleep;
	if ( obj->testStatus( OBJECT_STATUS_BIT_37 ) && quick &&
		!(obj->isKindOf( (KindOfType)14 ) && m_mode1D8 == 3) )
		sleep = rva0027C250();
	else
		sleep = rva00273F90();

	if ( getAIUpdateModuleData()->m_sync )
		reinterpret_cast<BfmeThingEGF *>( this )->bfmeSyncEGF();
	UpdateSleepTime engaged = (UpdateSleepTime)rva0027bf60();
	if ( engaged < sleep )
		sleep = engaged;

	Object *source = obj->getTemplate()->isKindOf3( KINDOF_RANGE_OWNER_WORD3_BIT ) ? getObject() : obj->m_rangeOwner;
	if ( source && source->getTemplate()->isKindOf3( KINDOF_RANGE_OWNER_WORD3_BIT ) )
	{
		AIUpdateInterface *ai = source->getAI();
		if ( ai->getAIUpdateModuleData()->m_rangeLocomotorSet != 0 )
		{
			Object *victim = ai->getCurrentVictim();
			Bool inRange;
			if ( victim == 0 )
			{
				GeometryInfo geom( source->getGeometryInfo() );
				Coord3D offset = source->rva001E3E40( getObject() );
				Real dist = offset.GetLengthEstimate2D();
				inRange = geom.getBoundingCircleRadius() * 2.0f > dist;
			}
			else if ( source->crushPolicy( victim, TEST_CRUSH_OR_SQUISH ) )
			{
				Real range = getAIUpdateModuleData()->m_rangeOwnerRange;
				inRange = range * range < source->getDistanceSquared( victim );
			}
			else
				inRange = true;

			if ( inRange )
			{
				getObject()->setModelConditionState( MODELCONDITION_IN_OWNER_RANGE );
				chooseLocomotorSet( ai->getAIUpdateModuleData()->m_rangeLocomotorSet );
			}
			else
			{
				getObject()->clearModelConditionState( MODELCONDITION_IN_OWNER_RANGE );
				chooseLocomotorSet( LOCOMOTORSET_NORMAL );
			}
		}
	}
	else if ( getObject()->testModelConditionState( MODELCONDITION_IN_OWNER_RANGE ) )
	{
		getObject()->clearModelConditionState( MODELCONDITION_IN_OWNER_RANGE );
		chooseLocomotorSet( LOCOMOTORSET_NORMAL );
	}

	obj->setStatus( ObjectStatusMaskType( OBJECT_STATUS_IS_AI_UPDATING ), false );
	return sleep;
}
