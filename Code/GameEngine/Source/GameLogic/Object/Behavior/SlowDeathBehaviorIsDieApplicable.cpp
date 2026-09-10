// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// SlowDeathBehavior::isDieApplicable (retail 0x001F7080, 23 B).
//
// The ZH header inlines this; retail keeps an out-of-line copy for the vtable.
// The body belongs to the SlowDeathBehaviorInterface subobject, which BFME
// places four bytes later than ZH (+0x24: this-relative loads -0x20/-0x1C):
// BFME's UpdateModule carries one more dword. That dword lives in this
// TU-local mirror of UpdateModule, not in the shared module headers (a
// non-polymorphic pad base would not do: MSVC lays vfptr-carrying bases first).
#include "PreRTS.h"
#include "GameLogic/Module/SlowDeathBehavior.h"

class Rva001F7080UpdateModule : public UpdateModule
{
protected:
	Int m_bfmePad;
};

class Rva001F7080SlowDeathBehavior : public Rva001F7080UpdateModule, public DieModuleInterface, public SlowDeathBehaviorInterface
{
public:
	const SlowDeathBehaviorModuleData *getSlowDeathBehaviorModuleData() const
	{
		return (const SlowDeathBehaviorModuleData *)getModuleData();
	}
	virtual Bool isDieApplicable( const DamageInfo *damageInfo ) const;	// ?isDieApplicable@SlowDeathBehavior@@UBE_NPBVDamageInfo@@@Z
};

// ?isDieApplicable@SlowDeathBehavior@@UBE_NPBVDamageInfo@@@Z
Bool Rva001F7080SlowDeathBehavior::isDieApplicable( const DamageInfo *damageInfo ) const
{
	return getSlowDeathBehaviorModuleData()->m_dieMuxData.isDieApplicable( getObject(), damageInfo );
}
