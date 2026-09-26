// cl: /DNDEBUG /MD /EHsc
// Address-derived Glo012F1024Type indexed entry selection at retail 0x003B39C0.

class AsciiString;
class Glo012F1024Item;
class BfmeSubYC;
class BfmeElemYC;

class BfmeRoomYC
{
public:
	BfmeRoomYC(const BfmeRoomYC &other);
	~BfmeRoomYC();

	unsigned char m_bfmeBytesYC[0x20];
};

class BfmeSubYC
{
public:
	BfmeRoomYC bfmeRoomYC();
};

extern BfmeRoomYC g_bfmeDefaultYC;

class GlobalData
{
public:
	char m_bfmeHead[0x8E];
	bool m_bfmeStepping;
};

extern GlobalData *TheWritableGlobalData;

class Glo012F1024Entry
{
public:
	Glo012F1024Item *select(AsciiString *key);
	void bfmeStep(void);

	char m_bfmeBody[0x20];
};

class BfmeEntryVector
{
public:
	int bfmeSize(void) const { return (int)(m_bfmeFinish - m_bfmeStart); }
	int bfmeSizeYC(void) const { return (int)(m_bfmeFinish - m_bfmeStart); }

	Glo012F1024Entry *m_bfmeStart;
	Glo012F1024Entry *m_bfmeFinish;
};

class BfmeElemYC
{
public:
	BfmeSubYC *bfmeSubYC(void);

	unsigned char m_bfmePadYC[0x20];
};

class BfmeVecYC
{
public:
	int bfmeSizeYC(void) const { return (int)(m_bfmeEndYC - m_bfmeBeginYC); }

	BfmeElemYC *m_bfmeBeginYC;
	BfmeElemYC *m_bfmeEndYC;
};

class Glo012F1024Type
{
public:
	Glo012F1024Item *selectEntry(AsciiString *key);
	void step(void);
	BfmeRoomYC Rva003B3950Room(void);

private:
	char m_pad00[0x0C];
	int m_bfmeIndex;
	union
	{
		BfmeEntryVector m_bfmeEntries;
		BfmeVecYC m_bfmeVecYC;
	};
	char m_pad18[0x1C - 0x18];
	bool m_at1C;
	bool m_bfmeArmed;
};

// ?selectEntry@Glo012F1024Type@@QAEPAVGlo012F1024Item@@PAVAsciiString@@@Z
Glo012F1024Item *Glo012F1024Type::selectEntry(AsciiString *key)
{
	if (m_bfmeIndex >= 0
		&& (unsigned int)m_bfmeIndex < (unsigned int)m_bfmeEntries.bfmeSize())
	{
		Glo012F1024Entry *start = m_bfmeEntries.m_bfmeStart;
		return start[m_bfmeIndex].select(key);
	}

	return 0;
}

void Glo012F1024Type::step(void)
{
	if (!TheWritableGlobalData->m_bfmeStepping)
		return;

	if (m_bfmeIndex < 0)
		return;

	if ((unsigned int)m_bfmeIndex >= (unsigned int)m_bfmeEntries.bfmeSize())
		return;

	m_bfmeArmed = false;

	m_bfmeEntries.m_bfmeStart[m_bfmeIndex].bfmeStep();
}

#define m_bfmeIndexYC m_bfmeIndex

BfmeRoomYC Glo012F1024Type::Rva003B3950Room(void)
{
	if (m_bfmeIndexYC >= 0
		&& (unsigned int)m_bfmeIndexYC < (unsigned int)m_bfmeVecYC.bfmeSizeYC())
	{
		BfmeElemYC *begin = m_bfmeVecYC.m_bfmeBeginYC;
		BfmeSubYC *sub = begin[m_bfmeIndexYC].bfmeSubYC();
		return sub->bfmeRoomYC();
	}

	return g_bfmeDefaultYC;
}
