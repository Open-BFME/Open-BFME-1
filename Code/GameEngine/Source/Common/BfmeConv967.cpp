// Open-BFME5 conversions.

extern char g_bfme967A0[];
extern char g_bfme967A1[];
extern char g_bfme967A2[];
extern char g_bfme967A3[];
extern char g_bfme967A4[];
extern char g_bfme967A5[];
extern char g_bfme967A6[];
extern char g_bfme967A7[];
extern char g_bfme967A8[];
extern char g_bfme967A9[];
extern char g_bfme967A10[];

class BfmeVft967A
{
public:
	void bfmeGo967A();
	void bfmeBase967A();
	char *volatile m_bfmeSlot0;
	char m_bfmePad0[0x8];
	char *volatile m_bfmeSlot1;
	char *volatile m_bfmeSlot2;
	char m_bfmePad1[0xc];
	char *volatile m_bfmeSlot3;
	char *volatile m_bfmeSlot4;
	char *volatile m_bfmeSlot5;
	char *volatile m_bfmeSlot6;
	char *volatile m_bfmeSlot7;
	char *volatile m_bfmeSlot8;
	char m_bfmePad2[0x9c];
	char *volatile m_bfmeSlot9;
	char m_bfmePad3[0xc];
	char *volatile m_bfmeSlot10;
};

void BfmeVft967A::bfmeGo967A()
{
	m_bfmeSlot0 = g_bfme967A0;
	m_bfmeSlot1 = g_bfme967A1;
	m_bfmeSlot2 = g_bfme967A2;
	m_bfmeSlot3 = g_bfme967A3;
	m_bfmeSlot4 = g_bfme967A4;
	m_bfmeSlot5 = g_bfme967A5;
	m_bfmeSlot6 = g_bfme967A6;
	m_bfmeSlot7 = g_bfme967A7;
	m_bfmeSlot8 = g_bfme967A8;
	m_bfmeSlot9 = g_bfme967A9;
	m_bfmeSlot10 = g_bfme967A10;
	bfmeBase967A();
}
