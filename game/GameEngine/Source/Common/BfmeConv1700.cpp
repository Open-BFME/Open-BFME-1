struct BfmeEntryFQ
{
	unsigned char m_bfmeHeadFQ[0xe];
	short m_bfmeShortFQ;
	struct BfmeNodeFQ *m_bfmeNodesFQ;
};

struct BfmeNodeFQ
{
	BfmeNodeFQ *m_bfmeNextFQ;
};

class AsciiString;

class BfmeTableFQ;

class Rva0035D2B0StringRecordTable
{
	friend class BfmeTableFQ;

	int findOrCreateIndex(AsciiString *name);

public:
	void release(int index);
};

class BfmeTableFQ
{
public:
	int bfmeAdvanceFQ(int index, AsciiString *name);

	unsigned char m_bfmeDataFQ[0x0c];
	BfmeEntryFQ *m_bfmeEntriesFQ;
};

int BfmeTableFQ::bfmeAdvanceFQ(int index, AsciiString *name)
{
	int next = reinterpret_cast<Rva0035D2B0StringRecordTable *>(this)->
		findOrCreateIndex(name);
	if (next == -1)
		return index;

	BfmeNodeFQ *node;
	{
		BfmeEntryFQ *entries = m_bfmeEntriesFQ;
		BfmeEntryFQ *source = &entries[index];
		node = source->m_bfmeNodesFQ;
		source->m_bfmeNodesFQ = node->m_bfmeNextFQ;
	}
	{
		BfmeEntryFQ *entries = m_bfmeEntriesFQ;
		BfmeEntryFQ *destination = &entries[next];
		node->m_bfmeNextFQ = destination->m_bfmeNodesFQ;
		destination->m_bfmeNodesFQ = node;
	}
	reinterpret_cast<Rva0035D2B0StringRecordTable *>(this)->release(index);
	return next;
}

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
};

void BfmeThingFQ::bfmeStepFQ(BfmeStateFQ *state, int arg)
{
	int current = state->m_bfmeIndexFQ;
	int index = m_bfmeTableFQ.bfmeAdvanceFQ(current, reinterpret_cast<AsciiString *>(arg));
	state->m_bfmeIndexFQ = index;
	state->m_bfmeValueFQ = m_bfmeTableFQ.m_bfmeEntriesFQ[index].m_bfmeShortFQ;
}

class BfmeTableFR
{
public:
	int bfmeAdvanceFR(int index, int arg);

	unsigned char m_bfmeDataFR[0x0c];
	BfmeEntryFQ *m_bfmeEntriesFR;
};

class BfmeThingFR
{
public:
	void bfmeStepFR(BfmeStateFQ *state, int arg);

	unsigned char m_bfmeHeadFR[0xc];
	BfmeTableFR m_bfmeTableFR;
};

void BfmeThingFR::bfmeStepFR(BfmeStateFQ *state, int arg)
{
	int current = state->m_bfmeIndexFQ;
	int index = m_bfmeTableFR.bfmeAdvanceFR(current, arg);
	state->m_bfmeIndexFQ = index;
	state->m_bfmeValueFQ = m_bfmeTableFR.m_bfmeEntriesFR[index].m_bfmeShortFQ;
}
