// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen_00160ec0
{
public:
	int m();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	char m_pad[0x17620];
	int m_difficulty;
};

extern ScriptEngine *TheScriptEngine;

class Rva000C9480
{
	char m_pad[0x220];
	Gen_00160ec0 *m_inner;

public:
	int wrap();
};

int Rva000C9480::wrap()
{
	if (m_inner)
		return m_inner->m();
	return TheScriptEngine->m_difficulty;
}
