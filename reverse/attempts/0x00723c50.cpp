// ?cachedRandom@Rva00723C50@@QAEMXZ
// partial score=0.4 date=2026-09-02
// cl: /EHs-c-
//
// Two independent override walks of the singleton at 0x012F15F8.  The first
// reads the +0x40 flag (and this+0x44); both clear => return 1.0f from a
// stack slot.  Both set => walk again and tail into
// GameClientRandomVariable::getValue (0x00096F60 / ILT 0x000D7B5) on the
// random variable at override+0x44.

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class GameClientRandomVariable
{
public:
	float getValue() const;
};

class Rva00723C50Data : public Overridable
{
public:
	char m_unmodelled_08[0x40 - 8];
	char m_flag40;
	char m_unmodelled_41[3];
	GameClientRandomVariable m_random;
};

extern Rva00723C50Data *g_rva00723CF0Data;

class Rva00723C50
{
public:
	float cachedRandom();

private:
	char m_unmodelled_00[0x44];
	char m_flag44;
};

float Rva00723C50::cachedRandom()
{
	float one = 1.0f;
	Rva00723C50Data *d = g_rva00723CF0Data;
	Rva00723C50Data *f;
	if (d == 0)
		f = d;
	else
		f = (Rva00723C50Data *)(d->m_nextOverride
			? d->m_nextOverride->getFinalOverride()
			: d);
	if (f->m_flag40 == 0 || m_flag44 == 0)
		return one;
	if (d == 0)
		f = d;
	else
		f = (Rva00723C50Data *)(d->m_nextOverride
			? d->m_nextOverride->getFinalOverride()
			: d);
	return f->m_random.getValue();
}
