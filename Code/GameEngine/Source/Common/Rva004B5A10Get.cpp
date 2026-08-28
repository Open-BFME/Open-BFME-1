// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva004B5A10User
{
	char m_lead[8];
	void *m_field;
};

class Rva004B5A10
{
	GameWindow *m_window;

public:
	void *get();
};

void *Rva004B5A10::get()
{
	return ((Rva004B5A10User *)m_window->winGetUserData())->m_field;
}
