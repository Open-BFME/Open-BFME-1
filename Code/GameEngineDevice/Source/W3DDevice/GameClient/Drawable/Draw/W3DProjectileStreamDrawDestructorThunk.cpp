// cl: /DNDEBUG /MD /EHsc
// Readable body of ??1W3DProjectileStreamDraw@@UAE@XZ.
// Retail 0x00369CF0, 116 bytes. Tears down the +0x20 resources member,
// restores the shared Update-module base vtables
// ([+0x10]=0x109CBAC, [+0]=0x109CB5C, [+0xC]=0x109CA98) and chains to the
// pinned ObjectModule destructor. Same base-teardown tail as
// SpawnPointProductionExitUpdate::~SpawnPointProductionExitUpdate.

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

class W3DProjectileStreamResources
{
public:
	~W3DProjectileStreamResources();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DProjectileStreamDraw.h
class W3DProjectileStreamDraw : public UpdateModule
{
public:
	virtual ~W3DProjectileStreamDraw();

private:
	W3DProjectileStreamResources m_resources;
};

// ??1W3DProjectileStreamDraw@@UAE@XZ
W3DProjectileStreamDraw::~W3DProjectileStreamDraw()
{
}
