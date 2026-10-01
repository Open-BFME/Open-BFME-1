// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of bfmeGoVHL (0x0025A930, BfmeConv1363.cpp); this body guards on
// a passed pointer instead of _bfme_debugReportingEnabled() and reports through the
// the debug manager g_rva00889690 (0x01336E5C), the same singleton BfmeConv1363.cpp
// reaches through the same spelling.

void __cdecl bfmeRecordVHJ(int n);

class BfmeMsgIBD
{
public:
	virtual class BfmeMsgIBD *bfmeSlot00IBD(void *t);
	virtual void bfmeSlot04IBD();
	virtual void bfmeSlot08IBD();
	virtual void bfmeSlot0CIBD();
	virtual void bfmeSlot10IBD();
	virtual void bfmeSlot14IBD();
	virtual void bfmeSlot18IBD();
	virtual void bfmeSlot1CIBD();
	virtual void bfmeSlot20IBD();
	virtual void bfmeSlot24IBD();
	virtual void bfmeSlot28IBD();
	virtual void bfmeSlot2CIBD();
	virtual void bfmeSlot30IBD();
	virtual void bfmeSlot34IBD();
	virtual class BfmeMsgIBD *bfmeSlot38IBD(const void *t);
	virtual void bfmeSlot3CIBD();
	virtual void bfmeSlot40IBD();
	virtual void bfmeSlot44IBD();
	virtual void bfmeSlot48IBD();
	virtual void bfmeSlot4cIBD(int n);
	virtual void bfmeSlot50IBD();
	virtual void bfmeSlot54IBD();
	virtual void bfmeSlot58IBD();
	virtual void bfmeSlot5CIBD();
	virtual void bfmeSlot60IBD();
	virtual void bfmeSlot64IBD();
	virtual void bfmeSlot68IBD();
	virtual void bfmeSlot6CIBD();
};

struct Rva00889690Obj
{
public:
	virtual void bfmeOwn00IBD();
	virtual void bfmeOwn04IBD();
	virtual void bfmeOwn08IBD();
	virtual void bfmeOwn0CIBD();
	virtual void bfmeOwn10IBD();
	virtual void bfmeOwn14IBD();
	virtual void bfmeOwn18IBD();
	virtual void bfmeOwn1CIBD();
	virtual void bfmeOwn20IBD();
	virtual void bfmeOwn24IBD();
	virtual void bfmeOwn28IBD();
	virtual void bfmeOwn2CIBD();
	virtual void bfmeOwn30IBD();
	virtual void bfmeOwn34IBD();
	virtual void bfmeOwn38IBD();
	virtual void bfmeOwn3CIBD();
	virtual void bfmeOwn40IBD();
	virtual void bfmeOwn44IBD();
	virtual void bfmeOwn48IBD();
	virtual void bfmeOwn4CIBD();
	virtual void bfmeOwn50IBD();
	virtual void bfmeOwn54IBD();
	virtual void bfmeOwn58IBD();
	virtual void bfmeOwn5CIBD();
	virtual void bfmeOwn60IBD();
	virtual void bfmeOwn64IBD();
	virtual void bfmeOwn68IBD();
	virtual class BfmeMsgIBD *bfmeOwn6cIBD(int a, int b);
};

extern Rva00889690Obj *g_rva00889690;

// ?d_006c07d0@@YAXXZ
void __cdecl Rva006C07D0(void *param)
{
	if (param)
	{
		bfmeRecordVHJ(1);
		g_rva00889690->bfmeOwn60IBD();
		g_rva00889690->bfmeOwn6cIBD(0, 0)->bfmeSlot38IBD((const void *)"DX8 error ")->bfmeSlot00IBD(param)->bfmeSlot4cIBD(1);
	}
}
