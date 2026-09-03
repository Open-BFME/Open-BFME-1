// cl: /DNDEBUG /MD /EHsc
// readable body of ??0RailedTransportDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp

class Thing;
class ModuleData;

class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();

private:
	const ModuleData *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public ObjectModuleBase
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_unmodelled_24[ 0x88 - 0x24 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RailedTransportDockUpdate.h
class RailedTransportDockUpdateInterface
{
public:
	virtual void railedTransportDockAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RailedTransportDockUpdate.h
class RailedTransportDockUpdate : public DockUpdate,
	public RailedTransportDockUpdateInterface
{
public:
	RailedTransportDockUpdate( Thing *thing, const ModuleData *moduleData );

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual void updateAnchor();
	virtual void dockAnchor();
	virtual void railedTransportDockAnchor();

private:
	unsigned int m_dockingObjectID;
	float m_pullInsideDistancePerFrame;
	unsigned int m_unloadingObjectID;
	float m_pushOutsideDistancePerFrame;
	int m_unloadCount;
};

RailedTransportDockUpdate::RailedTransportDockUpdate( Thing *thing, const ModuleData *moduleData )
	: DockUpdate( thing, moduleData )
{
	m_dockingObjectID = 0;
	m_pullInsideDistancePerFrame = 0.0f;
	m_unloadingObjectID = 0;
	m_pushOutsideDistancePerFrame = 0.0f;
	m_unloadCount = -1;
}
