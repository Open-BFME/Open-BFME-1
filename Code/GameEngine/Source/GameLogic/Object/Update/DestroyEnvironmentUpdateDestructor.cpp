// cl: /DNDEBUG /MD /EHsc

// RainOfFireUpdate extra iface at module+0x20, vtable 0x010C1838.
// BMI +0x78 unique override is RainOfFireUpdate 0x010C1850 / getter 0x002A0A10.
// Slot 0 (0x002A0880) stores the 4-byte arg at this+0xC; that memory is the
// float initialized 1.0f at object+0x2C. Sibling slot 1 (0x002A0A30) fadd/fstp
// the same dword. Caller 0x0028D2D0 fstps a float onto the stack before the
// virtual call. push 0 in the dtor is 0.0f.
class RainOfFireUpdateInterface
{
public:
	virtual void set(float value);
};

class BehaviorModuleInterface
{
public:
	virtual void *s00(); virtual void *s01(); virtual void *s02(); virtual void *s03();
	virtual void *s04(); virtual void *s05(); virtual void *s06(); virtual void *s07();
	virtual void *s08(); virtual void *s09(); virtual void *s10(); virtual void *s11();
	virtual void *s12(); virtual void *s13(); virtual void *s14(); virtual void *s15();
	virtual void *s16(); virtual void *s17(); virtual void *s18(); virtual void *s19();
	virtual void *s20(); virtual void *s21(); virtual void *s22(); virtual void *s23();
	virtual void *s24(); virtual void *s25(); virtual void *s26(); virtual void *s27();
	virtual void *s28(); virtual void *s29();
	virtual RainOfFireUpdateInterface *getRainOfFireUpdateInterface();
};

class ObjectModule
{
public:
	virtual ~ObjectModule() {}

private:
	void *m_moduleData;
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

private:
	unsigned char m_pad[0x1F0];
	BehaviorModule **m_behaviors;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

__declspec(noinline)
static RainOfFireUpdateInterface *findRainOfFireUpdateInterface(Object *object)
{
	BehaviorModule **m = object->getBehaviorModules();
	for (; *m; ++m)
	{
		RainOfFireUpdateInterface *iface = (*m)->getRainOfFireUpdateInterface();
		if (iface != 0)
			return iface;
	}
	return 0;
}

class Thing;
class ModuleData;

class BFU_DeepBase
{
public:
	virtual ~BFU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BFU_Iface1
{
public:
	virtual void slot() = 0;
};

class BFU_Iface2
{
public:
	virtual void slot() = 0;
};

class BFU_BehaviorBase : public BFU_DeepBase, public BFU_Iface1
{
public:
	virtual ~BFU_BehaviorBase() {}
};

class UpdateModule : public BFU_BehaviorBase, public BFU_Iface2
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class DestroyEnvironmentUpdate : public UpdateModule
{
protected:
	virtual ~DestroyEnvironmentUpdate();

private:
	unsigned int m_nextCallFrame;
	int m_objectID;
};

// ??1DestroyEnvironmentUpdate@@MAE@XZ
DestroyEnvironmentUpdate::~DestroyEnvironmentUpdate()
{
	if (m_objectID != 0) {
		Object *object = TheGameLogic->findObjectByID(m_objectID);
		if (object != 0) {
			RainOfFireUpdateInterface *iface = findRainOfFireUpdateInterface(object);
			if (iface != 0) {
				iface->set(0.0f);
				TheGameLogic->destroyObject(object);
			}
		}
		m_objectID = 0;
	}
}
