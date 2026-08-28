class BfmeThingBZD
{
public:
	void bfmeGoBZD(const char *text, int value);
	unsigned char m_bfmeHead[0x50];
	char m_bfmeBuf[0x80];
	int m_bfmeVal;
};

void bfmeCopyBZD(char *dest, const char *text, unsigned int size);

void BfmeThingBZD::bfmeGoBZD(const char *text, int value)
{
	bfmeCopyBZD(m_bfmeBuf, text, 0x40);
	m_bfmeVal = value;
}
