class BfmeThingCFB
{
public:
	void bfmeGoCFB();
	unsigned char m_bfmeHead[4];
	char *m_bfmePtr;
	unsigned char m_bfmeGap[4];
	char *m_bfmeEnd;
};

void bfmeFreeBigCFB(char *ptr);
void bfmeFreeSmallCFB(char *ptr, unsigned int size);

void BfmeThingCFB::bfmeGoCFB()
{
	char *ptr = m_bfmePtr;
	unsigned int size = m_bfmeEnd - ptr;
	if (ptr != 0)
	{
		if (size > 0x80)
			bfmeFreeBigCFB(ptr);
		else
			bfmeFreeSmallCFB(ptr, size);
	}
}
