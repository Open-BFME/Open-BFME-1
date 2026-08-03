// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgrade::friend_newModuleInstance MI factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class Module
{
public:
	virtual ~Module() {}
};

class ObjectCreationUpgradeBase
{
public:
	virtual ~ObjectCreationUpgradeBase() {}
private:
	unsigned char m_pad[0x4];
};

class ObjectCreationUpgrade : public ObjectCreationUpgradeBase, public Module
{
public:
	ObjectCreationUpgrade(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x24];
};

// ?friend_newModuleInstance@ObjectCreationUpgrade@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *ObjectCreationUpgrade::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return new ObjectCreationUpgrade(thing, data);
}
