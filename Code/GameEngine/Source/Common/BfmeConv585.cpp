class BfmeThingCEB
{
public:
	void bfmeGoCEB(const char *text, int value);
	unsigned char m_bfmeHead[0x90];
	char m_bfmeBuf[0x44];
	int m_bfmeVal;
};

void bfmeCopyCEB(char *dest, const char *text, unsigned int size);

void BfmeThingCEB::bfmeGoCEB(const char *text, int value)
{
	bfmeCopyCEB(m_bfmeBuf, text, 0x40);
	m_bfmeVal = value;
}
