// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: the BFME ScriptEngine flag setter at retail 0x00337070.  The
// release body copies the four-byte incoming bool slot into the four-byte
// storage at +0x17620; retaining that representation is necessary for the
// exact mov/ret sequence rather than narrowing it to a byte store.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void setObjectsShouldReceiveDifficultyBonus( Bool receive );

private:
	unsigned char m_unreconstructed_000[0x17620];
	int m_objectsShouldReceiveDifficultyBonus;
};

// ?setObjectsShouldReceiveDifficultyBonus@ScriptEngine@@QAEX_N@Z
void ScriptEngine::setObjectsShouldReceiveDifficultyBonus( Bool receive )
{
	m_objectsShouldReceiveDifficultyBonus = *(const int *)&receive;
}
