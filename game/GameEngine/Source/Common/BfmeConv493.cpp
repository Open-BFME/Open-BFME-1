class BfmeSinkBMF
{
public:
	void bfmeDoBMF(int what, int flag);
};

// Retail's load in bfmeGoBMF is 0x012F1028: the global BfmeConv2113.cpp defines.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

void __stdcall bfmeGoBMF(int what)
{
	BfmeSinkBMF *sink = reinterpret_cast<BfmeSinkBMF *>(Glo012F1028);
	if (sink != 0)
		sink->bfmeDoBMF(what - 1, 1);
}
