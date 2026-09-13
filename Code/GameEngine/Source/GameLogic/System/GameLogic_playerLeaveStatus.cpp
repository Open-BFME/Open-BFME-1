// cl: /O2 /Ob0

// GameLogic's per-player leave status: the accessor, the setter and the reset.
//
// They were three files with three different accounts of the same 0x1C-byte
// struct. getPlayerLeaveStatus called it an opaque `char fields[0x1C]`.
// setPlayerLeaveStatus named the first two Ints and left `char fields[0x14]`
// behind them. resetPlayerLeaveStatus, which touches every field, named all
// eight -- and its account sums to exactly the 0x1C the other two padded past.
// Nothing was wrong in any of them; two simply could not say what they were
// pointing at. Declared once, a modder reading getPlayerLeaveStatus can see
// that the thing it returns tracks quit, defeat and victory frames.
//
// GameLogic split the same way: only setPlayerLeaveStatus knew that the frame
// counter it stamps into quitFrame is the member at +0x3C. The other two padded
// blindly to the array at +0x1B0.

struct PlayerLeaveStatus
{
	int status;						// +0x00
	int quitFrame;						// +0x04
	int defeatFrame;					// +0x08
	int victoryFrame;					// +0x0C
	bool notPresent;					// +0x10
	char padding[3];
	int isHuman;						// +0x14
	char playerName[4];					// +0x18
};

class GameLogic
{
public:
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
	void setPlayerLeaveStatus(int playerIndex, int status);
	void resetPlayerLeaveStatus(void);

private:
	char m_fieldsBeforeFrame[0x3c];
	int m_frame;						// +0x3C
	char m_fieldsBeforeLeaveStatus[0x1b0 - 0x40];
	PlayerLeaveStatus m_playerLeaveStatus[8];		// +0x1B0
};

PlayerLeaveStatus *GameLogic::getPlayerLeaveStatus(int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 8)
		return 0;
	return &m_playerLeaveStatus[playerIndex];
}

void GameLogic::setPlayerLeaveStatus(int playerIndex, int status)
{
	if (playerIndex < 0 || playerIndex >= 8)
		return;

	m_playerLeaveStatus[playerIndex].status = status;
	m_playerLeaveStatus[playerIndex].quitFrame = m_frame;
}

void GameLogic::resetPlayerLeaveStatus(void)
{
	for (int index = 0; index < 8; ++index)
	{
		m_playerLeaveStatus[index].notPresent = true;
		m_playerLeaveStatus[index].quitFrame = 0;
		m_playerLeaveStatus[index].defeatFrame = 0;
		m_playerLeaveStatus[index].victoryFrame = 0;
		m_playerLeaveStatus[index].status = 0;
		m_playerLeaveStatus[index].isHuman = 0xFF;
	}
}
