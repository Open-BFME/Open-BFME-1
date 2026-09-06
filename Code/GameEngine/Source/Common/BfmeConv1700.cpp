struct BfmeEntryFQ
{
	unsigned char m_bfmeHeadFQ[0xe];
	short m_bfmeShortFQ;
	unsigned char m_bfmeTailFQ[4];
};

class BfmeTableFQ
{
public:
	int bfmeAdvanceFQ(int index, int arg);

	unsigned char m_bfmeDataFQ[4];
};

class BfmeStateFQ
{
public:
	unsigned char m_bfmeHeadFQ[4];
	int m_bfmeIndexFQ;
	int m_bfmeValueFQ;
};

class BfmeThingFQ
{
public:
	void bfmeStepFQ(BfmeStateFQ *state, int arg);

	unsigned char m_bfmeHeadFQ[0x2c];
	BfmeTableFQ m_bfmeTableFQ;
	unsigned char m_bfmeMidFQ[8];
	BfmeEntryFQ *m_bfmeEntriesFQ;
};

void BfmeThingFQ::bfmeStepFQ(BfmeStateFQ *state, int arg)
{
	int current = state->m_bfmeIndexFQ;
	int index = m_bfmeTableFQ.bfmeAdvanceFQ(current, arg);
	state->m_bfmeIndexFQ = index;
	state->m_bfmeValueFQ = m_bfmeEntriesFQ[index].m_bfmeShortFQ;
}

class BfmeTableFR
{
public:
	int bfmeAdvanceFR(int index, int arg);

	unsigned char m_bfmeDataFR[4];
};

class BfmeThingFR
{
public:
	void bfmeStepFR(BfmeStateFQ *state, int arg);

	unsigned char m_bfmeHeadFR[0xc];
	BfmeTableFR m_bfmeTableFR;
	unsigned char m_bfmeMidFR[8];
	BfmeEntryFQ *m_bfmeEntriesFR;
};

void BfmeThingFR::bfmeStepFR(BfmeStateFQ *state, int arg)
{
	int current = state->m_bfmeIndexFQ;
	int index = m_bfmeTableFR.bfmeAdvanceFR(current, arg);
	state->m_bfmeIndexFQ = index;
	state->m_bfmeValueFQ = m_bfmeEntriesFR[index].m_bfmeShortFQ;
}
