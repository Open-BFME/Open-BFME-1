// ?bfmeGetJD@BfmeArrJD@@QAEXPAVBfmeBlobJD@@H@Z
// partial score=0.85 date=2026-09-08
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeBlobJD
{
public:
	BfmeBlobJD()
	{
		bfmeClearJD();
	}

	void bfmeClearJD()
	{
		volatile int *p = (volatile int *)&m_bfmeF0JD;

		p[0] = 0;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0;
		p[4] = 0;
		p[5] = 0;
		p[6] = 0;
		p[7] = 0;
		p[8] = 0;
		p[9] = 0;
	}

	int m_bfmeF0JD;
	int m_bfmeF1JD;
	int m_bfmeF2JD;
	int m_bfmeF3JD;
	int m_bfmeF4JD;
	int m_bfmeF5JD;
	int m_bfmeF6JD;
	int m_bfmeF7JD;
	int m_bfmeF8JD;
	int m_bfmeF9JD;
};

class BfmeEntryJD
{
public:
	unsigned char m_bfmeHeadJD[0x44];
	BfmeBlobJD m_bfmeBlobJD;
};

class BfmeArrJD
{
public:
	void bfmeGetJD(BfmeBlobJD *dst, int index);

	unsigned char m_bfmeHeadJD[8];
	BfmeEntryJD **m_bfmeBeginJD;
	BfmeEntryJD **m_bfmeEndJD;
};

void BfmeArrJD::bfmeGetJD(BfmeBlobJD *dst, int index)
{
	BfmeBlobJD zero;

	memset(&zero, 0, sizeof(zero));

	if (index >= 0)
	{
		int last = (int)(m_bfmeEndJD - m_bfmeBeginJD) - 1;

		if ((unsigned int)index <= (unsigned int)last)
		{
			BfmeEntryJD *e = m_bfmeBeginJD[index];

			if (e != 0)
			{
				*dst = e->m_bfmeBlobJD;
				return;
			}
		}
	}

	*dst = zero;
}
