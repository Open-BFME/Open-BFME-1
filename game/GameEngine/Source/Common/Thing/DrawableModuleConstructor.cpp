// cl: /DNDEBUG /MD /EHsc
//
// DrawableModule::DrawableModule, retail 0x00113DA0.  Every matched derived
// drawable-module constructor reaches this body through ILT 0x00002874.  The
// old claim called it two unrelated sound-selector constructors, but those
// classes have their own 46-byte bodies at 0x00121F60 and 0x00124A10.
//
// The implementation follows the shipped Generals/Zero Hour source in
// Common/Thing/Module.cpp: construct Module from the required ModuleData and
// cache AsDrawable(thing).  A non-trivial Module destructor is declared so
// VC7.1 emits the constructor's retail exception-unwind state.

typedef int Int;

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

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
	virtual void unknown2();
	virtual Object *asObjectMeth();
	virtual Drawable *asDrawableMeth();
};

inline Drawable *AsDrawable(Thing *thing)
{
	return thing ? thing->asDrawableMeth() : 0;
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

class DrawableModule : public Module
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual void drawableModuleAnchor();

private:
	Drawable *m_drawable;
};

// ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z
DrawableModule::DrawableModule(Thing *thing, const ModuleData *moduleData) :
	Module(moduleData)
{
	if (!moduleData)
		throw INIException(3, "module data may not be null\n");

	m_drawable = AsDrawable(thing);
}
