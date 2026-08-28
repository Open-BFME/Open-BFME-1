class BfmeThingCFA
{
public:
	void bfmeGoCFA();
	unsigned char m_bfmeHead[4];
	char *m_bfmePtr;
	unsigned char m_bfmeGap[4];
	char *m_bfmeEnd;
};

void bfmeFreeBigCFA(char *ptr);
void bfmeFreeSmallCFA(char *ptr, unsigned int size);

void BfmeThingCFA::bfmeGoCFA()
{
	char *ptr = m_bfmePtr;
	unsigned int size = m_bfmeEnd - ptr;
	if (ptr != 0)
	{
		if (size > 0x80)
			bfmeFreeBigCFA(ptr);
		else
			bfmeFreeSmallCFA(ptr, size);
	}
}
