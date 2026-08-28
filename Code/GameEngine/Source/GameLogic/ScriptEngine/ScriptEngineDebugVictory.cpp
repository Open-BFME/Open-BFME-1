// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

class ScriptAction
{
public:
	enum ScriptActionType
	{
		VICTORY = 3
	};

	ScriptAction(ScriptActionType type);

private:
	char m_data[0x48];
};

class ScriptActions
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void executeAction(ScriptAction *action);
};

class ScriptEngine
{
public:
	void debugVictory(void);
};

#define TheScriptActions (*(ScriptActions **)0x012F0620)

void ScriptEngine::debugVictory(void)
{
	ScriptAction *action = new ScriptAction(ScriptAction::VICTORY);
	TheScriptActions->executeAction(action);
}
