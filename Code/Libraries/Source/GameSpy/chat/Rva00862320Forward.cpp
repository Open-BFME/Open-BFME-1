// ?rva00862320Forward@@YAXHHHHHHHHHH@Z
// Address-derived: sibling of 0x008622C0, same 10-int-to-21-arg forwarding
// shape into the already-named callee 0x00861ED0 with a different zero/param
// arrangement.
extern void d_00861ed0();

typedef void (*Rva00862320Fn)(int, int, int, int, int, int, int, int, int, int,
	int, int, int, int, int, int, int, int, int, int, int);

void rva00862320Forward(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10)
{
	Rva00862320Fn fn = (Rva00862320Fn)d_00861ed0;
	fn(0, p1, p2, p3, 0, p4, 0, 0, 0, 0, 0, 0, 0, 0, 0, p5, p6, p7, p8, p9, p10);
}
