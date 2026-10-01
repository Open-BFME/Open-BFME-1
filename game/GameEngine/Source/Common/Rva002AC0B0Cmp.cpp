// cl: /O2 /Ob0

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the frame field at +0x3C
// through its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

struct Rva002AC0B0Global
{
	char m_lead[0x3C];
	unsigned m_frame;
};

class Rva002AC0B0
{
	char m_lead[0x28];
	unsigned m_value;

public:
	unsigned char cmp();
};

unsigned char Rva002AC0B0::cmp()
{
	return ((Rva002AC0B0Global *)TheGameLogic)->m_frame >= m_value;
}
