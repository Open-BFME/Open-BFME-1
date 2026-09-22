// ScriptEngine::Rva00343780 at retail 0x00343780 (617 bytes).
// The matched dispatcher establishes this existing name; retain it.
// BFME canonicalizes a script/group name, latches the current scope string,
// and executes a subroutine or reports its fully qualified name.
// Retail has no early return for a missing action parameter. Debug output
// takes two complete temporaries: headline, then JoinPath(canonical,name).
// Native LatchRestore<AsciiString> independently reproduces the 99-byte ctor,
// 86-byte destructor, and 30-byte deleting destructor. Its first vtable entry
// at VA010E7688 routes through ILT0001D499 to the deleting body00339FA0.
// Identity is established by the protected dispatcher call in
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineExecuteActions.cpp.
// The string ABI is the repository's canonical ascii_string.h; 0x00887B60 is
// StringBase<char>'s copy body, not GameSpyGroupRoom.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common

#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_pad[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	int getNumParameters() const { return m_parameterCount; }
	Parameter *getParameter(int index) const
	{
		return index >= 0 && index < m_parameterCount ? m_parameters[index] : 0;
	}

private:
	void *m_vtable;
	int m_actionType;
	int m_parameterCount;
	Parameter *m_parameters[12];
	ScriptAction *m_nextAction;
};

struct Rva003412E0Node;
class Rva00355950Arr;

class ScriptGroup
{
public:
	Rva003412E0Node *getScript() const
	{
		return *(Rva003412E0Node **)((const char *)this + 8);
	}
	bool isActive() const { return *(const unsigned char *)((const char *)this + 0x0C) != 0; }
	bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x0D) != 0; }
};

class Script
{
public:
	bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x17) != 0; }
};

#include "LatchRestore.h"

// These two member contracts are established by their direct retail call
// shapes and existing named rows: by-value AsciiString plus optional canonical
// output.  The returned objects expose the fields consumed below at +8/+C/+D
// and +17, respectively.
class ScriptEngine
{
protected:
	ScriptGroup *findGroup(AsciiString name, AsciiString *canonicalOut);
	Script *findScript(AsciiString name, AsciiString *canonicalOut);

	// ILT0x000485BD -> 0x0033C290: ECX=this; one AsciiString*; pointer result.
	Rva00355950Arr *Rva0033C290(AsciiString *canonical);

	public:
	// Existing named ScriptEngine family members at 0x003412E0/0x00340F10.
	void walkNamed(Rva00355950Arr *array, Rva003412E0Node *node, bool filter);
	void applyNamed(void *object, void *slot);

	void AppendDebugMessage(const AsciiString &message, bool forcePause);
protected:

	void Rva00343780(ScriptAction *action);
};

// Matched JoinPath at00195FC0 via ILT00029B6D returns left + slash + right.
// Its returned temporary survives the debug call and is then destroyed.
AsciiString Rva00195FC0JoinPath(const AsciiString &left, const AsciiString &right);

#define RVA00343780_REPORT(NAME, HEADLINE) \
    do { \
        AppendDebugMessage(AsciiString(HEADLINE), false); \
        AppendDebugMessage(Rva00195FC0JoinPath(canonical, NAME), false); \
    } while (0)

// ?Rva00343780@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::Rva00343780(ScriptAction *action)
{
	AsciiString name = action->getParameter(0)->getString();
	AsciiString canonical;
	ScriptGroup *group = findGroup(name, &canonical);
	if (group)
	{
		if (group->isSubroutine())
        {
            if (group->isActive())
            {
                Rva00355950Arr *array = Rva0033C290(&canonical);
                if (array)
                {
                    LatchRestore<AsciiString> restore(*(AsciiString *)((char *)this + 0x17088), canonical);
                    walkNamed(array, group->getScript(), false);
                }
            }
        }
        else
        {
            RVA00343780_REPORT(name,
                "***Attempting to call script that is not a subroutine:***");
        }
	}
	else
	{
		Script *script = findScript(name, &canonical);
		if (script)
		{
			if (script->isSubroutine())
			{
				LatchRestore<AsciiString> restore(*(AsciiString *)((char *)this + 0x17088), canonical);
				applyNamed(script, &name);
			}
			else
			{
				RVA00343780_REPORT(name,
					"***Attempting to call script that is not a subroutine:***");
			}
		}
		else
		{
			RVA00343780_REPORT(name, "***Script not defined:***");
		}
	}
}
