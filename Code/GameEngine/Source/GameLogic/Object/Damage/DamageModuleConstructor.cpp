// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BfmeDamageModuleInterface
{
public:
	virtual void damageModuleInterfaceAnchor();
};

// DamageModule adds a hidden 4-byte member beyond ObjectModule + the two
// interface vtables; the retail ctor initializes it to 1.0f right after
// installing the three vtable pointers. The vendored Zero Hour header shows
// no such member (BFME-specific drift). A sibling class, DieModule, was
// already proven NOT to carry this store: CreateObjectDieConstructor.cpp
// builds DieModule with this same 3-base shape and no extra field, and its
// 60-byte retail body matches without any [this+0x14] store.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModule : public ObjectModule,
	public BehaviorModuleInterface,
	public BfmeDamageModuleInterface
{
public:
	DamageModule( Thing *thing, const ModuleData *moduleData );

private:
	float m_unknown14;
};

DamageModule::DamageModule( Thing *thing, const ModuleData *moduleData )
	: ObjectModule( thing, moduleData )
{
	m_unknown14 = 1.0f;
}
