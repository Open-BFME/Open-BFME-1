// cl: /DNDEBUG /MD /EHsc
//
// ObjectModule::ObjectModule, retail 0x00113C60 (131 B).  Identical in shape
// to the DrawableModule constructor at 0x00113DA0 (see
// DrawableModuleConstructor.cpp) except that it installs vtable 0x01089774 and
// caches AsObject(thing) through Thing vtable slot +8 instead of slot +0x10.
//
// The implementation follows the shipped Generals/Zero Hour source in
// Common/Thing/Module.cpp: construct Module from the required ModuleData and
// cache AsObject(thing).  A non-trivial Module destructor is declared so
// VC7.1 emits the constructor's retail exception-unwind state.
//
// Identity: the exact constructor is reached through ILT 0x000170E4 by the
// named module constructors (ObjectHelper, FiringTracker, UpdateModule,
// SiegeDockingBehavior), its vtable 0x01089774 slot zero routes through
// ILT 0x00002C9D to the ObjectModule scalar-deleting destructor at
// 0x00113F20, and the null ModuleData string at 0x01089750 is shared with the
// DrawableModule twin.

typedef int Int;

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	Int m_code;
	const char *m_message;
};

class ModuleData
{
};

class Object;
class Drawable;

class Thing
{
public:
	virtual void unknown0();
	virtual void unknown1();
	virtual Object *asObjectMeth();
	virtual void unknown2();
	virtual Drawable *asDrawableMeth();
};

inline Object *AsObject(Thing *thing)
{
	return thing ? thing->asObjectMeth() : 0;
}

class Module
{
public:
	Module(const ModuleData *moduleData) : m_moduleData(moduleData) {}
	virtual ~Module();
	virtual void moduleAnchor();

private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual void objectModuleAnchor();

private:
	Object *m_object;
};

// ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectModule::ObjectModule(Thing *thing, const ModuleData *moduleData) :
	Module(moduleData)
{
	if (!moduleData)
		throw INIException(3, "module data may not be null\n");

	m_object = AsObject(thing);
}
