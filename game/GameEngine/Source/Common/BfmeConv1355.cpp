// Open-BFME5 conversions.

extern "C" long __ftol2(double v);

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *p);

class BfmeRefVGO
{
public:
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &o);
	unsigned *m_bfmeP;
};

BfmeRefVGO &BfmeRefVGO::bfmeAssignVGO(const BfmeRefVGO &o)
{
	if (&o != this)
	{
		if (m_bfmeP && Rva00894D90Accessor::decrement(m_bfmeP) == 0)
			bfmeDropA(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			Rva00894D80Accessor::increment(m_bfmeP);
	}
	return *this;
}
