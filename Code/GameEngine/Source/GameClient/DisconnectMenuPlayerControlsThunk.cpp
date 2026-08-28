// cl: /DNDEBUG /DWIN32 /MD /O2
// Open-BFME5: per-player control visibility bytes start at this+0x262.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	bool _bfme_arePlayerControlsShown(int slot);

private:
	char m_lead[0x262];
	bool m_playerControlsShown[8];
};

// @?_bfme_arePlayerControlsShown@DisconnectMenu@@QAE_NH@Z 0x0050E6D0
bool DisconnectMenu::_bfme_arePlayerControlsShown(int slot)
{
	return m_playerControlsShown[slot];
}
