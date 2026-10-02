extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  This TU keeps its
// own frame-word view of the pointee and casts at the use.
class GameLogic;
extern GameLogic *TheGameLogic;

struct GameLogicFrameView
{
	char unused[0x3c];
	unsigned int frame;
};

struct Rva002A11F0ModeProgress
{
	char opaque[0x2c];
	unsigned int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	float value(int *out) const;
};

float Rva002A11F0ModeProgress::value(int *out) const
{
	if (out)
		*out = m_3c;
	switch (m_2c)
	{
	case 0:
		return BfmeZeroRange;
	case 1:
		return g_bfmeDefaultBU;
	case 2:
		return BfmeZeroRange;
	case 3:
		if (m_38 > 0)
			return ((float)reinterpret_cast<GameLogicFrameView *>(TheGameLogic)->frame - m_34) / m_38;
		return BfmeZeroRange;
	case 4:
		return BfmeZeroRange;
	default:
		return BfmeZeroRange;
	}
}
