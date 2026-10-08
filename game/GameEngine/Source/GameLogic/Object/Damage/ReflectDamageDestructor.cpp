// cl: /O2 /Ob1
//
// Open-BFME: ReflectDamage complete destructor at retail RVA 0x00251690
// (25 bytes). The protected scalar-deleting wrapper (ReflectDamage
// DeletingDestructor.cpp, 0x00251800) reaches it through ILT 0x00007C57;
// ilt_oracle confirms the protected ??1ReflectDamage@@MAE@XZ decoration.
// The empty destructor inlines the DamageModule teardown: the
// DamageModuleInterface vftable at +0x10, then the BehaviorModule stores,
// and tail-jumps to the ObjectModule destructor ILT 0x00047C53.
//
// The +0x10 vftable is named by its decorated symbol as dir32 records it;
// DamageModule is not declared as a class here so the name cannot bind to a
// vftable of this TU, and novtable keeps ReflectDamage's own tables out.

extern "C" const void *__identifier("??_7DamageModule@@6B@")[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	virtual ~Module();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Module
{
public:
	virtual ~ObjectModule();

private:
	void *m_thing;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class __declspec(novtable) ReflectDamage : public BehaviorModule
{
protected:
	virtual ~ReflectDamage();
};

#define REFLECT_DAMAGE_VPTR(offset, table) \
	(*(const void *volatile *)((unsigned char *)this + (offset)) = (const void *)__identifier(table))

ReflectDamage::~ReflectDamage()
{
	REFLECT_DAMAGE_VPTR(0x10, "??_7DamageModule@@6B@");
}
