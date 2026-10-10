// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class ScriptGroupPoolObject
{
public:
};

class ScriptPoolObject
{
public:
};

struct ScriptGroupWrapper
{
	ScriptGroupPoolObject *m_value;
};

struct ScriptWrapper
{
	ScriptPoolObject *m_value;
};

class BfmeScriptOwnedWrappers
{
public:
	void clear();

private:
	ScriptWrapper *m_script;
	ScriptGroupWrapper *m_scriptGroup;
};

extern "C" void __cdecl __identifier("?j_00002338@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00022039@@YAXXZ")();

void BfmeScriptOwnedWrappers::clear()
{
	union { void (*raw)(); void *(ScriptGroupPoolObject::*member)(unsigned); }
		dropGroup = { __identifier("?j_00002338@@YAXXZ") };
	union { void (*raw)(); void *(ScriptPoolObject::*member)(unsigned); }
		dropScript = { __identifier("?j_00022039@@YAXXZ") };
	ScriptGroupWrapper *scriptGroup = m_scriptGroup;
	if (scriptGroup != 0) {
		if (scriptGroup->m_value != 0)
			(scriptGroup->m_value->*dropGroup.member)(1);
		operator delete(scriptGroup);
	}

	ScriptWrapper *script = m_script;
	if (script != 0) {
		if (script->m_value != 0)
			(script->m_value->*dropScript.member)(1);
		operator delete(script);
	}
}
