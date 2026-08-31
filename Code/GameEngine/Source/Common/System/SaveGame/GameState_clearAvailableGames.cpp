// cl: /DNDEBUG /MD /EHsc

struct AvailableGameInfo
{
	char m_data[0x34];
	AvailableGameInfo *next;
	~AvailableGameInfo();
};

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
