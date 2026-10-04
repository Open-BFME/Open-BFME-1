// cl: /DNDEBUG /MD /EHsc
//
// DestroyEnvironmentUpdate destructor, retail 0x0028CFB0 (171 bytes).
// The constructor at 0x0028CD70 establishes the three UpdateModule vtables
// and the object ID at +0x24.  The destructor resolves that ID, deletes the
// attached helper when present, destroys the object, clears the ID, and then
// runs the shared UpdateModule base teardown at 0x00047C53.

class ModuleData;
class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
	void destroyObject(Object *object);
};

// The retail global TheBfmeGameLogic is a Rva00367E30Logic *, so the
// declaration must spell that pointee type to mangle to the same name.
struct Rva00367E30Logic : GameLogic
{
};

extern Rva00367E30Logic *TheBfmeGameLogic;

// destroyObject is reached through the retail ILT thunk 0x0001D0DE.
extern void j_0001d0de();

class BfmeDestroyable
{
public:
	virtual void deleteInstance(int flags);
};

BfmeDestroyable *bfmeFindModule();

class BFU_DeepBase
{
public:
	virtual ~BFU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public BFU_DeepBase, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class DestroyEnvironmentUpdate : public UpdateModule
{
public:
	virtual ~DestroyEnvironmentUpdate();

private:
	unsigned int m_nextCallFrame;
	unsigned int m_objectID;
};

// ??1DestroyEnvironmentUpdate@@UAE@XZ
DestroyEnvironmentUpdate::~DestroyEnvironmentUpdate()
{
	if (m_objectID)
	{
		Object *object = TheBfmeGameLogic->findObjectByID((int)m_objectID);
		if (object)
		{
			BfmeDestroyable *module = bfmeFindModule();
			if (module)
			{
				typedef void (GameLogic::*DestroyFn)(Object *);
				union { void (*fn)(); DestroyFn call; } destroy = { j_0001d0de };
				module->deleteInstance(0);
				(TheBfmeGameLogic->*destroy.call)(object);
			}
		}
		m_objectID = 0;
	}
}
