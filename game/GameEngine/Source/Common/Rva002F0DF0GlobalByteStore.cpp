// Open-BFME: global byte store reconstructed from retail RVA 0x002F0DF0.

class Rva002F0DF0Global
{
public:
	char m_pad0[0xBD];
	unsigned char m_flag;
};

// 0x012F1464 is retail's `GameClient *TheGameClient;` (defined once in
// game/GameEngine/Source/GameClient/GameClient.cpp). The pointee is seen here
// through a TU-local view; the reference itself carries the canonical spelling.
class GameClient;

extern GameClient *TheGameClient;

void __stdcall Rva002F0DF0Store(unsigned char value)
{
	((Rva002F0DF0Global *)TheGameClient)->m_flag = value;
}
