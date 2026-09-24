// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: FireWeaponWhenDeadBehavior::onDie; the constructor 0x001FBC70 installs vtable 0x010A3F3C at
// this+0x28 (DieModuleInterface), whose slot 0 reaches ILT 0x0004B317 and this body.

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;
	static const char *s_bitNameList[];

public:
	BitFlags();
	Bool testForAny( const BitFlags &other ) const;
};

template <int NUMBITS>
BitFlags<NUMBITS>::BitFlags()
{
}

typedef BitFlags<192> UpgradeMaskType;

struct Coord3D
{
	Real x, y, z;
};

class Player
{
public:
	const UpgradeMaskType &getCompletedUpgradeMask() const { return m_upgradesCompleted; }

private:
	char m_unreconstructed00[ 0x8c ];
	UpgradeMaskType m_upgradesCompleted;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool testStatus( Int status ) const;
	UnsignedInt getStatusBits98() const { return m_statusBits98; }
	const UpgradeMaskType &getObjectCompletedUpgradeMask() const { return m_objectUpgradesCompleted; }

private:
	char m_unreconstructed00[ 0x98 ];
	UnsignedInt m_statusBits98;
	char m_unreconstructed9C[ 0x224 - 0x9c ];
	UpgradeMaskType m_objectUpgradesCompleted;
};

class BfmeArgFV
{
public:
	unsigned char m_bytes[ 4 ];
};

class BfmeVec3FV
{
public:
	Real x, y, z;
};

class BfmeThingFV
{
public:
	void bfmeComputeFV( BfmeArgFV *argument, BfmeVec3FV *position );
};

class DamageInfoInput
{
public:
	DamageInfoInput &operator=( const DamageInfoInput &other );

private:
	char m_unreconstructed00[ 0x48 ];
};

class DamageInfoOutput
{
public:
	DamageInfoOutput() : m_actualDamageDealt( 0 ), m_actualDamageClipped( 0 ), m_noEffect( false ) {}
	virtual void snapshotAnchor();

	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo
{
public:
	virtual void snapshotAnchor();

	DamageInfoInput in;
	DamageInfoOutput out;
};

class DieMuxData
{
public:
	Bool isDieApplicable( const Object *obj, const DamageInfo *damageInfo ) const;
};

class WeaponTemplate;

class WeaponStore
{
public:
	void createAndFireTempWeapon( const WeaponTemplate *weaponTemplate, const Object *source, const Coord3D *position );
};

extern WeaponStore *TheWeaponStore;

class ModuleData
{
};

class FireWeaponWhenDeadBehaviorModuleData : public ModuleData
{
public:
	char m_unreconstructed00[ 0x70 ];
	Bool m_initiallyActive;
	Bool m_skipStatus2Check71;
	char m_unreconstructed72[ 0x78 - 0x72 ];
	Coord3D m_weaponOffset78;
	DieMuxData m_dieMuxData;
	char m_unreconstructed85[ 0xb0 - 0x85 ];
	const WeaponTemplate *m_deathWeapon;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	virtual void updateModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
	void setWakeFrame( Object *object, UpdateSleepTime wakeDelay );

	const ModuleData *m_moduleData;
	Object *m_object;
	char m_unreconstructed0C[ 0x20 - 0x0c ];
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void getUpgradeActivationMasks( UpgradeMaskType &activation,
		UpgradeMaskType &conflicting ) const = 0;

	Bool m_upgradeExecuted;
};

class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

class FireWeaponWhenDeadBehavior : public UpdateModule, public UpgradeMux, public DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo );

protected:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const
	{
		return static_cast<const FireWeaponWhenDeadBehaviorModuleData *>( getModuleData() );
	}
	Bool isUpgradeActive() const { return isAlreadyUpgraded(); }

	DamageInfo m_lastDamageInfo;
	Int m_deferCount88;
};

// ?onDie@FireWeaponWhenDeadBehavior@@UAEXPBVDamageInfo@@@Z
void FireWeaponWhenDeadBehavior::onDie( const DamageInfo *damageInfo )
{
	const FireWeaponWhenDeadBehaviorModuleData *d = getFireWeaponWhenDeadBehaviorModuleData();

	if ( m_deferCount88 > 0 )
	{
		m_lastDamageInfo = *damageInfo;
		setWakeFrame( getObject(), UPDATE_SLEEP_NONE );
		return;
	}

	if ( !isUpgradeActive() && !getFireWeaponWhenDeadBehaviorModuleData()->m_initiallyActive )
		return;

	if ( !d->m_dieMuxData.isDieApplicable( getObject(), damageInfo ) )
		return;

	if ( getObject()->getStatusBits98() & 0x200000 )
		return;

	if ( !d->m_skipStatus2Check71 && getObject()->testStatus( 2 ) )
		return;

	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );

	Object *obj = getObject();
	if ( obj->getObjectCompletedUpgradeMask().testForAny( conflicting ) )
		return;
	if ( obj->getControllingPlayer()->getCompletedUpgradeMask().testForAny( conflicting ) )
		return;

	if ( d->m_deathWeapon )
	{
		Coord3D position;
		reinterpret_cast<BfmeThingFV *>( getObject() )->bfmeComputeFV(
			reinterpret_cast<BfmeArgFV *>( const_cast<Coord3D *>( &d->m_weaponOffset78 ) ),
			reinterpret_cast<BfmeVec3FV *>( &position ) );
		TheWeaponStore->createAndFireTempWeapon( d->m_deathWeapon, getObject(), &position );
	}
}
