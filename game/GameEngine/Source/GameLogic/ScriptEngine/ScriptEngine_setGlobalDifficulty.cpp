// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// ScriptEngine::setGlobalDifficulty, retail 0x00337070 (13 bytes). The body
// stores the incoming GameDifficulty dword at +0x17620: ZH's ScriptEngine has
// m_gameDifficulty (a GameDifficulty) immediately before m_freezeByScript, and
// BFME+0x17620 is ZH+0x10DB8 after the proven +0x6868 pre-freezeByScript delta
// (inputs/reference/shims/scriptenginelayout/GameLogic/ScriptEngine.h). ZH
// declares the setter out-of-line; the enum spelling is oracle-CONFIRMED at
// this address while bool/int spellings are contradicted. Three named retail
// callers reach it through ILT 0x000126BB, all in difficulty contexts:
// GameLogic::prepareNewGame, DifficultySelectSystem, bfmeShutdownAAV.

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void setGlobalDifficulty(GameDifficulty difficulty);

private:
	unsigned char m_unreconstructed_000[0x17620];
	GameDifficulty m_gameDifficulty;
};

// ?setGlobalDifficulty@ScriptEngine@@QAEXW4GameDifficulty@@@Z
void ScriptEngine::setGlobalDifficulty(GameDifficulty difficulty)
{
	m_gameDifficulty = difficulty;
}
