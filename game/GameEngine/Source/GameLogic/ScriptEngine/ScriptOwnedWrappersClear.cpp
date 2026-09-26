// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class ScriptGroupPoolObject
{
public:
	void deleteInstance(int flags);
};

class ScriptPoolObject
{
public:
	void deleteInstance(int flags);
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

void BfmeScriptOwnedWrappers::clear()
{
	ScriptGroupWrapper *scriptGroup = m_scriptGroup;
	if (scriptGroup != 0) {
		if (scriptGroup->m_value != 0)
			scriptGroup->m_value->deleteInstance(1);
		operator delete(scriptGroup);
	}

	ScriptWrapper *script = m_script;
	if (script != 0) {
		if (script->m_value != 0)
			script->m_value->deleteInstance(1);
		operator delete(script);
	}
}
