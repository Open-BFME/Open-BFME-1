class BfmeGlobalDFE
{
public:
	void bfmeRunDFE(int what, int flag);
};

// Retail's load at 0x002F1235 is 0x012F1028: the global BfmeConv2113.cpp defines.
class Glo012F1028Type;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

void __stdcall bfmeGoDFE(int what)
{
	if (Glo012F1028 != 0)
		reinterpret_cast<BfmeGlobalDFE *>(Glo012F1028)->bfmeRunDFE(what - 1, 0);
}
