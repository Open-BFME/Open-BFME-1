// cl: /DNDEBUG /MD /EHsc
// readable body of ??0FireWeaponWhenDeadBehavior@@: this file (the Zero Hour
// FireWeaponWhenDeadBehavior.cpp view cannot reproduce the BFME tables).
// Real C++ for ??0FireWeaponWhenDeadBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// which until s555 was a __declspec(naked) __emit copy of retail.
//
// IDENTITY.  The registered factory constructs this class here, and the body
// installs the class's own vtables: primary 0x010A405C (whose ??_G slot is the
// matched ??_GFireWeaponWhenDeadBehavior at 0x001FC080), the UpgradeMux table
// 0x010A3F40 at +0x20 (slots 4/7/9 are the matched isSubObjectsUpgrade,
// removeUpgrade and upgradeImplementation of this class) and the
// DieModuleInterface table 0x010A3F3C at +0x28 (slot 0 is the matched onDie at
// 0x001FC0B0).  Retail ends `ret 8` at +0x188, so the extent is 395 bytes.
//
// LAYOUT.  The same UpdateModule prologue as LeafletDropBehaviorCtorThunk.cpp
// (ObjectModule ctor ILT 0x000170E4, then the two interface vptrs and the
// 0/-1/-1 update state), the shared UpgradeMux base constructed out of line by
// ILT 0x0003D24E (body 0x002D9B80, matched as ??0Rva002D9B80@@QAE@XZ), the
// DieModuleInterface at +0x28, the inline DamageInfo at +0x2C..+0x87 whose
// defaults (22, 15, true, 1.0f) are the ones ActiveBody_Constructor.cpp
// recovers, and the defer counter at +0x88 that onDie tests.  The module-data
// offsets +0x70 (m_initiallyActive) and +0x74 are the ones the matched
// FireWeaponWhenDeadBehaviorModuleData constructor fixes.
//
// BODY.  Zero Hour's constructor gives the self upgrade when the module starts
// active (UpgradeMux::giveSelfUpgrade: performUpgradeFX, processUpgradeRemoval,
// upgradeImplementation, setUpgradeExecuted(true) at UpgradeMux slots 0x2C,
// 0x34, 0x24, 0x20).  BFME then seeds the defer counter from module data +0x74
// (an unsigned compared against 0.0f, clamped to at least 1 by a by-reference
// max) and puts the module to sleep forever.

class Thing;
class ModuleData;
class Object;

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

template <class T>
inline const T &maxOf( const T &a, const T &b )
{
	return a < b ? b : a;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDeadBehavior.h
class FireWeaponWhenDeadBehaviorModuleData
{
public:
	char m_unreconstructed00[ 0x70 ];
	Bool m_initiallyActive;
	Bool m_field71;
	UnsignedInt m_field74;
};

class PB_DeepBase
{
public:
	PB_DeepBase( Thing *thing, const ModuleData *moduleData );
	virtual ~PB_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: PB_DeepBase( thing, moduleData ),
		  m_nextCallFrameAndPhase( 0 ), m_indexInLogic( -1 ), m_updateState( -1 )
	{
	}

protected:
	void setWakeFrame( Object *object, UpdateSleepTime wakeDelay );
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_updateState;
};

// The shared UpgradeMux base (vptr plus the executed flag).  Its constructor is
// the matched 13-byte body at 0x002D9B80, which the ledger names by address.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class Rva002D9B80
{
public:
	Rva002D9B80();

	virtual Bool isAlreadyUpgraded() const;
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual Bool isSubObjectsUpgrade();
	virtual void slot14();
	virtual void slot18();
	virtual void removeUpgrade();
	virtual void setUpgradeExecuted( Bool executed );
	virtual void upgradeImplementation();
	virtual void slot28();
	virtual void performUpgradeFX();
	virtual void slot30();
	virtual void processUpgradeRemoval();

	void giveSelfUpgrade()
	{
		performUpgradeFX();
		processUpgradeRemoval();
		upgradeImplementation();
		setUpgradeExecuted( true );
	}

private:
	Bool m_upgradeExecuted;
};

class DieModuleInterface
{
public:
	virtual void onDie( const class DamageInfo *damageInfo ) = 0;
};

class DamageInfoInput
{
public:
	__forceinline DamageInfoInput()
	{
		m_field04 = 0;
		m_field08 = 0;
		m_field0C = 22;
		m_field10 = 15;
		m_field14 = 0;
		m_field18 = 0;
		m_field1C = false;
		m_field1D = true;
		m_field20 = 0;
		m_field24 = 0;
		m_field28 = 0;
		m_field2C = 0;
		m_field30 = 0;
		m_field34 = 0;
		m_field38 = 0;
		m_field3C = 0;
		m_field40 = 0;
		m_field44 = 1.0f;
	}
	virtual void xfer();

	UnsignedInt m_field04;
	unsigned short m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Real m_field18;
	Bool m_field1C;
	Bool m_field1D;
	UnsignedInt m_field20;
	UnsignedInt m_field24;
	UnsignedInt m_field28;
	Real m_field2C;
	Real m_field30;
	Real m_field34;
	Real m_field38;
	Real m_field3C;
	Real m_field40;
	Real m_field44;
};

class DamageInfoOutput
{
public:
	__forceinline DamageInfoOutput() : m_actualDamageDealt( 0 ), m_actualDamageClipped( 0 ), m_noEffect( false ) {}
	virtual void xfer();

	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo
{
public:
	__forceinline DamageInfo() {}
	__forceinline explicit DamageInfo( int ) {}
	virtual void xfer();

	DamageInfoInput in;
	DamageInfoOutput out;
};

// FireWeaponWhenDeadBehavior's own five tables are installed by hand so each
// store names what the DIR32 record admits: the primary 0x010A405C under its
// owned ??_7FireWeaponWhenDeadBehavior@@6B@ (slot zero reaches the matched
// ??_GFireWeaponWhenDeadBehavior), the UpgradeMux and DieModuleInterface tables
// 0x010A3F40/0x010A3F3C under their recorded address-derived names and the two
// unowned interface tables 0x010A3F98/0x010A3F8C under g_Va names. The class is
// novtable and installTables() runs as the first member's initializer, which is
// where the compiler's own round runs: after the bases, before the members.
extern "C" const char __identifier("??_7FireWeaponWhenDeadBehavior@@6B@")[];
extern "C" const char __identifier("??_7Rva001FBFC0DeepDtor@@6BRva001FBFC0DeepDtorL2M0@@@")[];
extern "C" const char __identifier("??_7Rva001FBFC0DeepDtor@@6BRva001FBFC0DeepDtorL2M1@@@")[];
extern const char g_Va010A3F98[];
extern const char g_Va010A3F8C[];

class __declspec(novtable) FireWeaponWhenDeadBehavior : public UpdateModule, public Rva002D9B80, public DieModuleInterface
{
public:
	FireWeaponWhenDeadBehavior( Thing *thing, const ModuleData *moduleData );
	virtual void onDie( const DamageInfo *damageInfo );

protected:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const
	{
		return reinterpret_cast<const FireWeaponWhenDeadBehaviorModuleData *>( getModuleData() );
	}

	__forceinline int installTables()
	{
		*reinterpret_cast<const char **>( static_cast<UpdateModule *>( this ) ) =
			__identifier("??_7FireWeaponWhenDeadBehavior@@6B@");
		*reinterpret_cast<const char **>( static_cast<PB_Iface1 *>( this ) ) = g_Va010A3F98;
		*reinterpret_cast<const char **>( static_cast<PB_Iface2 *>( this ) ) = g_Va010A3F8C;
		*reinterpret_cast<const char **>( static_cast<Rva002D9B80 *>( this ) ) =
			__identifier("??_7Rva001FBFC0DeepDtor@@6BRva001FBFC0DeepDtorL2M0@@@");
		*reinterpret_cast<const char **>( static_cast<DieModuleInterface *>( this ) ) =
			__identifier("??_7Rva001FBFC0DeepDtor@@6BRva001FBFC0DeepDtorL2M1@@@");
		return 0;
	}

	DamageInfo m_lastDamageInfo;
	UnsignedInt m_deferCount88;
};

// ??0FireWeaponWhenDeadBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
FireWeaponWhenDeadBehavior::FireWeaponWhenDeadBehavior( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData ), m_lastDamageInfo( installTables() ), m_deferCount88( 0 )
{
	if ( getFireWeaponWhenDeadBehaviorModuleData()->m_initiallyActive )
	{
		giveSelfUpgrade();
	}

	if ( getFireWeaponWhenDeadBehaviorModuleData()->m_field74 > 0.0f )
	{
		UnsignedInt one = 1;
		m_deferCount88 = maxOf( getFireWeaponWhenDeadBehaviorModuleData()->m_field74, one );
	}

	setWakeFrame( getObject(), UPDATE_SLEEP_FOREVER );
}
