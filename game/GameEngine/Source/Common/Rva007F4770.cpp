// Retail 0x007F4770: two-argument cdecl callback registered at 0x007F46F0.
// First argument is forwarded unchanged; the second is the live receiver.
class BfmeC994;
class BfmeXVJL;

class BfmeThingVJL
{
public:
	virtual void bfmeA00VJL();
	virtual class BfmeXVJL *bfmeA04VJL();
	virtual void bfmeA08VJL();
	virtual void bfmeA0CVJL();
	virtual void bfmeA10VJL();
	virtual void bfmeA14VJL();
	virtual void bfmeA18VJL(BfmeC994 *m);
	void bfmeGoVJL(int unused);
};


// Organizational address scope preserves the established callback basename.
// This is a static cdecl function, with no hidden receiver or EA class claim.
class Rva007F4770
{
public:
	static void __cdecl bfmeCbAZC(int unused, BfmeThingVJL *receiver);
};

void __cdecl Rva007F4770::bfmeCbAZC(int unused, BfmeThingVJL *receiver)
{
	receiver->bfmeGoVJL(unused);
}
