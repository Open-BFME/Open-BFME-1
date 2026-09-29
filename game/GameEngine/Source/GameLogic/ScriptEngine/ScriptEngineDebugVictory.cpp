// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	enum ScriptActionType
	{
		VICTORY = 3,
		DEFEAT = 4
	};

	ScriptAction(ScriptActionType type);

private:
	char m_data[0x48];
};

// The image declares the global at 0x012F0620 as a ScriptActionsInterface
// pointer, so the extern carries that exact type (and the vtable slot index
// of executeAction stays where the literal load put it).
class ScriptActionsInterface
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void executeAction(ScriptAction *action);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions : public ScriptActionsInterface
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void debugVictory(void);
	void debugDefeat(void);
};

// retail 0x012F0620: ?TheScriptActions@@3PAVScriptActionsInterface@@A
extern ScriptActionsInterface *TheScriptActions;

void ScriptEngine::debugVictory(void)
{
	ScriptAction *action = new ScriptAction(ScriptAction::VICTORY);
	TheScriptActions->executeAction(action);
}

void ScriptEngine::debugDefeat(void)
{
	ScriptAction *action = new ScriptAction(ScriptAction::DEFEAT);
	TheScriptActions->executeAction(action);
}
