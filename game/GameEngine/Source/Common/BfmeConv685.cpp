class BfmeGlobalDFD
{
public:
	void bfmeRunDFD(int what, int flag);
};

// Retail's load at 0x002F1215 is 0x012F1028: the global BfmeConv2113.cpp defines.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

void __stdcall bfmeGoDFD(int what)
{
	if (Glo012F1028 != 0)
		reinterpret_cast<BfmeGlobalDFD *>(Glo012F1028)->bfmeRunDFD(what - 1, 1);
}
