// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CivilianSpawnCollide module ctor.
// Base call then interim dual iface vtbls at +0xC/+0x10, then three
// most-derived vtbls at +0/+0xC/+0x10.

class Thing;
class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// The base is retail's ObjectModule, whose constructor is the shared
// ObjectModule constructor at 0x00113C60 (a matched body in
// game/GameEngine/Source/Common/Thing/ObjectModuleConstructor.cpp) reached
// through ILT 0x000170E4, the exact rel32 target of this body.  Naming the
// base for the constructor it calls is what makes the call resolve; an
// invented intermediate class left the reference dangling.  Its 0x0C size
// (vptr plus Module::m_moduleData and ObjectModule::m_object) is what puts the
// dual iface subobjects at +0x0C and +0x10.  Retail's own vtable slots hold ILT
// thunks, so no slot name can link and the anchors are left pure: that emits
// no reference and changes no body byte.
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);

private:
	virtual void objectModuleAnchor() = 0;

	unsigned char m_data[8];
};

class CivilianSpawnCollideIface1
{
public:
	virtual void civilianSpawnCollideIface1Anchor() = 0;
};

class CivilianSpawnCollideIface2
{
public:
	virtual void civilianSpawnCollideIface2Anchor() = 0;
};

class CivilianSpawnCollide : public ObjectModule,
	public CivilianSpawnCollideIface1,
	public CivilianSpawnCollideIface2
{
public:
	CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData);
};

// ??0CivilianSpawnCollide@@QAE@PAVThing@@PBVModuleData@@@Z
CivilianSpawnCollide::CivilianSpawnCollide(Thing *thing, const ModuleData *moduleData)
	: ObjectModule(thing, moduleData)
{
}
