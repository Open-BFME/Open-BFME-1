class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int Rva007EC5C0(char *record, int size, const char *name, int value);

void BfmeThingCIB::bfmeGoCIB(void *one, void *two)
{
	if (Rva007EC5C0((char *)m_bfmeA, (int)(size_t)m_bfmeB, (const char *)one, (int)(size_t)two) < 0)
		m_bfmeErr = -100;
}
