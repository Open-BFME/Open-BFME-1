// Open-BFME5 conversions.

extern "C" long __ftol2(double v);

void __cdecl bfmeGoVGM(float x, float y, int *ox, int *oy, int w, int h)
{
	*ox = (int)((x + 1.0f) * w * 0.5f);
	*oy = (int)((1.0f - y) * h * 0.5f);
}

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

unsigned __cdecl bfmeIncVGO(unsigned *p);
void __cdecl bfmeDropVGO(void *p);

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
			bfmeDropVGO(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			bfmeIncVGO(m_bfmeP);
	}
	return *this;
}
