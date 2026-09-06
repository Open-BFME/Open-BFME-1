// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ~SpawnPointProductionExitUpdate, retail 0x002D17A0, 133 bytes.
//
// >=93% difflib twin of FoundationAIUpdate::~FoundationAIUpdate
// (Code/GameEngine/Source/Common/FoundationAIUpdateDestructorThunk.cpp,
// retail 0x002B9D60, 123 bytes): same base hierarchy shape copied verbatim
// (that shape is what drives the three vtable-repair stores in the shared
// base-teardown tail -- 0x109CBAC/0x109CB5C/0x109CA98, call to the pinned
// SPEU_DeepBase/BFU_DeepBase dtor). The vtable-install constants for the
// derived class itself (0x010CB8AC, 0x010CB7E8, 0x010CB7DC, 0x010CB7A0)
// match ??0SpawnPointProductionExitUpdate
// (SpawnPointProductionExitUpdateCtorModuleFactoryBody.cpp). The one
// semantic difference from the twin: the twin tears down a single embedded
// object with a plain call, this one tears down an array member
// (m_worldCoordSpawnPoints[10], Coord3D, size 0xC each) via the compiler's
// array-delete-iterator helper -- count 0xA (== MAX_SPAWN_POINTS == 10),
// element size 0xC, array base at this+0x2C, matching the ctor's layout.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	Coord3D();
	~Coord3D();

private:
	float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h
class SpawnPointProductionExitUpdate : public UpdateModule,
	public FoundationAIUpdateIface3
{
public:
	virtual ~SpawnPointProductionExitUpdate();

private:
	enum { MAX_SPAWN_POINTS = 10 };

	bool m_bonesInitialized;
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];
	float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];
	unsigned int m_spawnPointOccupier[MAX_SPAWN_POINTS];
};

// ??1SpawnPointProductionExitUpdate@@UAE@XZ
SpawnPointProductionExitUpdate::~SpawnPointProductionExitUpdate()
{
}
