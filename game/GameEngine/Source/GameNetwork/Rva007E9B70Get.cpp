// cl: /O2
// Retail 0x007E9B70 is a six-byte singleton getter: `mov eax,0x0130A580; ret`.
// It never reads a receiver or arguments.  The object at VA 0x0130A580 is a
// FESL polymorphic service (its vtable pointer is installed at run time, so
// retail .data holds zeros); its vslot 2 is the clock sample many FESL bodies
// read, vslots 2/3/4 the begin/stamp/end triple used by the 0x007EA5E0
// dispatch pass.  Name stays address-derived: the original class is not
// recoverable from the callers.

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual int v2();
};

char g_Va0130A580[4];

Rva007E9B70Obj *Rva007E9B70Get()
{
	return (Rva007E9B70Obj *)g_Va0130A580;
}
