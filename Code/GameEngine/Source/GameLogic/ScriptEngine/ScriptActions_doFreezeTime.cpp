// cl: /DNDEBUG /MD /EHsc

class ScriptEngine
{
public:
	void doFreezeTime(void);
};

// Retail TheScriptEngine global (DIR32 filled by patcher).
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doFreezeTime(void);
};

// ?doFreezeTime@ScriptActions@@IAEXXZ
void ScriptActions::doFreezeTime(void)
{
	TheScriptEngine->doFreezeTime();
}
