class BfmeEntryJP
{
public:
	unsigned char m_bfmeHeadJP[8];
	int m_bfmeValueJP;
	unsigned char m_bfmeTailJP[0xc];
};

void __cdecl bfmeSendJP(void *sink, int *values, int count);

class BfmeOwnerJP
{
public:
	BfmeEntryJP *bfmeAtJP(int index)
	{
		if (index < 0 || index >= m_bfmeCountJP)
			return 0;

		return &m_bfmeEntriesJP[index];
	}

	void bfmeFlushJP(void *sink);

	unsigned char m_bfmeHeadJP[0x28];
	int m_bfmeCountJP;
	BfmeEntryJP m_bfmeEntriesJP[1];
};

void BfmeOwnerJP::bfmeFlushJP(void *sink)
{
	int values[32];
	int index;

	for (index = 0; index < m_bfmeCountJP; index++)
		values[index] = bfmeAtJP(index)->m_bfmeValueJP;

	bfmeSendJP(sink, values, m_bfmeCountJP);
}
