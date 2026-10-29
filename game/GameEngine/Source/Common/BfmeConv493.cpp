class BfmeSinkBMF
{
public:
	void bfmeDoBMF(int what, int flag);
};

// Retail's load in bfmeGoBMF is 0x012F1028: the global BfmeConv2113.cpp defines.
class Glo012F1028Type;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

void __stdcall bfmeGoBMF(int what)
{
	BfmeSinkBMF *sink = reinterpret_cast<BfmeSinkBMF *>(Glo012F1028);
	if (sink != 0)
		sink->bfmeDoBMF(what - 1, 1);
}
