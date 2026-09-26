// cl: /O2

class BfmeMapWU
{
public:
	unsigned char sample(int x, int y, int a, int b, int c);
	unsigned char help(int idx, short v, int a, int b, int c);

private:
	char m_pad00[8];
	int m_w;
	char m_pad0c[0x14];
	int m_limit;
	char m_pad24[0x68];
	short *m_data;
	char m_pad90[0x12050];
	int m_e0;
	int m_e4;
};

unsigned char BfmeMapWU::sample(int x, int y, int a, int b, int c)
{
	int i = (m_e4 + y) * m_w + m_e0 + x;
	if (i < m_limit)
	{
		if (m_data)
			return help(i, m_data[i], a, b, c);
	}
	return 0;
}
