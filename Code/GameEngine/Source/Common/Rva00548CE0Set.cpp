// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva00548CE0User
{
	char m_lead[0x12];
	unsigned char m_flag;
};

void rva00548ce0(GameWindow *window)
{
	((Rva00548CE0User *)window->winGetUserData())->m_flag = 1;
}
