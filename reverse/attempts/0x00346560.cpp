// ?executeActions@ScriptEngine@@IAEXPAVScriptAction@@@Z
// partial score=0.4 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

class Parameter
{
public:
	int getInt() const { return m_integer; }
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }
private:
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
	ScriptAction *getNext() const { return m_next; }
private:
	void *m_vtable;
	int m_actionType;
	int m_parameterCount;
	Parameter *m_parameters[12];
	ScriptAction *m_next;
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

#define TheScriptActions (*(ScriptActions **)0x012F0620)

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
	void callSubroutine(ScriptAction *action);
	void setSway(ScriptAction *action);
	void setFade(ScriptAction *action);
	void setPriorityThing(ScriptAction *action);
	void setPriorityKind(ScriptAction *action);
	void setPriorityDefault(ScriptAction *action);
	void bfmeAction345A50(ScriptAction *action, bool a, bool b, bool c);
	void bfmeAction345910(ScriptAction *action, bool enabled);
	void executeActions(ScriptAction *head);
};

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
int GetGameClientRandomValue(int low, int high, char *file, int line);
static float const bfmeMillisecondsPerSecond = 1000.0f;

void ScriptEngine::executeActions(ScriptAction *head)
{
	UnicodeString unused;
	for (ScriptAction *action = head; action; action = action->getNext()) {
		switch (action->getActionType()) {
		case 1: setFlag(action, false); break;
		case 2: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
			if (counter) { counter->value = action->getParameter(1)->getInt(); counter->milliseconds = false; }
			break;
		}
		case 5: break;
		case 6: setTimer(action, false, false); break;
		case 8: enableScript(action); break;
		case 9: disableScript(action); break;
		case 10: callSubroutine(action); break;
		case 15: addCounter(action); break;
		case 16: subCounter(action); break;
		case 20: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
			counter->value = (int)ceil(action->getParameter(1)->getReal() * bfmeMillisecondsPerSecond);
			counter->milliseconds = true; counter->countdown = true;
			break;
		}
		case 103: setSway(action); break;
		case 124: case 125: case 126: case 127: setFade(action); break;
		case 132: setPriorityThing(action); break;
		case 133: setPriorityKind(action); break;
		case 134: setPriorityDefault(action); break;
		case 150: setTimer(action, false, true); break;
		case 151: setTimer(action, true, true); break;
		case 152: pauseTimer(action); break;
		case 153: restartTimer(action); break;
		case 154: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(1)->getString());
			counter->value += (int)ceil(action->getParameter(0)->getReal() * bfmeMillisecondsPerSecond);
			break;
		}
		case 155: adjustTimer(action, true, false); break;
		case 372: bfmeAction345A50(action, true, false, false); break;
		case 373: bfmeAction345A50(action, false, true, false); break;
		case 374: setFlag(action, true); break;
		case 415: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
			if (counter) { counter->value = (int)ceil(action->getParameter(1)->getReal() * bfmeMillisecondsPerSecond); counter->milliseconds = true; }
			break;
		}
		case 416: bfmeAction345A50(action, true, false, true); break;
		case 439: bfmeAction345910(action, false); break;
		case 440: bfmeAction345910(action, true); break;
		case 507: {
			ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
			if (counter) { counter->value = GetGameClientRandomValue(action->getParameter(1)->getInt(), action->getParameter(2)->getInt(), "ScriptEngine.cpp", 1831); counter->milliseconds = false; }
			break;
		}
		default: if (TheScriptActions) TheScriptActions->executeAction(action); break;
		}
	}
}
