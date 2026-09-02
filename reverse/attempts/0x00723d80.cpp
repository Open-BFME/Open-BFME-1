// ?resetOrCopy@BfmeA1137@@QAEXXZ
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversions.
// ghidra: FUN_00b23d80 retail @ 0x00723D80 size 160
// Sibling of BfmeA1137::copyFromOverride: clear this+0x4c/0x98, copy
// Glo012F0FE0+0xc into this+0x94, then either copy this+0x58/0x5c down
// or pull override+0x30/0x34 from walked Glo012F15F8.

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
	char m_unmodelled_08[0x30 - 8];
	int m_30;
	int m_34;
	char m_unmodelled_38[0x3a - 0x38];
	char m_flag3a;
	char m_unmodelled_3b[0x5c - 0x3b];
	int m_5c;
};

class BfmeGlo012F0FE0
{
public:
	char m_unmodelled_00[0x0c];
	int m_0c;
};

extern BfmeOverride1137 *g_bfmeGlo012F15F8;
extern BfmeGlo012F0FE0 *g_bfmeGlo012F0FE0;

class BfmeA1137
{
public:
	void resetOrCopy();

private:
	char m_unmodelled_00[0x10];
	int m_10;
	char m_unmodelled_14[0x38 - 0x14];
	int m_38;
	char m_unmodelled_3c;
	char m_flag3d;
	char m_unmodelled_3e[0x4c - 0x3e];
	int m_4c;
	char m_unmodelled_50[0x58 - 0x50];
	int m_58;
	int m_5c;
	char m_unmodelled_60[0x94 - 0x60];
	int m_94;
	int m_98;
};

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

void BfmeA1137::resetOrCopy()
{
	const BfmeOverride1137 *d;
	const BfmeOverride1137 *f;
	int a;
	int b;

	m_4c = 0;
	m_98 = 0;
	m_94 = g_bfmeGlo012F0FE0->m_0c;

	d = g_bfmeGlo012F15F8;
	f = walk3(d);
	if (f->m_flag3a == 0)
	{
		a = m_58;
		b = m_5c;
		m_flag3d = 0;
		m_38 = a;
		m_10 = b;
		return;
	}

	f = walk3(d);
	m_38 = f->m_30;

	d = g_bfmeGlo012F15F8;
	f = d;
	if (!g_bfmeGlo012F15F8)
	{
		m_10 = f->m_34;
		return;
	}
	if (d->m_nextOverride)
		d = (const BfmeOverride1137 *)d->m_nextOverride->getFinalOverride();
	m_10 = d->m_34;
}
