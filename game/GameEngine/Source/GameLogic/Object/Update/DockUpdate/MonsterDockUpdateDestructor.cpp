// cl: /DNDEBUG /MD /EHsc

class DockUpdate
{
public:
	virtual ~DockUpdate();

private:
	unsigned int m_objectModuleStorage[2];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor();

private:
	unsigned int m_updateModuleStorage[3];
};

class DockUpdateInterface
{
public:
	virtual void dockAnchor();
};

class MonsterDockUpdate : public DockUpdate,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public DockUpdateInterface
{
protected:
	virtual ~MonsterDockUpdate();
};

MonsterDockUpdate::~MonsterDockUpdate()
{
}
