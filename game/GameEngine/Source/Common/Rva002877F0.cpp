// cl: /O2 /DNDEBUG /MD
// Retail 0x002877F0 is a free helper with two stack arguments. The retail
// fields match the BoneFX random-delay layout, but no owner identity is known.

class GameLogicRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class GameLogic
{
public:
	unsigned int getFrame() const
	{
		return m_frame;
	}

private:
	char m_padding[0x3c];
	unsigned int m_frame;
};

struct Rva002877F0Info
{
	char m_prefix[0x10];
	GameLogicRandomVariable m_gameLogicDelay;
	bool m_onlyOnce;
};

#define TheGameLogic (*(GameLogic **)0x012f0898)

#pragma comment(linker, "/alternatename:?getValue@GameLogicRandomVariable@@QBEMXZ=?j_000188cc@@YAXXZ")

void __stdcall Rva002877F0(void *rawInfo, int *nextFrame)
{
	Rva002877F0Info *info = (Rva002877F0Info *)rawInfo;
	if (info->m_onlyOnce)
		*nextFrame = -1;
	else
		*nextFrame = TheGameLogic->getFrame() + (int)info->m_gameLogicDelay.getValue();
}
