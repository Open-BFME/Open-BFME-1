extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

struct GameLogic
{
	char unused[0x3c];
	unsigned int frame;
};
extern GameLogic *TheBfmeGameLogic;

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
			return ((float)TheBfmeGameLogic->frame - m_34) / m_38;
		return BfmeZeroRange;
	case 4:
		return BfmeZeroRange;
	default:
		return BfmeZeroRange;
	}
}
