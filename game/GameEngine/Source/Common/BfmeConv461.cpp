void *g_bfmeWhatBGE = "ID";

class BfmeSubBGE
{
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *what, void *flag);
};

void __stdcall bfmeGoBGE(BfmeSubBGE *sub)
{
	reinterpret_cast<BfmeThingRF *>(sub)->bfmeGoRF(g_bfmeWhatBGE, 0);
}
