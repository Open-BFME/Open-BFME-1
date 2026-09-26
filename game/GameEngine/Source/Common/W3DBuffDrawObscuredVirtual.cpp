// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x007502B0, slot 32 of the dedicated W3DBuffDraw table VA 0x01121CD8.
// The table is the only one holding this body, so the owning class is proven;
// the lexical method name stays RVA-derived.

typedef bool Bool;

class W3DBuffDraw
{
public:
	virtual void rva007502B0(Bool);
};

// ?rva007502B0@W3DBuffDraw@@UAEX_N@Z
void W3DBuffDraw::rva007502B0(Bool)
{
}
