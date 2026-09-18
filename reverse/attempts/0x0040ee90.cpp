// ?d_0040ee90@@YAXXZ
// partial score=0.93 date=2026-09-08
// The owner and member names below are address-derived carriers for the
// witnessed offsets; no BfmeFadeHP identity is asserted.
#define Rva01075350Zero (*(const float *)0x01075350)
#define Rva01075334One (*(const float *)0x01075334)
#define Rva01084068Scale (*(const float *)0x01084068)

class Rva0040E2F0State
{
public:
	void call_0040E2F0(void *o, int k, unsigned int c);

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
};

class Rva0040EE90Owner
{
public:
	void update();

	unsigned char m_000[0x10c];
	volatile int m_10c;
	unsigned char m_110[8];
	float m_118;
	float m_11c;
	Rva0040E2F0State m_120;
};

void Rva0040EE90Owner::update()
{
	unsigned int c = 0xffffff;

	if (m_11c > Rva01075350Zero)
	{
		int v = m_10c;

		if (v != 0)
		{
			v = v - 1;
			m_10c = v;
			bool nonnegative = v >= 0;
			v &= -(int)nonnegative;
			m_10c = v;

			if (v > 0x2d)
			{
				v = 0x2d;
			}
			m_10c = v;

			c = 0xffffffff;
			m_11c = 1.0f;
		}
		else if (m_11c > Rva01075350Zero)
		{
			m_11c = m_11c - m_118;

			if (m_11c <= Rva01075350Zero)
			{
				m_11c = 0;
				m_120.m_00 = 0;
				m_120.m_04 = 0;
				m_120.m_08 = 0;
				m_120.m_0c = 0;
				m_120.m_10 = 0;
				m_120.m_14 = 0;
			}

			float x = (Rva01075334One < m_11c) ? Rva01075334One : m_11c;

			m_11c = x;

			c = ((unsigned int)(int)(x * Rva01084068Scale) << 24) | 0xffffff;
		}

		if (c & 0xff000000)
			m_120.call_0040E2F0(this, 1, c);
	}
}
