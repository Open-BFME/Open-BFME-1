// ?rva007CBB70@Rva007CBB70ColorFade@@QAEIXZ
// partial score=0.4333 date=2026-09-29
// ?rva007CBB70@Rva007CBB70ColorFade@@QAEIXZ
// cl: /O2 /Ob0 /G6
// BFME retail 1.03 RVA 0x007CBB70 (270 bytes plus the 16-byte jump table).
// A color fade stepper. State 0 fades the level in by 1/60 per call, state 1
// holds it, state 2 fades it out, state 3 rests at zero. The result is the
// stored color scaled by the level, or the color itself at full level.
// No caller or vtable names the owner, so the class and method keep the address.

extern double g_bfmeMulB3;
extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

class RGBColor
{
public:
	float red;
	float green;
	float blue;
	void setFromInt(int color);
};

class Rva007CBB70ColorFade
{
public:
	unsigned int rva007CBB70(void);

private:
	char m_pad00[0x38];
	int m_color;
	char m_pad3c[4];
	int m_state;
	float m_level;
};

unsigned int Rva007CBB70ColorFade::rva007CBB70(void)
{
	switch (m_state)
	{
	case 0:
		m_level += 1.0f / 60.0f;
		if (m_level >= g_bfmeDefaultBU)
		{
			m_level = 1.0f;
			m_state = 1;
		}
		break;
	case 2:
		m_level -= 1.0f / 60.0f;
		if (m_level > BfmeZeroRange)
			break;
		m_state = 3;
	case 3:
		m_level = 0.0f;
		break;
	case 1:
		m_level = 1.0f;
		break;
	}

	if (m_level >= g_bfmeDefaultBU)
		return m_color;
	if (m_level <= BfmeZeroRange)
		return 0;

	RGBColor rgb;
	rgb.setFromInt(m_color);
	rgb.red *= m_level;
	rgb.green *= m_level;
	rgb.blue *= m_level;
	unsigned int color = (int)(rgb.red * g_bfmeMulB3) | 0xffffff00;
	color = (color << 8) | (int)(rgb.green * g_bfmeMulB3);
	color = (color << 8) | (int)(rgb.blue * g_bfmeMulB3);
	return color;
}
