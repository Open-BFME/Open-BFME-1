// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Open-BFME5: CaveContain::onContaining.
//
// The retail entry `this` is already the ContainModuleInterface secondary-vtable
// pointer (the same one OpenContain::onContaining and the recalc call both read
// through unmodified -- no adjustor in the bytes), so this replica models just
// that interface slice standalone rather than pulling in the full drifted
// vendored OpenContain.h hierarchy (see CaveContainCtorThunk.cpp for the general
// note on BFME's layout drift vs. the ZH header).
//
// ZH's ContainModuleInterface (reference/.../GameLogic/Module/ContainModule.h)
// puts recalcApparentControllingPlayer() 16 pure virtuals in (slot 0x3C); retail
// calls it through slot 0x40, one pointer further out, so BFME's interface has
// exactly one additional virtual ahead of it that ZH's doesn't declare. Its
// identity doesn't matter for this function's bytes -- only the count does --
// so it is modelled as an anonymous pad slot.
#include "PreRTS.h"
#include "GameLogic/Object.h"

class ContainModuleInterfaceSlice
{
public:
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;								///< slot 0x3C: last ZH-declared virtual before recalc
	virtual void recalcApparentControllingPlayer() = 0;	///< slot 0x40 in retail
	virtual void onContaining( Object *obj, Bool wasSelected ) = 0;
};

// ?onContaining@OpenContain@@UAEXPAVObject@@_N@Z is a pinned callee (packet 00219850);
// no local definition needed, only the declaration to get the mangled name right.
class OpenContain : public ContainModuleInterfaceSlice
{
public:
	virtual void onContaining( Object *obj, Bool wasSelected );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CaveContain.h
class CaveContain : public OpenContain
{
public:
	virtual void onContaining( Object *obj, Bool wasSelected );
};

// ?onContaining@CaveContain@@UAEXPAVObject@@_N@Z
void CaveContain::onContaining( Object *obj, Bool wasSelected )
{
	OpenContain::onContaining( obj, wasSelected );
	// objects inside a building are held
	obj->setDisabled( DISABLED_HELD );

	//
	// the team of the building is now the same as those that have garrisoned it, be sure
	// to save our original team tho so that we can revert back to it when all the
	// occupants are gone
	//
	recalcApparentControllingPlayer();

}
