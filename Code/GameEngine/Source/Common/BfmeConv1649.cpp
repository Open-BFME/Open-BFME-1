// Open-BFME5 conversions.

class BfmeStrVUO
{
public:
	~BfmeStrVUO() { bfmeClearVUO(); }
	char *m_bfme00;

private:
	void bfmeClearVUO();
};

class BfmeOwnVUO
{
public:
	~BfmeOwnVUO();
	virtual void bfmeSlot0VUO();
	BfmeStrVUO m_bfme04;
	BfmeStrVUO m_bfme08;
	BfmeStrVUO m_bfme0c;
	char m_bfmePad10[0xc];
	BfmeStrVUO m_bfme1c;
	BfmeStrVUO m_bfme20;
	BfmeStrVUO m_bfme24;
	BfmeStrVUO m_bfme28;
};

BfmeOwnVUO::~BfmeOwnVUO()
{
}
