// ?setFade@ScriptEngine@@IAEXPAVScriptAction@@@Z
// partial score=0.88 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
//
// ScriptEngine::setFade, retail RVA 0x003369D0.  The reference implementation
// is GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp.
// The BFME ScriptAction and Parameter views below retain their independently
// observed retail offsets: the action type is at +4, parameter count at +8,
// parameter pointers at +0xC, and each parameter value at +0xC.

typedef bool Bool;
typedef int Int;
typedef float Real;

class Parameter
{
	char m_prefix[8];
	Int m_int;
	Real m_real;

public:
	Int getInt(void) const { return m_int; }
	Real getReal(void) const { return m_real; }
};

class ScriptAction
{
	char m_vtable[4];
	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[12];

public:
	enum ScriptActionType
	{
		CAMERA_FADE_ADD = 0x7C,
		CAMERA_FADE_SUBTRACT,
		CAMERA_FADE_SATURATE,
		CAMERA_FADE_MULTIPLY
	};

	ScriptActionType getActionType(void) { return (ScriptActionType)m_actionType; }
	Int getNumParameters(void) { return m_numParms; }
	Parameter *getParameter(Int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}
};

class ScriptEngine
{
protected:
	enum TFade
	{
		FADE_NONE,
		FADE_SUBTRACT,
		FADE_ADD,
		FADE_SATURATE,
		FADE_MULTIPLY
	};

	__declspec(noinline) void updateFades(void);

private:
	unsigned char m_unknown[0x170B4];
	TFade m_fade;
	Bool m_fadeActive;
	Real m_minFade;
	Real m_maxFade;
	Real m_curFadeValue;
	Int m_curFadeFrame;
	Int m_fadeFramesIncrease;
	Int m_fadeFramesHold;
	Int m_fadeFramesDecrease;

protected:
	void setFade(ScriptAction *pAction);
};

__declspec(noinline) void ScriptEngine::updateFades(void)
{
	m_curFadeFrame++;
	Int fade = m_curFadeFrame;
	m_fadeActive = false;
	Real factor;
	if (fade <= m_fadeFramesIncrease)
	{
		factor = (Real)m_curFadeFrame / m_fadeFramesIncrease;
		m_curFadeValue = m_minFade + factor * (m_maxFade - m_minFade);
		return;
	}
	fade -= m_fadeFramesIncrease;
	if (fade <= m_fadeFramesHold)
	{
		m_curFadeValue = m_maxFade;
		return;
	}
	fade -= m_fadeFramesHold;
	if (fade <= m_fadeFramesDecrease)
	{
		Int divisor = m_fadeFramesDecrease + 1;
		if (divisor == 0)
			divisor = 1;
		factor = (Real)fade / divisor;
		m_curFadeValue = m_maxFade + factor * (m_minFade - m_maxFade);
		return;
	}
	m_fade = FADE_NONE;
}

// ?setFade@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::setFade(ScriptAction *pAction)
{
	switch (pAction->getActionType())
	{
		default:
			m_fade = FADE_NONE;
			return;
		case ScriptAction::CAMERA_FADE_ADD:
			m_fade = FADE_ADD;
			break;
		case ScriptAction::CAMERA_FADE_SUBTRACT:
			m_fade = FADE_SUBTRACT;
			break;
		case ScriptAction::CAMERA_FADE_SATURATE:
			m_fade = FADE_SATURATE;
			break;
		case ScriptAction::CAMERA_FADE_MULTIPLY:
			m_fade = FADE_MULTIPLY;
			break;
	}

	m_curFadeFrame = 0;
	m_minFade = pAction->getParameter(0)->getReal();
	m_maxFade = pAction->getParameter(1)->getReal();
	m_fadeFramesIncrease = pAction->getParameter(2)->getInt();
	m_fadeFramesHold = pAction->getParameter(3)->getInt();
	m_fadeFramesDecrease = pAction->getParameter(4)->getInt();
	m_curFadeValue = m_minFade;
	if (m_fadeFramesIncrease == 0)
		updateFades();
	m_fadeActive = true;
}
