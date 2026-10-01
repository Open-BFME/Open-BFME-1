// cl: /O2 /Ob0 /G6

class BfmeObjB3
{
public:
	unsigned bfmeGoB3();
	char m_00[0x54];
	float m_54;
	float m_58;
	float m_5C;
	float m_60;
};

unsigned BfmeObjB3::bfmeGoB3()
{
	double t = 1.0 - m_60;
	t = t * 255.0;
	int v = (int)t;
	if (v > 255)
		v = 255;
	else if (v < 0)
		v = 0;
	float f = (float)v;
	float s = m_54 * m_60;
	int r = (int)(s * 255.0f + f);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	s = m_58 * m_60;
	int g = (int)(s * 255.0f + f);
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	s = m_5C * m_60;
	int b = (int)(s * 255.0f + f);
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	unsigned x = (unsigned)r + 0xFF00;
	x = (x << 8) + (unsigned)g;
	x = (x << 8) + (unsigned)b;
	return x;
}
