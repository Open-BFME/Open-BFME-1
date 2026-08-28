// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModule
{
public:
	virtual void updateModuleAnchor();
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
	unsigned int m_04;
	Object *m_object;
};

class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *thing, const ModuleData *moduleData);
};

class __declspec(novtable) ObjectRecoveryHelperIface1
{
public:
	virtual void objectRecoveryIface1Anchor();
};

class __declspec(novtable) ObjectRecoveryHelperIface2
{
public:
	virtual void objectRecoveryIface2Anchor();
};

class ObjectRecoveryHelper : public ObjectHelper,
	public ObjectRecoveryHelperIface1,
	public ObjectRecoveryHelperIface2
{
public:
	ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData);
};

ObjectRecoveryHelper::ObjectRecoveryHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
