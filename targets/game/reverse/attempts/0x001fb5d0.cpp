// ??0FireWeaponWhenDamagedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=1.0 date=2026-10-03
// Native FireWeaponWhenDamagedBehavior constructor; retail 001FB5D0, 652 bytes.
// Requires queued UpdateModule m_pad(-1) initialization. Header/data/virtual
// layout differences are documented in the companion bank evidence.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I. /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#define BFME_MODULE_NO_MPO
#include "PreRTS.h"
#include "game/GameEngine/Include/GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/FireWeaponWhenDamagedBehavior.h"
#include "GameLogic/Object.h"


struct Rva001FB5D0Data {
 char prefix[0x70]; Bool m_initiallyActive; char pad71[11];
 const WeaponTemplate *m_reactionWeaponPristine, *m_reactionWeaponDamaged, *m_reactionWeaponReallyDamaged, *m_reactionWeaponRubble;
 const WeaponTemplate *m_continuousWeaponPristine, *m_continuousWeaponDamaged, *m_continuousWeaponReallyDamaged, *m_continuousWeaponRubble;
};
class Rva001FB5D0UpgradeView {
public:
 virtual Bool slot00() const;
 virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(Bool);
 virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
 void apply() { slot11(); slot13(); slot09(); slot08(true); }
};
static inline void rva001FB5D0SetWeaponID(Weapon* weapon,const Object* object) {
 *(ObjectID*)((char*)weapon+8)=*(const ObjectID*)((const char*)object+0x74);
}

FireWeaponWhenDamagedBehavior::FireWeaponWhenDamagedBehavior( Thing *thing, const ModuleData* moduleData ) : 
	UpdateModule( thing, moduleData ),
	m_reactionWeaponPristine( NULL ),
	m_reactionWeaponDamaged( NULL ),
	m_reactionWeaponReallyDamaged( NULL ),
	m_reactionWeaponRubble( NULL ),
	m_continuousWeaponPristine( NULL ),
	m_continuousWeaponDamaged( NULL ),
	m_continuousWeaponReallyDamaged( NULL ),
	m_continuousWeaponRubble( NULL )
{

	const Rva001FB5D0Data *d = (const Rva001FB5D0Data*)getModuleData();
	const Object* obj = getObject();

	if ( d->m_reactionWeaponPristine )
	{
		m_reactionWeaponPristine				= TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponPristine,					PRIMARY_WEAPON);
		m_reactionWeaponPristine->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_reactionWeaponPristine,obj);
	}
	if ( d->m_reactionWeaponDamaged )
	{
		m_reactionWeaponDamaged					= TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponDamaged,					PRIMARY_WEAPON);
		m_reactionWeaponDamaged->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_reactionWeaponDamaged,obj);
	}
	if ( d->m_reactionWeaponReallyDamaged )
	{
		m_reactionWeaponReallyDamaged		= TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponReallyDamaged,		PRIMARY_WEAPON); 
		m_reactionWeaponReallyDamaged->reloadAmmo( obj ); 
		rva001FB5D0SetWeaponID(m_reactionWeaponReallyDamaged,obj);
	}
	if ( d->m_reactionWeaponRubble )
	{
		m_reactionWeaponRubble					= TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponRubble,						PRIMARY_WEAPON);
		m_reactionWeaponRubble->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_reactionWeaponRubble,obj);
	}


	if ( d->m_continuousWeaponPristine )
	{
		m_continuousWeaponPristine			= TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponPristine,				PRIMARY_WEAPON);
		m_continuousWeaponPristine->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_continuousWeaponPristine,obj);
	}
	if ( d->m_continuousWeaponDamaged )
	{
		m_continuousWeaponDamaged				= TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponDamaged,				PRIMARY_WEAPON);
		m_continuousWeaponDamaged->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_continuousWeaponDamaged,obj);
	}
	if ( d->m_continuousWeaponReallyDamaged )
	{
		m_continuousWeaponReallyDamaged = TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponReallyDamaged,	PRIMARY_WEAPON);
		m_continuousWeaponReallyDamaged->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_continuousWeaponReallyDamaged,obj);
	}
	if ( d->m_continuousWeaponRubble )
	{
		m_continuousWeaponRubble				= TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponRubble,					PRIMARY_WEAPON);
		m_continuousWeaponRubble->reloadAmmo( obj );
		rva001FB5D0SetWeaponID(m_continuousWeaponRubble,obj);
	}

	if (d->m_initiallyActive)
	{
		((Rva001FB5D0UpgradeView*)(UpgradeMux*)this)->apply();
	}

	if (isUpgradeActive() &&
			(d->m_continuousWeaponPristine != NULL ||
			d->m_continuousWeaponDamaged != NULL ||
			d->m_continuousWeaponReallyDamaged != NULL ||
			d->m_continuousWeaponRubble != NULL))
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}
	else
	{
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	}

}

