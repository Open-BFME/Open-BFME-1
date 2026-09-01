// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class W3DDisplay
{
public:
	virtual Bool isLetterBoxFading();

private:
	unsigned char m_retailPad[0xcc];
	float m_letterBoxFadeLevel;
	unsigned char m_letterBoxEnabled;
};

Bool W3DDisplay::isLetterBoxFading()
{
	if (m_letterBoxEnabled && m_letterBoxFadeLevel != 1.0f)
		return 1;
	if (!m_letterBoxEnabled && m_letterBoxFadeLevel != 0.0f)
		return 1;
	return 0;
}
