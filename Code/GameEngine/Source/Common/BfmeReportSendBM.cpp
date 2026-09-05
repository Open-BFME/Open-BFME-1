// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the report submit at retail 0x0042B3D0, 71 bytes.  Its own
// parameters are unused: everything submitted comes from the object, and the
// name goes by value.

class StringBaseNarrowBM
{
protected:
	StringBaseNarrowBM(const StringBaseNarrowBM &other) throw();

	~StringBaseNarrowBM(void) throw();

	char *m_bfmeNarrowBM;
};

class AsciiStringBM : public StringBaseNarrowBM
{
public:
	AsciiStringBM(const AsciiStringBM &other) throw() : StringBaseNarrowBM(other)
	{
	}

	~AsciiStringBM(void) throw()
	{
	}
};

class BfmeBlobBM
{
public:
	char m_bfmePadBBM[12];
};

class BfmeSinkBM
{
public:
	void bfmeSubmitBM(AsciiStringBM name, int count, BfmeBlobBM *first,
			BfmeBlobBM *second, BfmeBlobBM *third, BfmeBlobBM *fourth) throw();
};

extern BfmeSinkBM *g_bfmeSinkBM;			// retail 0x012F148C

class BfmeReportBM
{
public:
	void bfmeSendBM(int unusedA, int unusedB);

	char m_bfmePadABM[0xb4];
	AsciiStringBM m_bfmeNameBM;
	int m_bfmeCountBM;
	BfmeBlobBM m_bfmeFirstBM;
	BfmeBlobBM m_bfmeSecondBM;
	BfmeBlobBM m_bfmeThirdBM;
	BfmeBlobBM m_bfmeFourthBM;
};

void BfmeReportBM::bfmeSendBM(int unusedA, int unusedB)
{
	g_bfmeSinkBM->bfmeSubmitBM(m_bfmeNameBM, m_bfmeCountBM,
			&m_bfmeFirstBM, &m_bfmeSecondBM, &m_bfmeThirdBM,
			&m_bfmeFourthBM);
}
