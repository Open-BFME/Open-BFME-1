// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HeroDie module ctor.
// Base call then interim dual iface vtbls at +0xC/+0x10, then three
// most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// The base is retail's HeroDieBase, whose constructor is the shared
// ObjectModule constructor at 0x00113C60 (a matched body in
// game/GameEngine/Source/Common/Thing/ObjectModuleConstructor.cpp) reached
// through ILT 0x000170E4, the exact rel32 target of this body.  Spelling the
// base HeroDieBase both names the primary vftable ??_7HeroDie@@6BHeroDieBase@@@
// (the dir32-recorded owner of 0x010B312C, retiring the ??_7HeroDie@@6BObjectModule@@@
// gate debt) and, via the symbols.csv pin on ??0HeroDieBase@@QAE@..., keeps the
// call resolving to the matched constructor through its ILT.  Its 0x0C size
// (vptr plus Module::m_moduleData and ObjectModule::m_object) is what puts the
// dual iface subobjects at +0x0C and +0x10.  Retail's own vtable slots hold ILT
// thunks, so no slot name can link and the anchors are left pure: that emits
// no reference and changes no body byte.
class HeroDieBase
{
public:
	HeroDieBase(Thing *thing, const ModuleData *moduleData);

private:
	virtual void objectModuleAnchor() = 0;

	unsigned char m_data[8];
};

class HeroDieIface1
{
public:
	virtual void heroDieIface1Anchor() = 0;
};

class HeroDieIface2
{
public:
	virtual void heroDieIface2Anchor() = 0;
};

class HeroDie : public HeroDieBase,
	public HeroDieIface1,
	public HeroDieIface2
{
public:
	HeroDie(Thing *thing, const ModuleData *moduleData);
};

// ??0HeroDie@@QAE@PAVThing@@PBVModuleData@@@Z
HeroDie::HeroDie(Thing *thing, const ModuleData *moduleData)
	: HeroDieBase(thing, moduleData)
{
}
