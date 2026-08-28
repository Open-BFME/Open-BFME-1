// cl: /DNDEBUG /MD /EHsc

// BFME ScriptAction::ScriptAction(), the protected read constructor.
//
// Two things differ from Zero Hour, and both are read off the retail bytes at
// 0x0034FF60: the body clears all twelve m_parms slots (ZH's protected ctor is
// empty; only the type-taking one clears them), and the init list ends with a
// dword store at +0x44, one past where ZH's class ends. That last member is
// unidentified, so it sits after the last ZH member where it shifts nothing.
//
// The class is declared TU-locally rather than by editing the shared
// reference/shims/scriptenginevtable copy of Scripts.h: this body only needs
// the layout, and a shim-header edit forces the full gate, which master
// currently fails on a ??_7DebugDisplay@@6B@ address split that predates this
// work (landed with ??1W3DDebugDisplay@@UAE@XZ in 61a3a324f).

enum { MAX_PARMS = 12 };

class Parameter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	virtual ~ScriptAction();

protected:
	ScriptAction();

	int							m_actionType;			// +0x04, NO_OP is ordinal 5
	int							m_numParms;				// +0x08
	Parameter *				m_parms[MAX_PARMS];	// +0x0c .. +0x38
	ScriptAction *			m_nextAction;			// +0x3c
	bool						m_hasWarnings;			// +0x40
	int							m_bfmeActionTail;		// +0x44
};

ScriptAction::ScriptAction():
m_actionType(5),
m_numParms(0),
m_nextAction(0),
m_hasWarnings(false),
m_bfmeActionTail(0)
{
	int i;
	for (i = 0; i < MAX_PARMS; i++) {
		m_parms[i] = 0;
	}
}
