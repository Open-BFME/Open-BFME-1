class BfmeSrcGG
{
public:
	unsigned char m_bfmeGapGG[0x64];
	unsigned int m_bfmeBitGG;
};

class BfmeThingGG
{
public:
	void bfmeNotifyGG();

	unsigned char m_bfmeGapGG[0x110];
	int m_bfmeMaskGG[8];
};

class BfmeMaskGG
{
public:
	void bfmeSetBitGG(bool on);

	unsigned char m_bfmeHeadGG[4];
	BfmeSrcGG *m_bfmeSrcGG;
	BfmeThingGG *m_bfmeThingGG;
};

void BfmeMaskGG::bfmeSetBitGG(bool on)
{
	BfmeThingGG *t = m_bfmeThingGG;
	BfmeSrcGG *s = m_bfmeSrcGG;

	if (t != 0 && s != 0)
	{
		unsigned int bit = s->m_bfmeBitGG;

		if (bit != 0xffffffff)
		{
			if (on)
			{
				if ((t->m_bfmeMaskGG[bit >> 5] & (1 << (bit & 0x1f))) == 0)
				{
					t->m_bfmeMaskGG[bit >> 5] |= (1 << (bit & 0x1f));
					t->bfmeNotifyGG();
				}
			}
			else
			{
				if ((t->m_bfmeMaskGG[bit >> 5] & (1 << (bit & 0x1f))) != 0)
				{
					t->m_bfmeMaskGG[bit >> 5] &= ~(1 << (bit & 0x1f));
					t->bfmeNotifyGG();
				}
			}
		}
	}
}
