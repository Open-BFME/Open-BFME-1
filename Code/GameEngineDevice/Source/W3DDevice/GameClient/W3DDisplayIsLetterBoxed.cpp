// cl: /DNDEBUG /MD /EHsc
// readable body of ?isLetterBoxed@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	virtual bool isLetterBoxed();

private:
	unsigned char m_retailPad[0xd0];
	bool m_letterBoxEnabled;
};

bool W3DDisplay::isLetterBoxed()
{
	return m_letterBoxEnabled;
}
