// cl: /O2 /Ob0

int Rva007EC5C0(char *record, int size, const char *name, int value);

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
	int r = Rva007EC5C0((char *)m_10, m_14, (const char *)x, (int)(f != 0));
	if (r < 0)
		m_24 = -100;
}
