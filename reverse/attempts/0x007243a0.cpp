// ?d_007243a0@@YAXXZ
// partial score=0.9 date=2026-09-03
// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x007243A0.  This is the weather-transition interpolation step in
// the same BFME object family as the 0x00723D80 override-copy body.  The
// second override walk is intentional: retail keeps both final pointers
// live while it computes the transition fraction.

class BfmeOverrideTBA;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const BfmeOverrideTBA *m_nextOverride;
};

class BfmeOverrideTBA : public Overridable
{
public:
	char m_pad08[0x58 - 8];
	char m_flag58;
	char m_pad59[3];
	int m_5c;
};

extern BfmeOverrideTBA *g_bfmeGlo012F15F8;

static const BfmeOverrideTBA *walkTBA(const BfmeOverrideTBA *d)
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

class BfmeThingTBA
{
public:
	void transitionTBA(void);
	void bfmeTwoTBA(void);

	char m_pad00[0x10];
	float m_10;
	char m_pad14[0x38 - 0x14];
	float m_38;
	char m_pad3c[0x4c - 0x3c];
	int m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	char m_pad68[0x2c];
	int m_94;
	int m_98;
};

void BfmeThingTBA::transitionTBA(void)
{
	BfmeOverrideTBA *f = g_bfmeGlo012F15F8;
	BfmeOverrideTBA *d = (BfmeOverrideTBA *)walkTBA(f);
	float fraction;
	BfmeOverrideTBA *from;
	BfmeOverrideTBA *to;
	BfmeOverrideTBA *next;
	if (d->m_flag58 == 0 || m_98 == 0)
		return;

	if (f == 0)
	{
		from = 0;
		to = 0;
	}
	else
	{
		next = (BfmeOverrideTBA *)f->m_nextOverride;
		if (next == 0)
		{
			from = f;
			to = f;
		}
		else
		{
			from = (BfmeOverrideTBA *)next->getFinalOverride();
			to = (BfmeOverrideTBA *)next->getFinalOverride();
		}
	}
	fraction = (float)(from->m_5c - m_4c) / (float)to->m_5c;
	if (fraction > 1.0f)
	{
		bfmeTwoTBA();
		return;
	}

	if (fraction > m_54)
	{
		m_98 = 3;
		float blend = (fraction - m_54) / (1.0f - m_54);
		m_38 = m_5c - (m_5c - m_58) * blend;
		m_10 = m_64 - (m_64 - m_60) * blend;
		return;
	}

	if (fraction > m_50)
	{
		m_98 = 2;
		m_38 = m_5c;
		m_10 = m_64;
		return;
	}

	if (fraction <= 0.0f)
	{
		bfmeTwoTBA();
		return;
	}

	m_98 = 1;
	float blend = m_50 > 0.00001f ? fraction / m_50 : 1.0f;
	m_38 = m_58 + (m_5c - m_58) * blend;
	m_10 = m_60 + (m_64 - m_60) * blend;
}
