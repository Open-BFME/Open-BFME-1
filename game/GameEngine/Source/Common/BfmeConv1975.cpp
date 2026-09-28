// Retail 0x00609DA0 (107 B). Parameter types: identity_evidence/bfme_run_esm_00609da0.md.
// The caller 0x006176A0 builds the two-float position in place in the argument
// area ($T store) and reads the height back as a float. The (void **) cast only
// satisfies bfmeDoESM's pinned placeholder decoration.
class BfmeThingESM;

struct BfmeCoordESM
{
	BfmeCoordESM(float x, float y) { m_x = x; m_y = y; }
	BfmeCoordESM(const BfmeCoordESM &other) throw() { m_x = other.m_x; m_y = other.m_y; }
	float m_x;
	float m_y;
};

struct BfmePairESM
{
	BfmePairESM(float a, float b)
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

	float m_bfmeAESM;
	float m_bfmeBESM;
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

	char bfmeRunESM(BfmeCoordESM pos, float *height);
	void bfmeMarkESM(BfmeThingESM *thing, int flag);
	void bfmePrepESM(BfmeThingESM *thing);
	char bfmeDoESM(BfmeThingESM *thing, BfmePairESM pair, void **out, int one,
		int zero);
};

char BfmeHostESM::bfmeRunESM(BfmeCoordESM pos, float *height)
{
	*height = 0.0f;

	BfmeThingESM *thing = bfmeSlot28ESM();

	if (thing == 0)
		return 0;

	bfmeMarkESM(thing, 0);
	bfmePrepESM(thing);

	char ok = bfmeDoESM(thing, BfmePairESM(pos.m_x, pos.m_y), (void **)height, 1, 0);

	bfmeMarkESM(thing, 1);

	return ok;
}
