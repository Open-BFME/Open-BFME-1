// cl: /O2 /Ob1
//
// Open-BFME: WargBehavior complete destructor at retail RVA 0x0020D930
// (18 bytes). The protected scalar-deleting wrapper (WargBehavior
// DeletingDestructor.cpp, 0x0020DA60) reaches it through ILT 0x000299C9;
// ilt_oracle confirms the protected ??1WargBehavior@@MAE@XZ
// decoration. The empty destructor inlines the BehaviorModule teardown (two
// vtable stores) and tail-jumps to the ObjectModule destructor ILT 0x00047C53.

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

class __declspec(novtable) WargBehavior : public BehaviorModule
{
protected:
	virtual ~WargBehavior();
};

WargBehavior::~WargBehavior()
{
}
