// Open-BFME: recovered mode-latch wrapper at retail 0x002F1150 (42 bytes).

typedef unsigned char Byte;

class Rva0038AD90GameLogic
{
public:
	void setObjectIndicators(bool enabled);

	unsigned char m_before114[0x114];
	unsigned char m_modeLatch;
};

extern Rva0038AD90GameLogic *TheGameLogic;

// ?func002F1150@@YGXH@Z
void __stdcall func002F1150(int mode)
{
	if (TheGameLogic->m_modeLatch != (Byte)mode)
	{
		union RawBool
		{
			int integer;
			bool boolean;
		} raw;
		raw.integer = mode;
		TheGameLogic->setObjectIndicators(raw.boolean);
		TheGameLogic->m_modeLatch = mode;
	}
}
