class BfmeAttrERT
{
public:
	BfmeAttrERT(const BfmeAttrERT &other);
	~BfmeAttrERT();

	unsigned char m_bfmeHeadERT[0x80];
	char m_bfmeFlagERT;
	unsigned char m_bfmeTailERT[7];
};

struct BfmeAttrPoolERT
{
	BfmeAttrERT *m_bfmeFirstERT;
	BfmeAttrERT *m_bfmeLastERT;
};

extern BfmeAttrPoolERT g_bfmeAttrPoolERT;

class BfmeHostERT
{
public:
	char bfmeQueryERT();

	int m_bfmeIndexERT;
};

char BfmeHostERT::bfmeQueryERT()
{
	int index = m_bfmeIndexERT;

	if (index >= 0 &&
		index < (int)(g_bfmeAttrPoolERT.m_bfmeLastERT - g_bfmeAttrPoolERT.m_bfmeFirstERT))
	{
		BfmeAttrERT copy(g_bfmeAttrPoolERT.m_bfmeFirstERT[index]);

		if (copy.m_bfmeFlagERT != 0)
			return 1;
	}

	return 0;
}
