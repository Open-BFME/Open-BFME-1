// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ExecuteAction, 0x002E49E0 / 554B. The registration routine at
// 0x002EC990 binds ExecuteAction to ILT 0x00031061 -> this body.
// Sibling EvaluateCondition has the same parameter loop. This variant also
// handles Lua type 6 and type 4 using the existing address-derived helpers.
// Parameter+0x24 is written with the extracted type-4 value; its semantic
// field identity is not assumed from the different Zero Hour layout.

#include <string.h>

#pragma intrinsic(strcmp)

#include "ascii_string.h"

struct lua_State;

extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_isnumber(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" int lua_isstring(lua_State *state, int index);
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(lua_State*,int);
unsigned Rva00990210Lookup(lua_State*,int);

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

class Parameter
{
public:
	void friend_setInt(int value) { m_int = value; }
	void friend_setReal(float value) { m_real = value; }
 void setWord24(unsigned value) { *(unsigned*)((char*)this+0x24)=value; }

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

class ScriptAction
{
public:
	enum ScriptActionType { NUM_ITEMS = 0x21F };

	ScriptAction(ScriptActionType type);
	virtual ~ScriptAction();

	int getNumParameters() const { return m_numParms; }
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parms[index];
		return 0;
	}

	ScriptActionType m_actionType;
	int m_numParms;
	Parameter *m_parms[12];
	ScriptAction *m_nextAction;
	bool m_hasWarnings;
	int m_bfmeActionTail;
	
};

class ActionTemplate
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
	virtual const ActionTemplate *getActionTemplate(ScriptAction::ScriptActionType type);
};

class ScriptActionsInterface
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
	virtual void executeAction(ScriptAction *action);
};

extern ScriptEngine *TheScriptEngine;
extern ScriptActionsInterface *TheScriptActions;

// ?ExecuteAction@@YAHPAUlua_State@@@Z
int ExecuteAction(lua_State *state)
{
	const char *name = lua_tostring(state, 1);
	int actionType = 0;
	const ActionTemplate *actionTemplate;

	for (;;)
	{
		actionTemplate = TheScriptEngine->getActionTemplate((ScriptAction::ScriptActionType)actionType);
		if (strcmp(name, actionTemplate->m_internalName.str()) == 0)
			break;
		++actionType;
		if (actionType >= ScriptAction::NUM_ITEMS)
			return 0;
	}

	if (actionTemplate == 0)
		return 0;

	ScriptAction *action = new ScriptAction((ScriptAction::ScriptActionType)actionType);

	// Argument 1 is the action name; the rest fill its parameters.
	int numArgs = lua_gettop(state);
	if (numArgs != action->getNumParameters() + 1)
		return 0;

	for (int i = 0; i < numArgs - 1; ++i)
	{
		Parameter *parameter = action->getParameter(i);
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
		else if (lua_type(state, i + 2) == 6)
        {
            parameter->friend_setInt(Rva00990210Lookup(state,i+2)!=0);
        }
        else if (lua_type(state,i+2)==4 && Rva00990030Lookup(state,i+2))
        {
            parameter->setWord24(Rva00990030Lookup(state,i+2));
        }
		else
		{
			return 0;
		}
	}

	TheScriptActions->executeAction(action);
	delete action;
	bfmeGo1039E((BfmeQ1039 *)state, 1);
	return 1;
}
