// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

extern void j_00026f49(void);
extern void j_00009bc9(void);
extern void j_0002805b(void);
extern void j_0000365c(void);

typedef const char *(__cdecl *Rva00463BA0LeafFn)(const char *);
typedef void *(__cdecl *Rva00463BA0LookupFn)(const char *);
typedef void *(__cdecl *Rva00463BA0FallbackFn)(const char *, void *);
typedef void (__cdecl *Rva00463BA0UpdateFn)(void *, void *);

class Rva00463BA0Node
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void setBounds(int x0, int y0, int x1, int y1);
};

// Retail 0x00463BA0 (110B): look up a named node by path leaf (strip a
// "~" or "/" marker with bfmePathLeafAfterMarker, then hash-lookup by
// name), create it through the fallback helper at 0x00462E80 when the
// lookup misses, refresh it through 0x004605F0, then push two Coord2D
// corners through __ftol2 and set the node's integer bounds through a
// thiscall virtual slot. No named caller, class or method identity
// survived the identity sweep (blocked once: boundary=0x00463ba0..
// 0x00463c0e, t=20m model=Codex); every name here is address-derived.
void Rva00463BA0(const Coord2D *a, const Coord2D *b, const char *c, void *d)
{
	const char *leaf = ((Rva00463BA0LeafFn)j_00026f49)(c);
	void *node = ((Rva00463BA0LookupFn)j_00009bc9)(leaf);
	if (!node)
	{
		node = ((Rva00463BA0FallbackFn)j_0002805b)(c, d);
		if (!node)
			return;
	}

	((Rva00463BA0UpdateFn)j_0000365c)(node, d);

	((Rva00463BA0Node *)node)->setBounds(
		(int)a->x, (int)a->y, (int)b->x, (int)b->y);
}
