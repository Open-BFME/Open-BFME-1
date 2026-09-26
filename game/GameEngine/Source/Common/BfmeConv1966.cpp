struct BfmePairESA
{
	int m_bfmeAESA;
	int m_bfmeBESA;
};

class BfmeStrESA
{
public:
	void bfmeSetESA(const BfmeStrESA &other);

	void *m_bfmeDataESA;
};

extern BfmeStrESA g_bfmeDefaultESA;

class BfmeRecESA
{
public:
	BfmePairESA bfmeRangeESA();

	unsigned char m_bfmeHeadESA[0xb8];
	BfmeStrESA m_bfmeTextESA;
};

class BfmeKeyESA
{
public:
	unsigned char m_bfmeBodyESA[4];
};

class BfmeOwnerESA
{
public:
	BfmeRecESA *bfmeFindESA(BfmeKeyESA *key);
};

class BfmeHostESA
{
public:
	void bfmeGetESA(BfmeStrESA *out, BfmePairESA *range);

	unsigned char m_bfmeHeadESA[0x28];
	BfmeOwnerESA *m_bfmeOwnerESA;
	unsigned char m_bfmeMidESA[4];
	BfmeKeyESA m_bfmeKeyESA;
};

void BfmeHostESA::bfmeGetESA(BfmeStrESA *out, BfmePairESA *range)
{
	BfmeRecESA *rec = m_bfmeOwnerESA->bfmeFindESA(&m_bfmeKeyESA);

	if (rec == 0)
	{
		out->bfmeSetESA(g_bfmeDefaultESA);

		range->m_bfmeAESA = 0;
		range->m_bfmeBESA = 0;
	}

	out->bfmeSetESA(rec->m_bfmeTextESA);

	*range = rec->bfmeRangeESA();
}
