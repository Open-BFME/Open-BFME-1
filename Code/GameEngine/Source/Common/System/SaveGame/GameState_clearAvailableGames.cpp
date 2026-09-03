// cl: /DNDEBUG /MD /EHsc
// readable body of ?clearAvailableGames@GameState@@AAEXXZ: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
struct AvailableGameInfo
{
	char m_data[0x34];
	AvailableGameInfo *next;
	~AvailableGameInfo();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h
class GameState
{
private:
	void clearAvailableGames();

	char m_bfmeLayout[0x50];
	AvailableGameInfo *m_availableGames;
};

void GameState::clearAvailableGames()
{
	while (m_availableGames)
	{
		AvailableGameInfo *next = m_availableGames->next;
		delete m_availableGames;
		m_availableGames = next;
	}
}
