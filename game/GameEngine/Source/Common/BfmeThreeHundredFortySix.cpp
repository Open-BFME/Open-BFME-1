extern "C" unsigned char bfmeVftTG[];

// Declared only: retail defines this constructor at 0x00899F00
// (functions.csv ??0Rva00899F00Base@@QAE@IH@Z, defined in
// Rva008B2EF0Constructors.cpp). No header declares the type, so this
// TU-local declaration carries no layout and emits no body.
class Rva00899F00Base
{
public:
	Rva00899F00Base(unsigned int one, int two);
};

class BfmeThingTG
{
public:
	BfmeThingTG *bfmeInitTG();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x1c];
	int m_bfmeOne;
};

BfmeThingTG *BfmeThingTG::bfmeInitTG()
{
	// Retail constructs the 0x00899F00 base in place on `this`. The explicit
// qualified constructor call is the only spelling that emits the bare
// thiscall to ??0Rva00899F00Base@@QAE@IH@Z; placement new adds an SEH frame.
((Rva00899F00Base *)this)->Rva00899F00Base::Rva00899F00Base(0x23, 8);
	m_bfmeVft = bfmeVftTG;
	m_bfmeOne = 0;
	return this;
}
