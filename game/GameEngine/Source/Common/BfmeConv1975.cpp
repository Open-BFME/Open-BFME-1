class BfmeThingESM;

struct BfmePairESM
{
	BfmePairESM(int a, int b)
	{
		m_bfmeAESM = a;
		m_bfmeBESM = b;
	}

	BfmePairESM(const BfmePairESM &other) throw()
	{
		m_bfmeAESM = other.m_bfmeAESM;
		m_bfmeBESM = other.m_bfmeBESM;
	}

	~BfmePairESM();

	int m_bfmeAESM;
	int m_bfmeBESM;
};

class BfmeHostESM
{
public:
	virtual void bfmeSlot00ESM();
	virtual void bfmeSlot01ESM();
	virtual void bfmeSlot02ESM();
	virtual void bfmeSlot03ESM();
	virtual void bfmeSlot04ESM();
	virtual void bfmeSlot05ESM();
	virtual void bfmeSlot06ESM();
	virtual void bfmeSlot07ESM();
	virtual void bfmeSlot08ESM();
	virtual void bfmeSlot09ESM();
	virtual void bfmeSlot10ESM();
	virtual void bfmeSlot11ESM();
	virtual void bfmeSlot12ESM();
	virtual void bfmeSlot13ESM();
	virtual void bfmeSlot14ESM();
	virtual void bfmeSlot15ESM();
	virtual void bfmeSlot16ESM();
	virtual void bfmeSlot17ESM();
	virtual void bfmeSlot18ESM();
	virtual void bfmeSlot19ESM();
	virtual void bfmeSlot20ESM();
	virtual void bfmeSlot21ESM();
	virtual void bfmeSlot22ESM();
	virtual void bfmeSlot23ESM();
	virtual void bfmeSlot24ESM();
	virtual void bfmeSlot25ESM();
	virtual void bfmeSlot26ESM();
	virtual void bfmeSlot27ESM();
	virtual BfmeThingESM *bfmeSlot28ESM();

	char bfmeRunESM(int a, int b, void **out);
	void bfmeMarkESM(BfmeThingESM *thing, int flag);
	void bfmePrepESM(BfmeThingESM *thing);
	char bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out, int one,
		int zero);
};

char BfmeHostESM::bfmeRunESM(int a, int b, void **out)
{
	*out = 0;

	BfmeThingESM *thing = bfmeSlot28ESM();

	if (thing == 0)
		return 0;

	bfmeMarkESM(thing, 0);
	bfmePrepESM(thing);

	char ok = bfmeDoESM(thing, BfmePairESM(a, b), out, 1, 0);

	bfmeMarkESM(thing, 1);

	return ok;
}
