// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the radius-decal update constructor to clean C++.

class Thing;
class ModuleData;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule, public UpdateModuleInterface, public ModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}
	virtual ~UpdateModule() {}
	void setWakeFrame(Object *, unsigned int);

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	RadiusDecal();
	~RadiusDecal();
	void clear();

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate : public UpdateModule
{
public:
	RadiusDecalUpdate(Thing *, const ModuleData *);
	virtual ~RadiusDecalUpdate();

private:
	RadiusDecal m_deliveryDecal;
	bool m_killWhenNoLongerAttacking;
};

// ??0RadiusDecalUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
RadiusDecalUpdate::RadiusDecalUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_deliveryDecal.clear();
	m_killWhenNoLongerAttacking = false;
	setWakeFrame(getObject(), 0x3FFFFFFF);
}
