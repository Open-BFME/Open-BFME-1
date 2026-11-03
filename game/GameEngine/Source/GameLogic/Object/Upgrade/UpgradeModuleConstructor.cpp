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

// The +0x18 interface's own table 0x010A1BFC is recorded as ??_7Rva001EE620@@6B@,
// so the interface keeps that address-derived name.
class Rva001EE620
{
public:
	virtual void isAlreadyUpgraded();
};

// UpgradeModule's own four tables are installed by hand: 0x010A36E0 and
// 0x010A36CC are recorded under the address-derived Rva002D44E0DeepDtorL1 view,
// 0x010A3804 and 0x010A3740 under nothing, so they take g_Va names.
extern "C" const char __identifier("??_7Rva002D44E0DeepDtorL1@@6BRva002D44E0DeepDtorL1M0@@@")[];
extern "C" const char __identifier("??_7Rva002D44E0DeepDtorL1@@6BRva002D44E0DeepDtorL1M1@@@")[];
extern const char g_Va010A3804[];
extern const char g_Va010A3740[];

class __declspec(novtable) UpgradeModule : public BehaviorModule, public Rva002D9B80, public Rva001EE620
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpgradeModule();
};

UpgradeModule::UpgradeModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	*reinterpret_cast<const char **>(static_cast<Rva002D9B80 *>(this)) =
		__identifier("??_7Rva002D44E0DeepDtorL1@@6BRva002D44E0DeepDtorL1M0@@@");
	*reinterpret_cast<const char **>(this) = g_Va010A3804;
	*reinterpret_cast<const char **>(static_cast<BehaviorModuleInterface *>(this)) = g_Va010A3740;
	*reinterpret_cast<const char **>(static_cast<Rva001EE620 *>(this)) =
		__identifier("??_7Rva002D44E0DeepDtorL1@@6BRva002D44E0DeepDtorL1M1@@@");
}
