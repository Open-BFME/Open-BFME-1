// Open-BFME5 conversions.

class BfmeStrVUQ
{
public:
	~BfmeStrVUQ() { bfmeClearVUQ(); }
	char *m_bfme00;

private:
	void bfmeClearVUQ();
};

class BfmeSinkVUQ
{
public:
	virtual void bfmeSlot0VUQ(int flags);
};

class BfmeBaseVUQ
{
public:
	~BfmeBaseVUQ() { }
	virtual void bfmeSlot0VUQ();
};

class BfmeOwnVUQ : public BfmeBaseVUQ
{
public:
	~BfmeOwnVUQ();
	BfmeStrVUQ m_bfme04;
	BfmeStrVUQ m_bfme08;
	BfmeStrVUQ m_bfme0c;
	char m_bfmePad10[0xc];
	BfmeSinkVUQ *m_bfme1c;
	BfmeSinkVUQ *m_bfme20;
	BfmeSinkVUQ *m_bfme24;
	char m_bfmePad28[8];
	BfmeStrVUQ m_bfme30;
};

BfmeOwnVUQ::~BfmeOwnVUQ()
{
	BfmeSinkVUQ *first = m_bfme1c;
	BfmeSinkVUQ *second;
	BfmeSinkVUQ *third;

	if (first != 0)
		first->bfmeSlot0VUQ(1);

	second = m_bfme20;

	if (second != 0)
		second->bfmeSlot0VUQ(1);

	third = m_bfme24;

	if (third != 0)
		third->bfmeSlot0VUQ(1);
}
