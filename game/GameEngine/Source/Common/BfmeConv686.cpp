class BfmeGlobalDFE
{
public:
	void bfmeRunDFE(int what, int flag);
};

// Retail's load at 0x002F1235 is 0x012F1028: the global BfmeConv2113.cpp defines.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

void __stdcall bfmeGoDFE(int what)
{
	if (Glo012F1028 != 0)
		reinterpret_cast<BfmeGlobalDFE *>(Glo012F1028)->bfmeRunDFE(what - 1, 0);
}
