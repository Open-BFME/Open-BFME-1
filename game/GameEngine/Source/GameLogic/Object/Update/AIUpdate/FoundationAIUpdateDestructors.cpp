// cl: /DNDEBUG /MD /EHsc
// Complete destructor 0x002B9D60 and emitted scalar wrapper 0x002BA130.
// Constructor 0x002BA040, module factories/name, and vtable 0x00CC734C
// identify the class; wrapper ILT 0x0000E791 reaches this complete teardown.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
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
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	// name_oracle: UpdateModule+0x14, layout_witness confidence 1.00.
	unsigned int m_nextCallFrameAndPhase;
	int m_18;
	int m_1c;
};

class FoundationAIUpdateIface3
{
public:
	virtual void interface3Anchor() = 0;
};

class Gen_dtor_000b33c0
{
public:
	virtual ~Gen_dtor_000b33c0();

private:
	unsigned char m_data[0x6c];
};

class FoundationAIUpdate : public UpdateModule,
	public FoundationAIUpdateIface3
{
public:
	virtual ~FoundationAIUpdate();

private:
	Gen_dtor_000b33c0 m_member;
};

// ??1FoundationAIUpdate@@UAE@XZ
FoundationAIUpdate::~FoundationAIUpdate()
{
}
