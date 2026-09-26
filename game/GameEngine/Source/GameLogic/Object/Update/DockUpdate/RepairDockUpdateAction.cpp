// cl: /DNDEBUG /MD /EHsc
//
// RepairDockUpdate::action, retail RVA 0x002CEFA0.  The constructor at
// 0x002CED20 installs the RepairDockUpdate vtables, and the retail body uses
// the repair module data and body-module calls described by RepairDockUpdate.h.

typedef int ObjectID;
typedef float Real;
typedef bool Bool;

enum DamageType
{
	DAMAGE_HEALING = 7
};

enum DeathType
{
	DEATH_NONE = 1
};

struct BFMEDamageInfoInput
{
	char m_gap00[ 8 ];
	ObjectID m_sourceID;
	char m_gap0c[ 4 ];
	DamageType m_damageType;
	char m_gap14[ 4 ];
	DeathType m_deathType;
	Real m_amount;
	Bool m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();
	BFMEDamageInfoInput in;
	char m_gap24[ 0x5c - 0x24 ];
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void attemptHealing( BFMEDamageInfo *damageInfo ) = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

class Object
{
public:
	ObjectID getID() const
	{
		return *(const ObjectID *)( (const char *)this + 0x74 );
	}

	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface *const *)( (const char *)this + 0x200 );
	}
};

class RepairDockUpdateModuleData
{
public:
	char m_gap00[ 0x10 ];
	Real m_framesForFullHeal;
};

class RepairDockUpdate
{
public:
	virtual Bool action( Object *docker, Object *drone );

	RepairDockUpdateModuleData *getRepairDockUpdateModuleData() const
	{
		return *(RepairDockUpdateModuleData **)( (char *)this - 0x1c );
	}

	Object *getObject() const
	{
		return *(Object **)( (char *)this - 0x18 );
	}

	char m_gap04[ 0x64 ];
	ObjectID m_lastRepair;
	Real m_healthToAddPerFrame;
};

Bool RepairDockUpdate::action( Object *docker, Object *drone )
{
	if ( docker == 0 )
		return false;

	RepairDockUpdateModuleData *modData = getRepairDockUpdateModuleData();
	BodyModuleInterface *body = docker->getBodyModule();
	if ( m_lastRepair == 0 )
	{
		m_lastRepair = docker->getID();
		m_healthToAddPerFrame =
			(body->getMaxHealth() - body->getHealth()) / modData->m_framesForFullHeal;
	}

	if ( body->getHealth() >= body->getMaxHealth() )
	{
		m_lastRepair = 0;
		return false;
	}

	BFMEDamageInfo healingInfo;
	healingInfo.in.m_amount = m_healthToAddPerFrame;
	healingInfo.in.m_sourceID = getObject()->getID();
	healingInfo.in.m_damageType = DAMAGE_HEALING;
	healingInfo.in.m_deathType = DEATH_NONE;
	body->attemptHealing( &healingInfo );
	if ( drone != 0 )
	{
		body = drone->getBodyModule();
		healingInfo.in.m_amount = body->getMaxHealth();
		body->attemptHealing( &healingInfo );
	}

	return true;
}
