// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

enum { MAX_PARMS = 12 };

class Parameter;

class ScriptAction
{
public:
	enum ScriptActionType
	{
		NO_OP = 5
	};

	virtual ~ScriptAction();
	ScriptAction(ScriptActionType type);
	void setActionType(ScriptActionType type);

private:
	ScriptActionType m_actionType;
	int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	bool m_hasWarnings;
	int m_bfmeActionTail;
};

ScriptAction::ScriptAction(ScriptActionType type):
m_numParms(0),
m_nextAction(0),
m_hasWarnings(false),
m_bfmeActionTail(0)
{
	int i;
	for (i = 0; i < MAX_PARMS; i++) {
		m_parms[i] = 0;
	}
	setActionType(type);
}
