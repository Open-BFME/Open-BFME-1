// cl: /O2 /Ob0

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the dword at +0x3C through
// its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class HoldRva002BC020
{
public:
	char m_lead[0x3C];
	int m_value;
};

class Rva002BC020
{
	char m_lead[0x24];
	int m_field;

public:
	int apply();
};

int Rva002BC020::apply()
{
	m_field = ((HoldRva002BC020 *)TheGameLogic)->m_value + 2;
	return 0;
}
