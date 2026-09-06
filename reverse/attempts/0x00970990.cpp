// ?bfmeLookupERK@@YA?AVBfmeHandleERK@@PAVBfmeProtoERK@@@Z (identity unknown)
// partial score=0.7 date=2026-09-06
// 145/141 with the destructor DECLARED (unresolved REL32 from the unwind funclet);
// 69/141 with it defined inline empty, which removes the SEH frame.
// Pins: handle ctor 0x00970940, find 0x009EBCE0, release 0x009EB7A0.
class BfmeProtoERK
{
public:
	void bfmeReleaseERK(void);
};

void *__cdecl bfmeFindERK(BfmeProtoERK **slot, BfmeProtoERK *proto);

class BfmeHandleERK
{
public:
	BfmeHandleERK(void) : m_bfmePtrERK(0) {}
	BfmeHandleERK(void *proto);
	~BfmeHandleERK(void);

	void *m_bfmePtrERK;
};

BfmeHandleERK __cdecl bfmeLookupERK(BfmeProtoERK *proto)
{
	if (proto != 0)
	{
		void *found = bfmeFindERK(&proto, proto);
		BfmeHandleERK handle(found);
		if (proto != 0)
			proto->bfmeReleaseERK();
		return handle;
	}
	return BfmeHandleERK();
}
