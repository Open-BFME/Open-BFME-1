// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModuleBase
{
public:
	virtual void objectModuleAnchor();

private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public ObjectModuleBase
{
private:
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor() = 0;
};

class DockUpdate : public UpdateModule, public DockUpdateInterface
{
public:
	DockUpdate( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_unmodelled_24[ 0x88 - 0x24 ];
};

class RailedTransportDockUpdateInterface
{
public:
	virtual void railedTransportDockAnchor() = 0;
};

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
