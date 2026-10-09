// The direct retail call is the matched FESL key-index helper at 0x007F76F0.
struct Rva007F76F0Vector;
class Rva00802240Host
{
public:
	int rva007F76F0(Rva007F76F0Vector *vector, const char *name);
};

class BfmeVecFN
{
public:
	int m_bfmeDummyZL;
};

class BfmeTableZL
{
public:
	unsigned char m_bfmeHeadZL[0x2b0];
	BfmeVecFN m_bfme2B0ZL;
};

class BfmeHostZL
{
public:
	void *bfmeLookupZL(const char *name);

	unsigned char m_bfmeHeadHZL[4];
	BfmeTableZL *m_bfme04ZL;
	unsigned char m_bfmeGapZL[0x30];
	void **m_bfme38ZL;
};

void *BfmeHostZL::bfmeLookupZL(const char *name)
{
	if (m_bfme38ZL)
	{
		int i = ((Rva00802240Host *)m_bfme04ZL)->rva007F76F0(
			(Rva007F76F0Vector *)&m_bfme04ZL->m_bfme2B0ZL, name);

		if (i != -1)
			return m_bfme38ZL[i];
	}

	return 0;
}
