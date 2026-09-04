// Open-BFME5 conversions.

class BfmeThingTBAFields
{
public:
	char m_bfmePad[0x10];
	union { int m_bfme10; float m_bfme10f; };
	char m_bfmePad2[0x24];
	union { int m_bfme38; float m_bfme38f; };
	char m_bfmePad3c;
	char m_bfmeFlag3d;
	char m_bfmePad3e[6];
	char m_bfmeFlag;
	char m_bfmePad45[0x48 - 0x45];
	int m_bfme48;
	int m_bfme4c;
	float m_bfme50;
	float m_bfme54;
	union { int m_bfme58; float m_bfme58f; };
	union { int m_bfme5c; float m_bfme5cf; };
	float m_bfme60;
	float m_bfme64;
	char m_bfmePad68[0x94 - 0x68];
	int m_bfmeCount;
	int m_bfme98;
};

class BfmeThingTBA : public BfmeThingTBAFields
{
public:
	void bfmeGoTBA();
	void bfmeOneTBA();
	void bfmeTwoTBA();
	void bfmeThreeTBA();
	void bfmeFourTBA();
};

void BfmeThingTBA::bfmeGoTBA()
{
	bfmeOneTBA();
	bfmeTwoTBA();
	m_bfmeCount = 0;
	m_bfmeFlag = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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
	char m_bfmePad3b[0x40 - 0x3b];
	char m_bfmeFlag40;
	char m_bfmePad41[0x50 - 0x41];
	int m_bfme50Override;
	float m_bfme54Override;
	char m_bfmeFlag58;
	char m_bfmePad59[3];
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
extern "C" float g_bfmeK1121004;
extern "C" float g_bfmeK075C6C;
extern "C" float g_bfmeK07533C;

class WWMath
{
public:
	static float Random_Float();
};

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

void BfmeThingTBA::bfmeThreeTBA()
{
	const BfmeOverrideTBA *f = g_bfmeGlo012F15F8;
	const BfmeOverrideTBA *from;
	const BfmeOverrideTBA *to;
	BfmeOverrideTBA *d = (BfmeOverrideTBA *)bfmeWalkTBA(f);
	float fraction;

	if (d->m_bfmeFlag58 == 0 || m_bfme98 == 0)
		return;

	if (f == 0)
	{
		from = 0;
		to = 0;
	}
	else
	{
		const BfmeOverrideTBA *next =
			(const BfmeOverrideTBA *)f->m_nextOverride;
		if (next != 0)
		{
			from = (const BfmeOverrideTBA *)next->getFinalOverride();
			to = (const BfmeOverrideTBA *)next->getFinalOverride();
		}
		else
		{
			from = f;
			to = f;
		}
	}
	fraction = (float)(from->m_bfme5c - m_bfme4c) / (float)to->m_bfme5c;
	if (fraction > *(const float *)0x01075334)
	{
		bfmeTwoTBA();
		return;
	}

	if (fraction > m_bfme54)
	{
		m_bfme98 = 3;
		float blend = (fraction - m_bfme54) /
			(*(const float *)0x01075334 - m_bfme54);
		m_bfme38f = m_bfme5cf - (m_bfme5cf - m_bfme58f) * blend;
		m_bfme10f = m_bfme64 - (m_bfme64 - m_bfme60) * blend;
		return;
	}

	if (fraction > m_bfme50)
	{
		m_bfme98 = 2;
		m_bfme38f = m_bfme5cf;
		m_bfme10f = m_bfme64;
		return;
	}

	if (fraction <= *(const float *)0x01075350)
	{
		bfmeTwoTBA();
		return;
	}

	m_bfme98 = 1;
	float blend = m_bfme50 > *(const float *)0x0112100C ?
		fraction / m_bfme50 : *(const float *)0x01075334;
	m_bfme38f = m_bfme58f + (m_bfme5cf - m_bfme58f) * blend;
	m_bfme10f = m_bfme60 + (m_bfme64 - m_bfme60) * blend;
}

void BfmeThingTBA::bfmeFourTBA()
{
	const BfmeOverrideTBA *d = g_bfmeGlo012F15F8;
	float slot;
	if (d && d->m_nextOverride)
		d = (const BfmeOverrideTBA *)d->m_nextOverride->getFinalOverride();
	if (d->m_bfmeFlag40 == 0)
		return;
	if (m_bfmeFlag)
	{
		--m_bfme48;
		if (m_bfme48 > 0)
			return;
		m_bfme48 = 0;
		m_bfmeFlag = 0;
		return;
	}
	slot = WWMath::Random_Float();
	d = g_bfmeGlo012F15F8;
	if (d && d->m_nextOverride)
		d = (const BfmeOverrideTBA *)d->m_nextOverride->getFinalOverride();
	if (!(slot < d->m_bfme54Override))
		return;
	m_bfmeFlag = 1;
	d = g_bfmeGlo012F15F8;
	const BfmeOverrideTBA *f = bfmeWalkTBA(d);
	m_bfme48 = (int)((WWMath::Random_Float() * g_bfmeK1121004 +
		g_bfmeK075C6C) * f->m_bfme50Override + g_bfmeK07533C);
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
