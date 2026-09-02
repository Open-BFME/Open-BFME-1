// cl: /O2

class BfmeMapWV
{
public:
	int lookup(int x, int y, unsigned char flag);
	int find(int key);

private:
	char m_pad00[8];
	int m_w;
	char m_pad0c[0x14];
	int m_limit;
	char m_pad24[0x68];
	short *m_data;
	int *m_a;
	int m_pad94;
	int *m_b;
};

int BfmeMapWV::lookup(int x, int y, unsigned char flag)
{
	int i = m_w * y + x;
	if (i < 0 || i >= m_limit)
		return -1;
	int v = m_data[i];
	if (flag || (m_a[i] == 0 && m_b[i] == 0))
		return find(v);
	return -1;
}
