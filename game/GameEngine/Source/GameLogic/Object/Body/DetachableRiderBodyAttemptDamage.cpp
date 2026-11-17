// cl: /DNDEBUG /MD /EHsc
//
// DetachableRiderBody::attemptDamage at retail 0x00213010.  Identity: the
// registered DetachableRiderBody constructor 0x00212EC0 stores table
// 0x010A8010 at +0x10, the BodyModuleInterface subobject, and slot 0 of that
// table (ILT 0x00035D05) is this body; BodyModuleInterface's first virtual is
// attemptDamage.  The random-value call carries the DetachableRiderBody.cpp
// source path (retail 0x010A8208) and line 94.  The UpgradeMux subobject sits at +0xE0; slots 4
// and 6 of the body interface and the module-data fields keep opaque names.

typedef unsigned char Bool;
typedef float Real;
#include "../../ScriptEngine/game_logic_dispatch.h"

class DamageInfo
{
public:
	char m_unreconstructed000[0x1c];
	Real m_amount;
	Bool m_flag20;
};

class Module;

class Object
{
	// Retail's Object::findModule (0x001BEE60) is a protected member, so the
	// mangled call name carries that access; only the friend may call it here.
protected:
	Module *findModule(NameKeyType key) const;
	friend class DetachableRiderBody;

public:
	char m_unreconstructed000[0x94];
	unsigned char m_flags094;
	char m_unreconstructed095[0x118 - 0x95];
	unsigned char m_flags118;
	char m_unreconstructed119[0x1a4 - 0x119];
	unsigned char m_disabledMask;
};


extern NameKeyGenerator *TheNameKeyGenerator;

float Rva0002CCA5GetGameLogicRandomValueRealThunk(Real lo, Real hi, char *file, int line);

class Gen_0028D8F0
{
public:
	void bfmeSelectCondition(void);
};

class DetachableRiderBodyModuleData
{
public:
	char m_unreconstructed000[0xc4];
	Real m_healthScale;
	char m_unreconstructed0c8[0xcc - 0xc8];
	Real m_chance;
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const DetachableRiderBodyModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *);
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Real slot04() const;
	virtual void slot05();
	virtual Real slot06() const;
};

// The base body (ILT 0x0003B372 -> ActiveBody::attemptDamage 0x00211D40).
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class DetachableRiderBodyBody : public ActiveBody
{
	char m_unreconstructed014[0xe0 - 0x14];
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const;
};

class DetachableRiderBody : public DetachableRiderBodyBody, public UpgradeMux
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

void DetachableRiderBody::attemptDamage(DamageInfo *damageInfo)
{
	Object *object = m_object;
	const DetachableRiderBodyModuleData *data = m_moduleData;
	Bool upgraded = isAlreadyUpgraded();
	Bool protectedHit = Rva0002CCA5GetGameLogicRandomValueRealThunk(0.0f, 1.0f,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Body\\DetachableRiderBody.cpp",
		94) < data->m_chance;
	if (object->m_flags118 & 0x80)
		protectedHit = true;
	if (upgraded && !protectedHit && !(object->m_flags094 & 0x40) &&
		!(object->m_disabledMask & 0x10)) {
		Real health = slot04();
		const DetachableRiderBodyModuleData *scaleData = m_moduleData;
		Real threshold = slot06() * scaleData->m_healthScale;
		Real amount = damageInfo->m_amount;
		if (damageInfo->m_flag20 || health - amount <= 0.0f) {
			damageInfo->m_flag20 = false;
			damageInfo->m_amount = health - threshold;
			static NameKeyType key =
				TheNameKeyGenerator->nameToKey("DetachableRiderUpdate");
			Module *rider = object->findModule(key);
			if (rider)
				((Gen_0028D8F0 *)rider)->bfmeSelectCondition();
		}
	}
	ActiveBody::attemptDamage(damageInfo);
}
