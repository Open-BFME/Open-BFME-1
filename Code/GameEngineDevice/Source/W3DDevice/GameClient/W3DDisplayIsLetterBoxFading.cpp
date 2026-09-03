// cl: /DNDEBUG /MD /EHsc
// readable body of ?isLetterBoxFading@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
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
