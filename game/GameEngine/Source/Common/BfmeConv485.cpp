class BfmeSinkBLD
{
public:
	void bfmeDoBLD(void *what, int flag);
};

// Retail 0x012F4B98: use the existing data owner; retain the local pointee view.
extern class AptPalantir *TheAptPalantir;

void __stdcall bfmeGoBLD(void *what)
{
	BfmeSinkBLD *sink = reinterpret_cast<BfmeSinkBLD *>(TheAptPalantir);
	if (sink != 0)
		sink->bfmeDoBLD(what, 0);
}
