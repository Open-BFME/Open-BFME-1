// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: NAMED_TOGGLE_CLOSE_RANGE_WEAPON at retail RVA 0x002F6CA0.

#include "StringInline.h"

typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class Object;
class SupplyWarehouseDockUpdate;

class ScriptEngineByValue
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	virtual Object *getUnitNamedByValue(BfmeAsciiStringArg name) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class DualWeaponBehavior
{
private:
	unsigned char m_beforeCloseRangeFlag[0x20];

public:
	Bool m_useCloseRangeWeapon;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SupplyWarehouseDockUpdate *findUpdateModule(int key);
};

extern ScriptEngineByValue *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedToggleCloseRangeWeapon(const AsciiString &unitName,
		Bool enabled);
};

void ScriptActions::doNamedToggleCloseRangeWeapon(
	const AsciiString &unitName, Bool enabled)
{
	Object *object = TheScriptEngine->getUnitNamedByValue(unitName);
	if (object)
	{
		static const int dualWeaponBehaviorKey =
			TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
		DualWeaponBehavior *behavior = (DualWeaponBehavior *)
			object->findUpdateModule(dualWeaponBehaviorKey);
		if (behavior)
			behavior->m_useCloseRangeWeapon = enabled;
	}
}
