// cl: /DNDEBUG /MD /EHsc
//
// Fuzzy twin (r0.895) of BfmeConv977.cpp's bfmeUpdateMaxPowerCommand
// (retail 0x0058C050, "NonCommand_MaxEvenstarPower"/"NonCommand_MaxRingPower"):
// the same ternary-string / find-then-do shape, but this body is a THISCALL
// member (not a stdcall free function taking an unused arg), it guards the
// whole thing on a this-relative pointer's first int being non-negative, and
// its string choice depends on a global object's two flag bytes at +0x2C/
// +0x2D (`g && g->flagA && g->flagB`) rather than a single bool. The two
// literal names -- "NonCommand_CommandPoints" and
// "NonCommand_CommandPointsLivingWorld" -- are read straight off
// reverse/string_xrefs.tsv for this RVA. `TheControlBar` (0x012F33F8) is the
// real global per symbols.csv; `Glo012F1028` (0x012F1028) is address-derived,
// its type and the this-relative guard pointer are not recovered.

class BfmeB977;

class BfmeMgr977
{
public:
	void *bfmeFind977B(BfmeB977 *b);
	void bfmeDo977B(int a, void *x);
};

extern BfmeMgr977 *TheControlBar;			// 0x012F33F8

class Glo012F1028Type
{
public:
	char m_pad[0x2c];
	char m_flagA;			// +0x2c
	char m_flagB;			// +0x2d
};

extern Glo012F1028Type *Glo012F1028;			// 0x012F1028

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

class Gen0058BD70
{
public:
	void handle(int unused);

private:
	int *m_0;			// this+0x0
};

// ?handle@Gen0058BD70@@QAEXH@Z
void Gen0058BD70::handle(int unused)
{
	if (*m_0 < 0)
		return;

	Glo012F1028Type *g = Glo012F1028;
	const char *name = (g && g->m_flagA && g->m_flagB)
		? "NonCommand_CommandPointsLivingWorld" : "NonCommand_CommandPoints";

	void *command;
	{
		BFMERetailAsciiString label(name);
		command = TheControlBar->bfmeFind977B((BfmeB977 *)&label);
	}

	if (command)
		TheControlBar->bfmeDo977B(0, command);
}
