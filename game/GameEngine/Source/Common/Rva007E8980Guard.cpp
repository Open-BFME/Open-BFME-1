// cl: /O2 /Ob0

int bfmeCallCIB(void *a, void *b, void *c, void *d);

class Rva007E8980
{
public:
	void go(int x, unsigned char f);

private:
	char m_pad[0x10];
	int m_10;
	int m_14;
	char m_pad18[0x0c];
	int m_24;
};

void Rva007E8980::go(int x, unsigned char f)
{
	int r = bfmeCallCIB((void *)m_10, (void *)m_14, (void *)x, (void *)(f != 0));
	if (r < 0)
		m_24 = -100;
}
