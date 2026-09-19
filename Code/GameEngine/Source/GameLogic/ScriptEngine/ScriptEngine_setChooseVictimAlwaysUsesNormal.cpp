// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;

class ScriptEngine
{
public:
	void setChooseVictimAlwaysUsesNormal(Bool receive);

private:
	unsigned char m_unreconstructed_000[0x17635];
	Bool m_ChooseVictimAlwaysUsesNormal;
};

// ?setChooseVictimAlwaysUsesNormal@ScriptEngine@@QAEX_N@Z
void ScriptEngine::setChooseVictimAlwaysUsesNormal(Bool receive)
{
	m_ChooseVictimAlwaysUsesNormal = receive;
}
