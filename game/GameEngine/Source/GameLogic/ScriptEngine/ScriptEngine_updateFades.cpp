// cl: /DNDEBUG /MD /EHsc
//
// ScriptEngine::updateFades, retail 0x003368E0. BFME clears the active flag
// before each interpolation step. The camera-fade setter at 0x003369D0 that
// calls it lives here too.

// Retail offsets: ScriptAction type +4, parameter count +8, parameters +0xC;
// Parameter int +8, real +0xC.
class Parameter
{
	char m_prefix[8];
	int m_int;
	float m_real;

public:
	int getInt(void) const { return m_int; }
	float getReal(void) const { return m_real; }
};

class ScriptAction
{
	char m_vtable[4];
	int m_actionType;
	int m_numParms;
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
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}
};

class ScriptEngine
{
protected:
	enum TFade { FADE_NONE, FADE_SUBTRACT, FADE_ADD, FADE_SATURATE, FADE_MULTIPLY };

	void updateFades(void);
	void Rva003369d0(ScriptAction *pAction);

private:
	unsigned char m_unknown[0x170b4];
	int m_fade;
	bool m_fadeActive;
	float m_minFade;
	float m_maxFade;
	float m_curFadeValue;
	int m_curFadeFrame;
	int m_fadeFramesIncrease;
	int m_fadeFramesHold;
	int m_fadeFramesDecrease;
};

// ?updateFades@ScriptEngine@@IAEXXZ
void ScriptEngine::updateFades(void)
{
	m_curFadeFrame++;
	int fade = m_curFadeFrame;
	m_fadeActive = false;
	float factor;
	if (fade <= m_fadeFramesIncrease)
	{
		factor = (float)m_curFadeFrame / m_fadeFramesIncrease;
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
		int divisor = m_fadeFramesDecrease + 1;
		if (divisor == 0)
			divisor = 1;
		factor = (float)fade / divisor;
		m_curFadeValue = m_maxFade + factor * (m_minFade - m_maxFade);
		return;
	}
	m_fade = FADE_NONE;
}

// Retail 0x003369D0 (245 B plus its 16-byte case table), reached from
// executeActions through ILT 0x00049963; ZH's setFade with BFME's active
// flag. ilt_oracle contradicts every setFade spelling, so it keeps the pinned
// address name. Setting the flag in both arms of the updateFades test is what
// makes VC7.1 keep the constant 1 in EBX (case store, count compare, flag)
// like retail; one shared store after the if leaves three immediates.
// ?Rva003369d0@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::Rva003369d0(ScriptAction *pAction)
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
	{
		updateFades();
		m_fadeActive = true;
	}
	else
		m_fadeActive = true;
}
