// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// Each vtable slot holds a real body address in retail, reached through an ILT
// thunk; the slots are declared pure so the emitted vftable entries resolve to
// __purecall instead of five undefined names that stop this object from
// linking. The constructor only stores the vtable pointers, so the emitted
// bytes are unchanged. Same convention as
// game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleModuleStateCtor005FC800.cpp.

// The base constructor is reached through the five-byte incremental-link thunk
// at 0x00013462 (ledger ?j_00013462@@YAXXZ, target 0x006A6360), and the body
// there is already matched as SpecialAbilityUpdate_ctor_Thunk.cpp's
// ??0SpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, so the mem-initializer
// below resolves to that file and needs no definition here.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor() = 0;

private:
	unsigned char m_data[8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;

private:
	unsigned char m_data[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor() = 0;

private:
	unsigned char m_data[196];
};

class SpecialAbilityUpdate : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface
{
public:
	SpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );
};

class ToggleMountedInterface
{
public:
	virtual void toggleMountedInterfaceAnchor() = 0;
};

class ToggleMountedSpecialAbilityUpdate : public SpecialAbilityUpdate,
	public ToggleMountedInterface
{
public:
	ToggleMountedSpecialAbilityUpdate( Thing *, const ModuleData * );
};

ToggleMountedSpecialAbilityUpdate::ToggleMountedSpecialAbilityUpdate(
	Thing *thing, const ModuleData *moduleData )
	: SpecialAbilityUpdate( thing, moduleData )
{
}