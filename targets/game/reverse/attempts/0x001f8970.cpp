// ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=1.0 date=2026-11-03
// cl: /DNDEBUG /MD /EHsc
//
// ??0UpgradeModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x001F8970, 139 B.
// The shared base constructor of the upgrade module constructors (they call it
// through ILT 0x0000C315). Identity evidence:
// targets/game/reverse/identity_evidence/0x001f8970.md.
//
// ZH UpgradeModule.h: UpgradeModule(thing, moduleData) : BehaviorModule(thing,
// moduleData) {}. Retail shape: the out-of-line ObjectModule constructor
// (ILT 0x000170E4), the inline BehaviorModule vptr round (its
// BehaviorModuleInterface base first), the UpgradeMux constructor at +0x10
// (ILT 0x0003D24E; ledgered under its address name Rva002D9B80, ilt_oracle
// CONFIRMS ??0UpgradeMux@@QAE@XZ there), an interface base at +0x18 whose own
// vptr (0x010A1BFC) is stored before the UpgradeModule round. Unwind state 0
// covers the constructed BehaviorModule while the mux is built.

class Thing;
class ModuleData;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
private:
	const ModuleData *m_moduleData;
	Thing *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
	}
	virtual ~BehaviorModule();
};

class Rva002D9B80
{
public:
	Rva002D9B80();
	virtual void upgradeImplementation();
private:
	bool m_upgradeExecuted;
};

class UpgradeModuleInterface
{
public:
	virtual void isAlreadyUpgraded();
};

class UpgradeModule : public BehaviorModule, public Rva002D9B80, public UpgradeModuleInterface
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpgradeModule();
};

UpgradeModule::UpgradeModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
}
