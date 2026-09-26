// ?handleBfmeJ1017Event00892100@@YAXHHHH@Z
// partial score=0.85 date=2026-09-06
// ?handleBfmeJ1017Event00892100@@YAXHHHH@Z
// cl: /O2 /DNDEBUG /MD

extern int g_bfme1017H;
extern int g_bfme1017I;

class BfmeJ1017
{
public:
	void rva008A1BB0(int a, int b, unsigned char c, int type);
};

extern BfmeJ1017 *g_bfmeHolderBU;

void __cdecl handleBfmeJ1017Event00892100(int a, int b, int c, int type)
{
	if (!g_bfme1017H)
		return;
	if (g_bfme1017I)
		return;
	BfmeJ1017 *holder = g_bfmeHolderBU;
	if (!holder)
		return;
	holder->rva008A1BB0(a, b, (unsigned char)c, type);
}
