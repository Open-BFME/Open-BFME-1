// ?rva008622C0Forward@@YAXHHHHHHHHHH@Z
// Address-derived: cdecl forwarder that packs its 10 int parameters plus a
// fixed run of zero defaults into a 21-argument call to the already-named
// callee 0x00861ED0.
extern void d_00861ed0();

typedef void (*Rva008622C0Fn)(int, int, int, int, int, int, int, int, int, int,
	int, int, int, int, int, int, int, int, int, int, int);

void rva008622C0Forward(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10)
{
	Rva008622C0Fn fn = (Rva008622C0Fn)d_00861ed0;
	fn(0, p1, p2, p3, p4, p5, 0, 0, 0, 0, 0, 0, 0, 0, 0, p6, p7, 0, p8, p9, p10);
}
