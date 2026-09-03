// ?extraAfterFmod@W3DSnowManager@@QAEXXZ
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversions.
// ghidra: FUN_00b25620 retail @ 0x00725620 size 189
// BfmeA1137 frame/state update: walk Glo012F15F8, maybe decrement this+0x4c,
// then either refresh from (K - this+0x54)*override+0x5c or tail-call
// copyFromOverride.

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
	char m_unmodelled_08[0x58 - 8];
	char m_flag58;
	char m_unmodelled_59[3];
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
extern "C" float g_bfmeDefaultBU;

class BfmeA1137
{
public:
	void update();
	void copyFromOverride();
	void sibling();

private:
	char m_unmodelled_00[0x4c];
	int m_4c;
	char m_unmodelled_50[0x54 - 0x50];
	float m_54;
	char m_unmodelled_58[0x94 - 0x58];
	int m_94;
	int m_98;
};

static const BfmeOverride1137 *walk(const BfmeOverride1137 *d)
{
	const BfmeOverride1137 *f = d;
	if (d && d->m_nextOverride)
		f = (const BfmeOverride1137 *)d->m_nextOverride->getFinalOverride();
	return f;
}

void BfmeA1137::update()
{
	const BfmeOverride1137 *ov = walk(g_bfmeGlo012F15F8);
	if (ov->m_flag58 == 0)
		return;

	if (m_98 != 0)
	{
		int state = m_98;
		if (state == 1 || state == 3)
			--m_4c;
		sibling();
		int state94 = m_94;
		if (state94 == 2)
		{
			int frame = g_bfmeGlo012F0FE0->m_0c;
			if (frame != state94)
			{
				m_98 = 3;
				ov = walk(g_bfmeGlo012F15F8);
				m_4c = (int)((g_bfmeDefaultBU - m_54) * ov->m_5c);
				m_94 = 2;
			}
		}
	}
	else
	{
		int frame = g_bfmeGlo012F0FE0->m_0c;
		if (frame == 2 && m_94 != 2)
		{
				m_94 = frame;
			copyFromOverride();
		}
	}
}
