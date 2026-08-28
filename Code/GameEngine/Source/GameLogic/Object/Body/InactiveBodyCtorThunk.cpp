// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: InactiveBody module ctor.
//
// Two non-novtable interface bases, so the interim +0xC/+0x10 vtbls precede the
// most-derived set. The 1.0f at +0x14 is written between the two groups, so it
// is a base-subobject initialiser; the bool at +0x18 is written after them and
// is the derived body.
//
// The trailing call is on m_object rather than on this -- retail loads ecx from
// this+8 -- and its target is unnamed in both ledgers (ILT 0x00030887 onto
// 0x001C7E60), so it carries an address-derived shim name.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void call_00030887(int value);				///< unnamed body at 0x001C7E60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class InactiveBodyIface1
{
public:
	virtual void inactiveBodyIface1Anchor();
};

class InactiveBodyIface2
{
public:
	virtual void inactiveBodyIface2Anchor();
};

class InactiveBodyFields
{
public:
	InactiveBodyFields() : m_14(1.0f) {}

	float m_14;									///< retail this+0x14
};

class InactiveBodyBase : public BehaviorModule
{
public:
	InactiveBodyBase(Thing *thing, const ModuleData *moduleData);
};

class InactiveBody : public InactiveBodyBase,
	public InactiveBodyIface1,
	public InactiveBodyIface2,
	public InactiveBodyFields
{
public:
	InactiveBody(Thing *thing, const ModuleData *moduleData);

protected:
	bool m_18;									///< retail this+0x18
};

// ??0InactiveBody@@QAE@PAVThing@@PBVModuleData@@@Z
InactiveBody::InactiveBody(Thing *thing, const ModuleData *moduleData)
	: InactiveBodyBase(thing, moduleData)
{
	m_18 = false;

	m_object->call_00030887(1);
}
