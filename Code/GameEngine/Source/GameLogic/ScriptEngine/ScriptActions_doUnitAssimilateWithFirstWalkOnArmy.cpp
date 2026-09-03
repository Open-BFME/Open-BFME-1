// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: UNIT_ASSIMILATE_WITH_FIRST_WALK_ON_ARMY at retail RVA 0x002F7480.

#include "StringInline.h"

typedef bool Bool;

class Object;

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

class BfmeScriptEngineUnitLookup
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

class ScriptEngine : public BfmeScriptEngineUnitLookup
{
};

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *object, int army);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeGlobFEA *TheGameLogic;

void j_0001867e();

typedef int (__fastcall *BfmeFirstWalkOnArmyThunk)(BfmeGlobFEA *gameLogic);

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doUnitAssimilateWithFirstWalkOnArmy(Parameter *unit);
};

void ScriptActions::doUnitAssimilateWithFirstWalkOnArmy(Parameter *unit)
{
	Object *object = ((ScriptEngine *)TheScriptEngine)->getUnitNamedByValue(
		unit->m_string);
	if (object)
	{
		int army = ((BfmeFirstWalkOnArmyThunk)j_0001867e)(TheGameLogic);
		if (army >= 0)
		{
			TheGameLogic->bfmeCallFEA(object, army);
		}
	}
}
