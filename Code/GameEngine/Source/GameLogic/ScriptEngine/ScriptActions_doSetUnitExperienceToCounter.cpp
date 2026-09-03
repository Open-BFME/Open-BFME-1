// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: SET_UNIT_EXPERIENCE_TO_COUNTER at retail RVA 0x002F6670.

#include "StringInline.h"

typedef bool Bool;

class Object;
class ScriptActions;

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
	virtual Object *getUnitNamed(const AsciiString &name) = 0;

protected:
	friend class ScriptActions;
	struct ScriptCounter *bfmeCounter(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;

struct ScriptCounter
{
	int m_value;
};

struct UnitExperience
{
	unsigned char m_beforeExperience[0xc];
	float m_experience;
};

class Object
{
private:
	unsigned char m_beforeExperience[0x210];

public:
	UnitExperience *m_experience;
};

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doSetUnitExperienceToCounter(const AsciiString &unit,
		Parameter *counter);
};

void ScriptActions::doSetUnitExperienceToCounter(const AsciiString &unit,
	Parameter *counter)
{
	Object *object = TheScriptEngine->getUnitNamed(unit);
	if (object)
	{
		UnitExperience *experience = object->m_experience;
		if (experience)
		{
			ScriptCounter *destination = TheScriptEngine->bfmeCounter(
				counter->m_string);
			destination->m_value = (int)experience->m_experience;
		}
	}
}
