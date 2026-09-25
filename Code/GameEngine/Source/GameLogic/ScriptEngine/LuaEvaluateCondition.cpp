// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lua script binding EvaluateCondition (cdecl int f(lua_State*)), retail
// 0x002E4760 (510 B). Identity: the Lua registration routine at 0x002EC990
// pushes ILT 0x0001A0C3 (jmp 0x002E4760) with lua_pushcclosure and binds it
// with the next lua_setglobal("EvaluateCondition"). The body resolves a
// condition template by its internal name, builds the matching Condition,
// fills its Parameters from the Lua stack, and sends it through the
// ScriptConditions interface. Its twin ExecuteAction (0x002E49E0, ILT
// 0x00031061) walks the same parameter loop over ScriptAction.

#include <string.h>

#pragma intrinsic(strcmp)

// StringBase<char> as ascii_string.h's base declares it, but without the
// out-of-line destructor: retail inlines ~AsciiString here as one direct
// releaseBuffer call (the 5-byte ~AsciiString at 0x0005EE90 is only a jmp to
// it).
template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);

private:
	StringBase(const T *str);
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

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

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { releaseBuffer(); }

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	const char *str() const { return m_data ? m_data->data : ""; }
};

class Parameter
{
public:
	void friend_setInt(int value) { m_int = value; }
	void friend_setReal(float value) { m_real = value; }

private:
	int m_paramType;
	bool m_initialized;
	int m_int;
	float m_real;

public:
	AsciiString m_string;

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

	// Argument 1 is the condition name; the rest fill its parameters.
	int numArgs = lua_gettop(state);
	if (numArgs != condition->getNumParameters() + 1)
		return 0;

	for (int i = 0; i < numArgs - 1; ++i)
	{
		Parameter *parameter = condition->getParameter(i);
		if (lua_isnumber(state, i + 2))
		{
			double value = lua_tonumber(state, i + 2);
			parameter->friend_setReal(value);
			parameter->friend_setInt(value);
		}
		else if (lua_isstring(state, i + 2))
		{
			AsciiString value(lua_tostring(state, i + 2));
			parameter->m_string = value;
		}
		else if (lua_type(state, i + 2) == 1)
		{
			parameter->friend_setInt(0);
		}
		else
		{
			return 0;
		}
	}

	bool result = TheScriptConditions->evaluateCondition(condition);
	delete condition;
	bfmeGo1039E((BfmeQ1039 *)state, result ? 1 : 0);
	return 1;
}
