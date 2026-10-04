// Open-BFME5 conversions.

extern char g_bfmeInfoTKB[];
extern void *g_bfmeVftTKB[];

// The retail call at +0x09 targets 0x0090E3D0.  The ledger row for that
// address (game/GameEngine/Source/Common/BfmeThreeHundredThirtyEight.cpp) carries
// object-symbol=??0BfmeThingSJ@@QAE@H@Z: that object DEFINES the constructor,
// not the member name the row spells, so no object defines
// ?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z and every reference to it is unresolved.
// Base-initialise instead, which reaches the defining symbol through a base
// constructor call: `this` is already in ecx, so the bytes are unchanged.
// Only the ctor and the leading vftable slot this body touches are declared.
class BfmeThingSJ
{
public:
	BfmeThingSJ(int what);

	void *m_bfmeVft;
};

class BfmeThingTKB : public BfmeThingSJ
{
public:
	BfmeThingTKB();
};

BfmeThingTKB::BfmeThingTKB()
	: BfmeThingSJ(reinterpret_cast<int>(g_bfmeInfoTKB))
{
	m_bfmeVft = g_bfmeVftTKB;
}

void bfmeStepTKD(double d, int a);

void bfmeGoTKD(double d, int a)
{
	bfmeStepTKD(d, a);
}
