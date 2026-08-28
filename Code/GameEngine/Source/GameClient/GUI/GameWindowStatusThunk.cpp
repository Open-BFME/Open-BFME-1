// cl: /DNDEBUG /DWIN32 /MD /O2
// Open-BFME5: BFME's GameWindow status field is the dword at this+8.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt _bfme_winSetStatus(UnsignedInt status);

private:
	char m_lead[8];
	UnsignedInt m_status;
};

// @?_bfme_winSetStatus@GameWindow@@QAEII@Z 0x00478420
UnsignedInt GameWindow::_bfme_winSetStatus(UnsignedInt status)
{
	UnsignedInt oldStatus = m_status;
	m_status |= status;
	return oldStatus;
}
