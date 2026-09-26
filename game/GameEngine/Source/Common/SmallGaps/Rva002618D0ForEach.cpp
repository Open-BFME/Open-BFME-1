// ?rva002618D0ForEach@@YAXPAURva002618D0Elem@@0PAX@Z
// Address-derived: for each 8-byte element in [begin,end), call the
// already-named thunk 0x000028D3 with (begin, current, current->a,
// current->b, ctx).
struct Rva002618D0Elem
{
	int a;
	int b;
};

extern void j_000028d3();

void rva002618D0ForEach(Rva002618D0Elem* begin, Rva002618D0Elem* end, void* ctx)
{
	typedef void(__cdecl* Fn)(Rva002618D0Elem*, Rva002618D0Elem*, int, int, void*);
	Fn fn = (Fn)j_000028d3;

	if (begin == end)
		return;

	Rva002618D0Elem* p = begin + 1;
	if (p == end)
		return;

	for (; p != end; ++p)
		fn(begin, p, p->a, p->b, ctx);
}
