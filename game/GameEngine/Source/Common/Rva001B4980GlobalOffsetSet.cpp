// Open-BFME: global-offset setter reconstructed from retail RVA 0x001B4980.

// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the dword at +0x3C through
// its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class Rva001B4980Global
{
public:
	char m_pad0[0x3C];
	int m_value;
};

class Rva001B4980Object
{
public:
	void set(int first, int second);

private:
	char m_pad0[0x58];
	int m_first;
	int m_second;
};

void Rva001B4980Object::set(int first, int second)
{
	m_first = first;
	m_second = ((Rva001B4980Global *)TheGameLogic)->m_value + second;
}
