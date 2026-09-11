// ?EvaluateCondition@@YAHPAUlua_State@@@Z
// partial score=0.97 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// The Lua binding resolves a condition template by its internal name, builds
// the matching Condition, fills its Parameters from the Lua stack, and sends
// it through the ScriptConditions interface.

#include <string.h>

#pragma intrinsic(strcmp)

struct lua_State;

extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_isnumber(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" int lua_isstring(lua_State *state, int index);
extern "C" int lua_type(lua_State *state, int index);

struct BfmeQ1039;
void bfmeGo1039E(BfmeQ1039 *queue, int value);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ObjectStatusMask
{
	unsigned int m_bits[2];
};

struct AsciiStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

private:
	AsciiStringData *m_data;
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);

private:
	char *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	operator const UnicodeString &() const
	{
		return *(const UnicodeString *)this;
	}

private:
	void releaseBuffer();
	char *m_data;
};

class Parameter
{
public:
	void setNumber(double value)
	{
		m_real = (float)value;
		m_int = (int)value;
	}

	void setBoolean()
	{
		m_int = 0;
	}

private:
	int m_paramType;
	bool m_initialized;
	unsigned char m_padding[3];
	int m_int;
	float m_real;

public:
	UnicodeString m_string;

private:
	Coord3D m_coord;
	ObjectStatusMask m_objectStatus;
};

class Condition
{
public:
	enum ConditionType { NUM_ITEMS = 0xB8 };

	Condition(ConditionType type);
	virtual ~Condition();

	int getNumParameters() const { return m_numParms; }
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parms[index];
		return 0;
	}

	public:
	ConditionType m_conditionType;
	int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAndCondition;
	int m_hasWarnings;
	int m_customData;
	unsigned int m_customFrame;
};

class ConditionTemplate
{
public:
	AsciiString m_uiName;
	AsciiString m_uiName2;
	AsciiString m_internalName;
};

class ScriptEngine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual const ConditionTemplate *getConditionTemplate(Condition::ConditionType type);
};

class ScriptConditionsInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual bool evaluateCondition(Condition *condition);
};

extern ScriptEngine *TheScriptEngine;
extern ScriptConditionsInterface *TheScriptConditions;

// ?EvaluateCondition@@YAHPAUlua_State@@@Z
int EvaluateCondition(lua_State *state)
{
	const char *name = lua_tostring(state, 1);
	int conditionType = 0;
	const ConditionTemplate *conditionTemplate;

	for (;;)
	{
		conditionTemplate = TheScriptEngine->getConditionTemplate((Condition::ConditionType)conditionType);
		if (strcmp(name, conditionTemplate->m_internalName.str()) == 0)
			break;
		++conditionType;
		if (conditionType >= Condition::NUM_ITEMS)
			return 0;
	}

	if (conditionTemplate == 0)
		return 0;

	Condition *condition = new Condition((Condition::ConditionType)conditionType);

	int numParameters;
	if ((numParameters = lua_gettop(state)) != condition->m_numParms + 1)
		return 0;
	--numParameters;

	if (numParameters > 0)
	{
		for (int index = 2; index - 2 < numParameters; ++index)
		{
			register Parameter *parameter = condition->getParameter(index - 2);
			if (lua_isnumber(state, index))
			{
				parameter->setNumber(lua_tonumber(state, index));
			}
			else if (lua_isstring(state, index))
			{
				BFMERetailAsciiString value(lua_tostring(state, index));
				UnicodeString *string = &parameter->m_string;
				string->set((const UnicodeString &)value);
			}
			else if (lua_type(state, index) == 1)
			{
				parameter->setBoolean();
			}
			else
			{
				return 0;
			}
		}
	}

	bool result = TheScriptConditions->evaluateCondition(condition);
	delete condition;
	bfmeGo1039E((BfmeQ1039 *)state, result ? 1 : 0);
	return 1;
}
