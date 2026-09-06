// ?bfmeLookupERK@@YA?AVBfmeHandleERK@@V1@@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 141/141, every instruction matches except WHERE the unwind state is raised to 1:
// retail does it just before the handle ctor, MSVC does it at function entry.
// Destructor recovered from the EH unwind map: 0x00970860 (emitted as ?dup_00970860).
// Pins: ctor 0x00970940, find 0x009EBCE0, release 0x009EB7A0.
class BfmeProtoERK
{
public:
	void bfmeReleaseERK(void);
};

class BfmeHandleERK
{
public:
	BfmeHandleERK(void) : m_bfmePtrERK(0) {}
	BfmeHandleERK(void *proto);
	~BfmeHandleERK(void)
	{
		if (m_bfmePtrERK != 0)
			m_bfmePtrERK->bfmeReleaseERK();
	}

	BfmeProtoERK *m_bfmePtrERK;
};

void *__cdecl bfmeFindERK(BfmeHandleERK *slot, BfmeProtoERK *proto);

BfmeHandleERK __cdecl bfmeLookupERK(BfmeHandleERK proto)
{
	if (proto.m_bfmePtrERK == 0)
		return BfmeHandleERK();

	void *found = bfmeFindERK(&proto, proto.m_bfmePtrERK);
	return BfmeHandleERK(found);
}
