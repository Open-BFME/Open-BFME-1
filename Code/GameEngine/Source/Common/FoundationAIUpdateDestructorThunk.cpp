// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift FoundationAIUpdate destructor to clean C++.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_14;
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
