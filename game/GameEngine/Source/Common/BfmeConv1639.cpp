// Open-BFME5 conversions.

class BfmeStrVUH
{
public:
	~BfmeStrVUH() { bfmeClearVUH(); }
	char *m_bfme00;

private:
	void bfmeClearVUH();
};

class BfmeSinkVUH
{
public:
	virtual void bfmeSlot0VUH(int flags);
};

class BfmeBaseVUH
{
public:
	~BfmeBaseVUH()
	{
		BfmeSinkVUH *sink = m_bfme04;

		if (sink != 0)
			sink->bfmeSlot0VUH(1);

		m_bfme04 = 0;
	}

	virtual void bfmeSlot0VUH();
	BfmeSinkVUH *m_bfme04;
	char m_bfmePad08[4];
};

class BfmeOwnVUH : public BfmeBaseVUH
{
public:
	~BfmeOwnVUH();
	BfmeStrVUH m_bfme0c;
};

BfmeOwnVUH::~BfmeOwnVUH()
{
}
