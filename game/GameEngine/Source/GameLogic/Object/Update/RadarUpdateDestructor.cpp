// cl: /O2 /Ob1
//
// Open-BFME: RadarUpdate complete destructor at retail RVA 0x002A0180
// (25 bytes). The protected scalar-deleting wrapper (RadarUpdate
// DeletingDestructor.cpp) reaches it through ILT 0x0000B037; ilt_oracle
// confirms the protected ??1RadarUpdate@@MAE@XZ decoration. The empty
// destructor inlines the UpdateModule teardown (three vtable stores) and
// tail-jumps to the ObjectModule destructor ILT 0x00047C53.

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
	void *m_object;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}
};

class __declspec(novtable) RadarUpdate : public UpdateModule
{
protected:
	virtual ~RadarUpdate();
};

RadarUpdate::~RadarUpdate()
{
}
