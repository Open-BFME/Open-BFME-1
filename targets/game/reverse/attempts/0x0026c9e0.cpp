// ?bfmeConv1060Reduced@Rva0026C9E0Owner@@QAEXXZ
// partial score=0.1 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: address-derived attempt for the BFME hero-mode/status-flag
// update helper at retail 0x0026C9E0 (406 B). No Zero Hour twin -- callees
// are BFME-only renames (BfmeThing3E0::doInit, BfmeOwnerVNI::bfmeApply1VNI,
// BfmeRvaBA00Object::action, BfmeQ1060::bfmeConv1060, BFX_Member::bind).
// Literal register-level translation of tools/dis_retail.py 0x0026C9E0; the
// SEH frame (fs:[0] chain) and the 0x12EFD9C one-time-init guard are not
// faithfully reconstructed yet -- see ledger notes for open questions.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class BfmeThing3E0
{
public:
	void doInit(void);					// ILT 0x0003FA30
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI(void);				// ILT 0x0002191D

	unsigned char m_bfmeGap[0x128];
	UnsignedInt m_bfmeFlags;				// +0x128
};

class BfmeRvaBA00Object
{
public:
	void action(Int kind);					// ILT 0x000122AB
};

extern void j_0000c1ee(BfmeRvaBA00Object *self, Int kind);	// still-unidentified ILT 0x0000C1EE

class BfmeQ1060
{
public:
	Int bfmeConv1060(Int kind);				// ILT 0x0003ADD7
};

class BFX_Member
{
public:
	Int bind(void *pool);					// ILT 0x0002AE23
};

extern void j_0003b5b1(BFX_Member *self, Int flag);		// still-unidentified ILT 0x0003B5B1

class BfmeObjE10
{
public:
	void actionA(Int kind);				// ILT 0x000348EC
};

extern UnsignedInt g_bfmeOnceFlag;				// 0x012EFD9C
extern void *g_bfmeNameKey;					// 0x012EFD98
extern void *g_theNameKeyGenerator;				// 0x012ED600

class Rva0026C9E0Owner :
	public BfmeThing3E0,
	public BfmeOwnerVNI,
	public BfmeRvaBA00Object,
	public BfmeQ1060,
	public BFX_Member,
	public BfmeObjE10
{
public:
	void bfmeConv1060Reduced(void);

	unsigned char m_bfmeGap2[0x8];
	void *m_bfmeSub;					// +0x08
};

void Rva0026C9E0Owner::bfmeConv1060Reduced(void)
{
	doInit();

	BfmeOwnerVNI *sub = (BfmeOwnerVNI *)m_bfmeSub;

	if ((sub->m_bfmeFlags & 0x800) != 0)
	{
		sub->m_bfmeFlags &= ~0x800u;
		sub->bfmeApply1VNI();
	}

	action(0x15);
	j_0000c1ee(this, 6);

	sub->m_bfmeFlags |= 0x800;
	sub->bfmeApply1VNI();

	actionA(0x15);
	j_0000c1ee(this, 6);
}
