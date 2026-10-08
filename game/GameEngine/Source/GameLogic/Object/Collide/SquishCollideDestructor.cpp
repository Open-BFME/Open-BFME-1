// cl: /O2 /Ob1
//
// Open-BFME: SquishCollide complete destructor at retail RVA 0x00216AF0
// (25 bytes). The protected scalar-deleting wrapper (SquishCollide
// DeletingDestructor.cpp, 0x00216C90) reaches it through ILT 0x0002421C;
// ilt_oracle confirms the protected ??1SquishCollide@@MAE@XZ
// decoration. The empty destructor inlines the CollideModule teardown (three
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	virtual ~CollideModule() {}
};

class __declspec(novtable) SquishCollide : public CollideModule
{
protected:
	virtual ~SquishCollide();
};

SquishCollide::~SquishCollide()
{
}
