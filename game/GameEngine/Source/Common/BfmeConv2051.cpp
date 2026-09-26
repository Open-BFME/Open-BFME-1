class BfmeRefFT
{
public:
	virtual void bfmeReleaseFT();

	int m_bfmeRefFT;
};

class BfmeHostFT
{
public:
	void bfmePopFT();

	unsigned char m_bfmeHeadFT[0x130];
	BfmeRefFT *m_bfmeStackFT[32];
	int m_bfmeCountFT;
	int m_bfmeDepthFT;
};

void BfmeHostFT::bfmePopFT()
{
	if (m_bfmeDepthFT != 0)
	{
		--m_bfmeDepthFT;

		return;
	}

	int i = --m_bfmeCountFT;
	BfmeRefFT *r = m_bfmeStackFT[i];

	if (r == 0)
		return;

	if (--r->m_bfmeRefFT != 0)
		return;

	r->bfmeReleaseFT();
}
