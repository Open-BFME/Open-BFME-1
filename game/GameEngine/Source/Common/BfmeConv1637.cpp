// Open-BFME5 conversions.

class BfmeStrVUG
{
public:
	~BfmeStrVUG() { bfmeClearVUG(); }
	char *m_bfme00;

private:
	void bfmeClearVUG();
};

class BfmeSubVUG
{
public:
	virtual void bfmeSlot0VUG(int flags);
	int m_bfme04;
};

class BfmeRefVUG
{
public:
	char m_bfmePad00[0x24];
	BfmeSubVUG m_bfme24;
};

class BfmeOwnVUG
{
public:
	~BfmeOwnVUG();
	char m_bfmePad00[0xc];
	BfmeStrVUG m_bfme0c;
	BfmeRefVUG *m_bfme10;
};

BfmeOwnVUG::~BfmeOwnVUG()
{
	BfmeRefVUG *ref = m_bfme10;

	if (ref != 0)
	{
		BfmeSubVUG *sub = &ref->m_bfme24;
		int count = --sub->m_bfme04;

		if (count <= 0)
			sub->bfmeSlot0VUG(1);
	}
}
