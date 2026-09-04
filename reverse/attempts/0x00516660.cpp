// ?Rva00516660@@YA_NPAVGameWindow@@@Z
// partial score=0.92 date=2026-09-04
// cl: /O2 /Ob0

// cdecl GameWindow helper @ 0x00516660, 25 bytes.
// Calls winGetUserData (ILT 0x00046538) and returns whether the unsigned
// shorts at user-data +0x1E and +0x1C differ.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva00516660User
{
	char m_lead[0x1C];
	unsigned short m_at1C;
	unsigned short m_at1E;
};

// ?Rva00516660@@YA_NPAVGameWindow@@@Z
bool Rva00516660(GameWindow *window)
{
	Rva00516660User *user = (Rva00516660User *)window->winGetUserData();
	unsigned short a = user->m_at1E;
	return a != user->m_at1C;
}
