// cl: /DNDEBUG /MD /EHsc
//
// ScriptEngine::updateFades, retail 0x003368E0. BFME clears the active flag
// before each interpolation step.

class ScriptEngine
{
protected:
	enum TFade { FADE_NONE, FADE_SUBTRACT, FADE_ADD, FADE_SATURATE, FADE_MULTIPLY };

	void updateFades(void);

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
