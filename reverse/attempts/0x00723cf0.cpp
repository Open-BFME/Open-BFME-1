// ?copyFromOverride@Rva00723CF0@@QAEXXZ
// partial score=0.85 date=2026-09-02
// cl: /EHs-c-
//
// Copy three dwords out of the walked override of the singleton at
// 0x012F15F8 after stamping this+0x98 and this+0x3d.  Each copy reloads the
// global and runs the same first-level override expansion Q2OverrideChainFieldReads
// recovered: n ? n->getFinalOverride() : d, with the null-global arm still
// reading through a zero register.  getFinalOverride is the already-matched
// body at 0x00087A80 (ILT 0x000022BB).

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class Rva00723CF0Data : public Overridable
{
public:
	char m_unmodelled_08[0x5c - 8];
	int m_5c;
	int m_60;
	int m_64;
};

extern Rva00723CF0Data *g_rva00723CF0Data;

class Rva00723CF0
{
public:
	void copyFromOverride();

private:
	char m_unmodelled_00[0x3d];
	char m_flag3d;
	char m_unmodelled_3e[0x4c - 0x3e];
	int m_4c;
	int m_50;
	int m_54;
	char m_unmodelled_58[0x98 - 0x58];
	int m_98;
};

static const Rva00723CF0Data *walk(const Rva00723CF0Data *d)
{
	const Rva00723CF0Data *f = d;
	if (d && d->m_nextOverride)
		f = (const Rva00723CF0Data *)d->m_nextOverride->getFinalOverride();
	return f;
}

void Rva00723CF0::copyFromOverride()
{
	const Rva00723CF0Data *f;

	m_98 = 1;
	m_flag3d = 1;
	f = walk(g_rva00723CF0Data);
	m_4c = f->m_5c;
	f = walk(g_rva00723CF0Data);
	m_50 = f->m_60;
	f = walk(g_rva00723CF0Data);
	m_54 = f->m_64;
}
