// Open-BFME5 conversions.

class BfmeStrVUJ
{
public:
	~BfmeStrVUJ() { bfmeClearVUJ(); }
	char *m_bfme00;

private:
	void bfmeClearVUJ();
};

class BfmeSinkVUJ
{
public:
	virtual void bfmeSlot0VUJ(int flags);
};

class BfmeBaseVUJ
{
public:
	~BfmeBaseVUJ()
	{
		BfmeSinkVUJ *sink = m_bfme04;

		if (sink != 0)
			sink->bfmeSlot0VUJ(1);

		m_bfme04 = 0;
	}

	virtual void bfmeSlot0VUJ();
	BfmeSinkVUJ *m_bfme04;
	char m_bfmePad08[4];
};

class BfmeOwnVUJ : public BfmeBaseVUJ
{
public:
	~BfmeOwnVUJ();
	BfmeStrVUJ m_bfme0c;
};

BfmeOwnVUJ::~BfmeOwnVUJ()
{
}
