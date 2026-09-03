// Open-BFME5 conversions.

class BfmeStrVUF
{
public:
	~BfmeStrVUF() { bfmeClearVUF(); }
	char *m_bfme00;

private:
	void bfmeClearVUF();
};

class BfmeSinkVUF
{
public:
	virtual void bfmeSlot0VUF(int flags);
};

class BfmeOwnVUF
{
public:
	~BfmeOwnVUF();
	BfmeStrVUF m_bfme00;
	char m_bfmePad04[8];
	int m_bfme0c;
	BfmeSinkVUF *m_bfme10;
};

BfmeOwnVUF::~BfmeOwnVUF()
{
	BfmeSinkVUF *sink = m_bfme10;

	m_bfme0c = 0;

	if (sink != 0)
		sink->bfmeSlot0VUF(1);

	m_bfme10 = 0;
}
