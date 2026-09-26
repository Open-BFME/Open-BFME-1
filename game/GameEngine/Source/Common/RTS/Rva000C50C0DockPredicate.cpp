// cl: /DNDEBUG /MD /EHsc
// Neutral reconstruction of the 102-byte dock-legality predicate at
// 0x000C50C0. Callers 0x00847AD0/0x00847AEC use TheActionManager;
// the method name remains neutral because its canonical name is not proven.
// Its ABI is an ActionManager thiscall with four stack arguments; the third
// word is unused here and the fourth controls the final dock-interface query.

typedef bool Bool;

class Object;

struct Rva000C50C0DockUpdateInterface
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual Bool accepts(Object const *) = 0;
};

struct Rva000C50C0BehaviorModuleInterface
{
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual Rva000C50C0DockUpdateInterface *getDockUpdateInterface();
};

struct Rva000C50C0BehaviorModule
{
	char padding00[0x0c];
	Rva000C50C0BehaviorModuleInterface interfaceAt0c;
};

class Object
{
	char padding00[0x1f0];

public:
	Rva000C50C0BehaviorModule **m_behaviorModules;
};

class ActionManager
{
public:
	Bool canTransferSuppliesAt(Object const *, Object const *);

	// ?rvaC50C0DockPredicate@ActionManager@@QAE_NPBVObject@@0H_N@Z
	Bool rvaC50C0DockPredicate(Object const *obj, Object const *dockDest,
		int, Bool checkDockInterface);
};

Bool ActionManager::rvaC50C0DockPredicate(Object const *obj,
	Object const *dockDest, int, Bool checkDockInterface)
{
	Object const *destination = dockDest;
	Rva000C50C0BehaviorModule **module = destination->m_behaviorModules;
	Rva000C50C0BehaviorModule *current;
	Rva000C50C0DockUpdateInterface *dockInterface;
	while ((current = *module) != 0)
	{
		dockInterface = current->interfaceAt0c.getDockUpdateInterface();
		if (dockInterface != 0)
			break;
		++module;
	}

	if (current == 0)
		return false;

	if (canTransferSuppliesAt(obj, destination) == true)
		return true;

	if (checkDockInterface == false)
		return false;

	return dockInterface->accepts(obj);
}
