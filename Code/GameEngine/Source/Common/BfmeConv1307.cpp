// Open-BFME5 conversions.

class BfmeThingTBAFields
{
public:
	char m_bfmePad[0x10];
	int m_bfme10;
	char m_bfmePad2[0x24];
	int m_bfme38;
	char m_bfmePad3c;
	char m_bfmeFlag3d;
	char m_bfmePad3e[6];
	char m_bfmeFlag;
	char m_bfmePad45[7];
	int m_bfme4c;
	char m_bfmePad50[8];
	int m_bfme58;
	int m_bfme5c;
	char m_bfmePad60[0x34];
	int m_bfmeCount;
	int m_bfme98;
};

class BfmeThingTBA : public BfmeThingTBAFields
{
public:
	void bfmeGoTBA();
	void bfmeOneTBA();
	void bfmeTwoTBA();
};

void BfmeThingTBA::bfmeGoTBA()
{
	bfmeOneTBA();
	bfmeTwoTBA();
	m_bfmeCount = 0;
	m_bfmeFlag = 0;
}

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class BfmeOverrideTBA : public Overridable
{
public:
	char m_bfmePad08[0x30 - 8];
	int m_bfme30;
	int m_bfme34;
	char m_bfmePad38[2];
	char m_bfmeFlag3a;
	char m_bfmePad3b[0x5c - 0x3b];
	int m_bfme5c;
};

class BfmeFrameTBA
{
public:
	char m_bfmePad[0x0c];
	int m_bfmeFrame;
};

extern BfmeOverrideTBA *g_bfmeGlo012F15F8;
extern BfmeFrameTBA *g_bfmeGlo012F0FE0;

static const BfmeOverrideTBA *bfmeWalkTBA(const BfmeOverrideTBA *d)
{
	const BfmeOverrideTBA *f;
	if (d == 0)
		f = 0;
	else if (d->m_nextOverride)
		f = (const BfmeOverrideTBA *)d->m_nextOverride->getFinalOverride();
	else
		f = d;
	return f;
}

void BfmeThingTBA::bfmeTwoTBA()
{
	const BfmeOverrideTBA *f;
	const BfmeOverrideTBA *d;
	int a;
	int b;

	m_bfme4c = 0;
	m_bfme98 = 0;
	const BfmeFrameTBA *q = g_bfmeGlo012F0FE0;
	m_bfmeCount = q->m_bfmeFrame;
	f = g_bfmeGlo012F15F8;

	d = bfmeWalkTBA(f);
	if (d->m_bfmeFlag3a == 0)
	{
		m_bfmeFlag3d = 0;
		a = m_bfme58;
		b = m_bfme5c;
		m_bfme38 = a;
		m_bfme10 = b;
		return;
	}

	if (f == 0)
		d = 0;
	else if (f->m_nextOverride)
		d = (const BfmeOverrideTBA *)f->m_nextOverride->getFinalOverride();
	else
		d = f;
	m_bfme38 = d->m_bfme30;

	d = bfmeWalkTBA(g_bfmeGlo012F15F8);
	b = d->m_bfme34;
	m_bfme10 = b;
}

class BfmeSinkTBB
{
public:
	virtual void bfmeV0TBB() = 0;
	virtual void bfmeV1TBB() = 0;
	virtual void bfmeV2TBB() = 0;
	virtual void bfmeV3TBB() = 0;
	virtual void bfmeV4TBB() = 0;
	virtual void bfmeV5TBB() = 0;
	virtual void bfmeV6TBB() = 0;
	virtual void bfmeV7TBB() = 0;
	virtual void bfmeDoTBB(int a) = 0;
};

class BfmeThingTBB
{
public:
	void bfmeGoTBB(int a);
	void bfmeUseTBB(int a);
	char m_bfmePad[0x2c];
	BfmeSinkTBB *m_bfmeSink;
};

void BfmeThingTBB::bfmeGoTBB(int a)
{
	m_bfmeSink->bfmeDoTBB(0);
	bfmeUseTBB(a);
}
