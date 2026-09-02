// ?d_003ea960@@YAXXZ
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeThingBIE;
struct BfmeSubBIE;

void __stdcall bfmeDoBIE(BfmeThingBIE *a, BfmeSubBIE *b, void *c);

void __stdcall bfmeInvokeBIE9A60(void *thing, void *c)
{
	BfmeSubBIE *sub;
	sub = (BfmeSubBIE *)((char *)thing + 0x38);
	bfmeDoBIE((BfmeThingBIE *)thing, sub, c);
}
