// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

// Five vptrs land at 0x00, 0x0c, 0x10, 0x20 and 0x24 -- the UpdateModule chain
// plus two further interfaces. The base constructor is declared only, so the
// call resolves to the existing pin for
// ??0WeaponModeSpecialPowerUpdateBase@@QAE@PAVThing@@PBVModuleData@@@Z
// at 0x0001DD40.

class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();

	const void *m_moduleData;				///< 0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public ObjectModuleBase
{
public:
	void *m_object;							///< 0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	unsigned int m_nextCallFrameAndPhase;	///< 0x14
	int m_indexInLogic;						///< 0x18
	unsigned int m_updateState;				///< 0x1c -- ends at 0x20
};

class SpecialPowerInterface
{
public:
	virtual void specialPowerAnchor() = 0;
};

class UpgradeInterface
{
public:
	virtual void upgradeAnchor() = 0;
};

class WeaponModeSpecialPowerUpdateBase
	: public UpdateModule, public SpecialPowerInterface, public UpgradeInterface
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *, const ModuleData *);

	unsigned char m_gap28[0x38 - 0x28];
};

// 0x3c..0x4c is a sub-object with its own inlined constructor. That keeps its
// four zero stores as a separate group after the vptr stores, while the single
// init-list member at 0x38 is the one store the vptrs sink past.
struct QuadZero
{
	QuadZero() { a = 0; b = 0; c = 0; d = 0; }

	int a;
	int b;
	int c;
	int d;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicGeometryInfoUpdate.h
class DynamicGeometryInfoUpdate : public WeaponModeSpecialPowerUpdateBase
{
public:
	DynamicGeometryInfoUpdate(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void specialPowerAnchor();
	virtual void upgradeAnchor();

	int m_value38;							///< 0x38
	QuadZero m_quad;						///< 0x3c
};

// ??0DynamicGeometryInfoUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DynamicGeometryInfoUpdate::DynamicGeometryInfoUpdate( Thing *thing, const ModuleData *moduleData )
	: WeaponModeSpecialPowerUpdateBase( thing, moduleData ), m_value38( 0 )
{
}

class SiegeDeployHordeSpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
	SiegeDeployHordeSpecialPower(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void specialPowerAnchor();
	virtual void upgradeAnchor();

	int m_value38;							///< 0x38
	QuadZero m_quad;						///< 0x3c
};

// ??0SiegeDeployHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeDeployHordeSpecialPower::SiegeDeployHordeSpecialPower( Thing *thing, const ModuleData *moduleData )
	: WeaponModeSpecialPowerUpdateBase( thing, moduleData ), m_value38( 0 )
{
}
