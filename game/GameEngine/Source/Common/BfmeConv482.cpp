extern void *g_bfmeWhatBGE;

// Retail calls 0x007E88D0, matched as BfmeThingCIB::bfmeGoCIB
// (BfmeConv606.cpp); the receiver is the same object.
class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
};

class BfmeSubBKG
{
};

void __stdcall bfmeGoBKG(BfmeSubBKG *sub, void *what)
{
	reinterpret_cast<BfmeThingCIB *>(sub)->bfmeGoCIB(g_bfmeWhatBGE, what);
}
