// Open-BFME: recovered mode-latch wrapper at retail 0x002F1150 (42 bytes).

typedef unsigned char Byte;

// TU-local view of the canonical GameLogic (GameLogic.cpp); the real class is
// only forward declared here, so every field read casts through this view.
class Rva0038AD90GameLogic
{
public:
	void setObjectIndicators(bool enabled);

	unsigned char m_before114[0x114];
	unsigned char m_modeLatch;
};

class GameLogic;

extern GameLogic *TheGameLogic;

// ?func002F1150@@YGXH@Z
void __stdcall func002F1150(int mode)
{
	if (((Rva0038AD90GameLogic *)TheGameLogic)->m_modeLatch != (Byte)mode)
	{
		union RawBool
		{
			int integer;
			bool boolean;
		} raw;
		raw.integer = mode;
		((Rva0038AD90GameLogic *)TheGameLogic)->setObjectIndicators(
			raw.boolean);
		((Rva0038AD90GameLogic *)TheGameLogic)->m_modeLatch = mode;
	}
}
