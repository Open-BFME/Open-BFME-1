// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GateOpenAndCloseBehavior::friend_newModuleInstance MI factory.

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

class GateOpenAndCloseBehaviorBase
{
public:
	virtual ~GateOpenAndCloseBehaviorBase() {}
};

class GateOpenAndCloseBehavior : public GateOpenAndCloseBehaviorBase, public Module
{
public:
	GateOpenAndCloseBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x44];
};

// ?friend_newModuleInstance@GateOpenAndCloseBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GateOpenAndCloseBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return new GateOpenAndCloseBehavior(thing, data);
}
