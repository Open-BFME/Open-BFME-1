// Open-BFME5 conversions.

extern char g_bfmeInfoTKB[];
extern void *g_bfmeVftTKB[];

// The retail call target at 0x0090E3D0 is the already-matched BfmeThingSJ
// member helper ?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z; spell the reference with
// its defining mangling (a plain member call through this, which leaves
// `this` already in ecx and therefore compiles to the same bytes).
class BfmeThingSJ
{
public:
	void bfmeBaseSJ(int what);
};

class BfmeThingTKB
{
public:
	BfmeThingTKB();
	void *m_bfmeVft;
};

BfmeThingTKB::BfmeThingTKB()
{
	reinterpret_cast<BfmeThingSJ *>(this)->bfmeBaseSJ(reinterpret_cast<int>(g_bfmeInfoTKB));
	m_bfmeVft = g_bfmeVftTKB;
}

void bfmeStepTKD(double d, int a);

void bfmeGoTKD(double d, int a)
{
	bfmeStepTKD(d, a);
}
