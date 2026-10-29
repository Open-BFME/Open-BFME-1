class BfmeSinkBQE
{
public:
	void bfmeDoBQE(void *what);
};

// 0x012F1028 is the one Glo012F1028 global.  BfmeSinkBQE above is this TU's
// view of that object (its member is the pinned bfmeDoBQE callee), so the use
// casts rather than declaring a second name for the address.
class Glo012F1028Type;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

void __stdcall bfmeGoBQE(void *what)
{
	if (what == 0)
		((BfmeSinkBQE *)Glo012F1028)->bfmeDoBQE(0);
}
