// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClientUpdateModule's constructor, retail 0x00602ED0.
//
// Forwards both arguments to the DrawableModule constructor at ILT 0x00002874,
// stores its own vtable at +0, and zeroes a dword at +0x0c.
//
// That store is the one thing ZH does not explain: ZH's ClientUpdateModule
// constructor has an empty body and initialises nothing, so BFME's carries a
// member of its own. Its offset puts DrawableModule at twelve bytes -- vtable
// plus two -- and says nothing about what the member holds, so it is left
// unnamed.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);		///< ILT 0x00002874
	virtual void drawableModuleAnchor();

private:
	const ModuleData *m_moduleData;					///< retail this+0x04
	void *m_drawable;								///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule : public DrawableModule
{
public:
	ClientUpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual void clientUpdateModuleAnchor();

private:
	int m_unreconstructed_0c;						///< retail this+0x0c, zeroed here
};

// ??0ClientUpdateModule@@QAE@PAVThing@@PBVModuleData@@@Z
ClientUpdateModule::ClientUpdateModule(Thing *thing, const ModuleData *moduleData) :
	DrawableModule(thing, moduleData),
	m_unreconstructed_0c(0)
{
}
