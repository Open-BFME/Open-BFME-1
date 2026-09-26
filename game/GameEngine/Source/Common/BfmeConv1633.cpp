// Open-BFME5 conversions.

class BfmeStrVUE
{
public:
	BfmeStrVUE() { m_bfme00 = 0; }
	~BfmeStrVUE() { bfmeClearVUE(); }
	void bfmeClearVUE();
	char *m_bfme00;
};

class BfmeOwnVUE
{
public:
	BfmeOwnVUE();
	virtual void bfmeSlot0VUE();
	BfmeStrVUE m_bfme04;
	BfmeStrVUE m_bfme08;
	BfmeStrVUE m_bfme0c;
	char m_bfme10;
};

BfmeOwnVUE::BfmeOwnVUE()
	: m_bfme10(0)
{
	m_bfme04.bfmeClearVUE();
	m_bfme0c.bfmeClearVUE();
	m_bfme08.bfmeClearVUE();
}
