class BfmeViewEUE
{
public:
	char bfmeReadyEUE();

	unsigned char m_bfmeHeadEUE[0x10c];
	int m_bfmeModeEUE;
	int m_bfmeStateEUE;
	unsigned char m_bfmePadAEUE[0xc8];
	char m_bfmeAEUE;
	unsigned char m_bfmePadBEUE[0x27];
	char m_bfmeBEUE;
	unsigned char m_bfmePadCEUE[0x23];
	char m_bfmeCEUE;
	unsigned char m_bfmePadDEUE[0x2b];
	char m_bfmeDEUE;
	unsigned char m_bfmePadEEUE[0x27];
	char m_bfmeEEUE;
	unsigned char m_bfmePadFEUE[0x20d7];
	int *m_bfmeQueueEUE;
};

static __forceinline int bfmeIdleEUE(BfmeViewEUE *v)
{
	if (v->m_bfmeQueueEUE != 0 ||
		v->m_bfmeAEUE != 0 ||
		v->m_bfmeBEUE != 0 ||
		v->m_bfmeCEUE != 0 ||
		v->m_bfmeDEUE != 0 ||
		v->m_bfmeEEUE != 0)
		return 0;

	return 1;
}

char BfmeViewEUE::bfmeReadyEUE()
{
	if (m_bfmeStateEUE == 2)
	{
		int mode = m_bfmeModeEUE;

		if (mode == 7 || mode == 8 || mode == 9 ||
			mode == 10 || mode == 11 || mode == 12)
			return 1;
	}

	return (char)bfmeIdleEUE(this);
}
