// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Retail 0x0034CA20, 80 bytes.  A script unit parameter may carry an object
// id; otherwise the name is resolved through BFME's by-value lookup slot.

#include "StringInline.h"

typedef int ObjectID;

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

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

class ScriptActionParameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
	unsigned char m_beforeObjectID[0x10];
	ObjectID m_objectID;
};

class ScriptEngineByValue
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual Object *getUnitNamedByValue(BfmeAsciiStringArg name) = 0;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *parameter);
};

Object *ScriptEngine::resolveUnit(ScriptActionParameter *parameter)
{
	Object *object;

	if (parameter->m_objectID)
	{
		object = TheGameLogic->findObjectByID(parameter->m_objectID);
		if (object)
			return object;
	}

	void *data = *(void **)&parameter->m_string;
	AsciiString *name = &parameter->m_string;
	if (data == 0)
		return 0;
	if (*(short *)((char *)data + 4) == 0)
		return 0;

	return ((ScriptEngineByValue *)this)->getUnitNamedByValue(*name);
}
