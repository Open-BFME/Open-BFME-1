// ?executeActions@ScriptEngine@@IAEXPAVScriptAction@@@Z
// BFME dispatcher: identity is established by the released Zero Hour twin,
// its callers, and the BFME-only action/helper fingerprints.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

class Parameter
{
public:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	int getActionType() const { return m_actionType; }
	Parameter *getParameter(int index) { return index >= 0 && index < m_parameterCount ? m_parameters[index] : 0; }
	ScriptAction *getNext() const { return m_nextAction; }
private:
	void *m_vtable;
	int m_actionType;
	int m_parameterCount;
	Parameter *m_parameters[12];
	ScriptAction *m_nextAction;
};

struct ScriptCounter { int value; bool countdown; bool milliseconds; };

class ScriptActions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void executeAction(ScriptAction *action);
};

class ScriptActionsInterface;
extern ScriptActionsInterface *TheScriptActions;
#define TheScriptActions ((ScriptActions *)TheScriptActions)

// ILT00049963 reaches the existing address-only body003369D0, which reads
// the ScriptEngine receiver, takes ScriptAction* and returns with RET4.
extern "C" void __cdecl __identifier("?d_003369d0@@YAXXZ")();

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void addCounter(ScriptAction *action);
	void subCounter(ScriptAction *action);
	void setFlag(ScriptAction *action, bool fromFlag);
	void setTimer(ScriptAction *action, bool milliseconds, bool random);
	void pauseTimer(ScriptAction *action);
	void restartTimer(ScriptAction *action);
	void adjustTimer(ScriptAction *action, bool milliseconds, bool add);
	void enableScript(ScriptAction *action);
	void disableScript(ScriptAction *action);
	void Rva00343780(ScriptAction *action);
	void setSway(ScriptAction *action);
	void setPriorityThing(ScriptAction *action);
	protected:
	void setPriorityKind(ScriptAction *action);
protected:
	void setPriorityDefault(ScriptAction *action);
	protected:
	void Rva00345a50(ScriptAction *action, int randomMode, bool copyCounter, bool seconds);
	void Rva00345910(ScriptAction *action, bool enabled);
	void executeActions(ScriptAction *head);
};

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
int GetGameClientRandomValue(int low, int high, char *file, int line);
#define g_bfmeK1266C 5.0f

// MSVC 7.1 casts call __ftol2; /QIfist changes the frame and conversion width.
// Retail reloads a rounded float and uses FISTP under the active x87 control word.
// This two-instruction helper preserves that proven compiler-specific shape.
__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

void ScriptEngine::executeActions(ScriptAction *head)
{
	ScriptAction *action;
	UnicodeString unused;
	for (action = head; action; action = action->getNext()) {
		switch (action->getActionType()) {
		case 2: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
			if (counter) { counter->value = action->getParameter(1)->m_integer; counter->milliseconds = false; }
			break;
		}
		case 15: addCounter(action); break;
		case 16: subCounter(action); break;
		case 1: setFlag(action, false); break;
		case 6: setTimer(action, false, false); break;
		case 8: enableScript(action); break;
		case 9: disableScript(action); break;
		case 10: Rva00343780(action); break;
		case 20: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
			float value = (float)ceil((double)(action->getParameter(1)->m_real * g_bfmeK1266C));
			counter->value = fast_float2long_round(value);
			counter->milliseconds = true; counter->countdown = true;
			break;
		}
		case 103: setSway(action); break;
		case 152: pauseTimer(action); break;
		case 153: restartTimer(action); break;
		case 150: setTimer(action, false, true); break;
		case 151: setTimer(action, true, true); break;
		case 124: case 125: case 126: case 127: {
			union
			{
				void (__cdecl *symbol)();
				void (ScriptEngine::*member)(ScriptAction *);
			} helper;
			helper.symbol = &__identifier("?d_003369d0@@YAXXZ");
			(this->*helper.member)(action);
			break;
		}
		case 132: setPriorityThing(action); break;
		case 133: setPriorityKind(action); break;
		case 134: setPriorityDefault(action); break;
		case 154: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(1)->m_string);
			float value = (float)ceil((double)(action->getParameter(0)->m_real * g_bfmeK1266C));
			counter->value += fast_float2long_round(value);
			break;
		}
		case 373: Rva00345a50(action, true, false, false); break;
		case 374: Rva00345a50(action, false, true, false); break;
		case 375: setFlag(action, true); break;
		case 155: adjustTimer(action, true, false); break;
		case 415: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
			if (counter) {
				float value = (float)ceil((double)(action->getParameter(1)->m_real * g_bfmeK1266C));
				counter->value = fast_float2long_round(value); counter->milliseconds = true;
			}
			break;
		}
		case 507: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->m_string);
			if (counter) {
				int low = action->getParameter(1)->m_integer;
				int high = action->getParameter(2)->m_integer;
				counter->value = GetGameClientRandomValue(low, high, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 1831);
				counter->milliseconds = false;
			}
			break;
		}
		case 416: Rva00345a50(action, true, false, true); break;
		case 439: Rva00345910(action, false); break;
		case 440: Rva00345910(action, true); break;
		case 5: break;
		default: {
			ScriptActions *actions = TheScriptActions;
			if (actions) actions->executeAction(action);
			break;
		}
		}
	}
}
