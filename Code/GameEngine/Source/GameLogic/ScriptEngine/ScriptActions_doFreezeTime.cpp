// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void doFreezeTime(void);
};

// Retail TheScriptEngine global (DIR32 filled by patcher).
extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
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
