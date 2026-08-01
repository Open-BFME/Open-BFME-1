// cl: /DNDEBUG /MD /EHsc

class ScriptEngineILT
{
public:
    void doFreezeTime(void);
};

#define TheScriptEngine (*(ScriptEngineILT **)0x012F076C)

class ScriptActions
{
protected:
    void doFreezeTime(void);
};

void ScriptActions::doFreezeTime(void)
{
	TheScriptEngine->doFreezeTime();
}
