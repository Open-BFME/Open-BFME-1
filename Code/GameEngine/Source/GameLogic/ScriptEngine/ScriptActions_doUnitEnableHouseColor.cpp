// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: UNIT_ENABLE_HOUSE_COLOR handler at retail RVA 0x002F74E0.

#include "StringInline.h"

typedef bool Bool;

class ScriptActions;

class Drawable
{
private:
	friend class ScriptActions;
	void bfmeSetIndicatorOn(Bool enabled);
};

class Object
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
	virtual Drawable *getDrawable() = 0;
};

class ScriptEngine
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
	virtual Object *getUnitNamed(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;

class Parameter
{
public:
	unsigned char _pad[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doUnitEnableHouseColor(Parameter *unit, Bool enabled);
};

void ScriptActions::doUnitEnableHouseColor(Parameter *unit, Bool enabled)
{
	Object *object = TheScriptEngine->getUnitNamed(unit->m_string);
	if (object) {
		Drawable *drawable = object->getDrawable();
		if (drawable) {
			drawable->bfmeSetIndicatorOn(enabled);
		}
	}
}
