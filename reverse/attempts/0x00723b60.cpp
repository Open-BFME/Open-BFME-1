// ?refreshCache@BfmeA1137@@QAEXXZ
// partial score=0.45 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversions.
// ghidra: FUN_00b23b60 retail @ 0x00723B60 size 184
// BfmeA1137 cache refresh: walk Glo012F15F8, decrement this+0x48 while
// this+0x44 is set, else Random_Float against override+0x54 and recompute
// this+0x48 via x87.

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class BfmeOverride1137 : public Overridable
{
public:
	char m_unmodelled_08[0x40 - 8];
	char m_flag40;
	char m_unmodelled_41[0x50 - 0x41];
	int m_50;
	float m_54;
};

extern BfmeOverride1137 *g_bfmeGlo012F15F8;
extern "C" float g_bfmeK1121004;
extern "C" float g_bfmeK075C6C;
extern "C" float g_bfmeK07533C;

class WWMath
{
public:
	static float Random_Float();
};

class BfmeA1137
{
public:
	void refreshCache();

private:
	char m_unmodelled_00[0x44];
	char m_flag44;
	char m_unmodelled_45[3];
	int m_48;
};

static const BfmeOverride1137 *walk(const BfmeOverride1137 *d)
{
	const BfmeOverride1137 *f = d;
	if (d && d->m_nextOverride)
		f = (const BfmeOverride1137 *)d->m_nextOverride->getFinalOverride();
	return f;
}

static const BfmeOverride1137 *walk3(const BfmeOverride1137 *d)
{
	const BfmeOverride1137 *f;
	if (d == 0)
		f = 0;
	else if (d->m_nextOverride)
		f = (const BfmeOverride1137 *)d->m_nextOverride->getFinalOverride();
	else
		f = d;
	return f;
}

void BfmeA1137::refreshCache()
{
	float slot;
	const BfmeOverride1137 *f = walk(g_bfmeGlo012F15F8);
	if (f->m_flag40 == 0)
		return;
	if (m_flag44)
	{
		int n = m_48 - 1;
		m_48 = n;
		if (n > 0)
			return;
		m_48 = 0;
		m_flag44 = 0;
		return;
	}
	slot = WWMath::Random_Float();
	f = walk(g_bfmeGlo012F15F8);
	if (slot > f->m_54)
		return;
	m_flag44 = 1;
	f = walk3(g_bfmeGlo012F15F8);
	m_48 = (int)((WWMath::Random_Float() * g_bfmeK1121004 + g_bfmeK075C6C) * f->m_50 + g_bfmeK07533C);
}
