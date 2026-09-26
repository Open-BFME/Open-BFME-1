// ?j_0002a969@Glo012F1024Item@@QAEXXZ
// partial score=0.68 date=2026-09-17
// Reviewer correction: identity is established by the matched run and
// bfmeEnter callers plus reverse/reloc_names.csv. The declarations below use
// the witnessed Glo012F1024 offsets and independently matched callee
// contracts. This remains a banked near miss and is not a generated-body lift.
//
// Verified direct-call contract in retail order: operator new,
// BfmeBoxVNF::bfmeInitVNF at 0x003BBD70 through 0x0003E405,
// Rva003C2280Owner::append at 0x003C2280 through 0x00003F0D,
// BfmeRectVNI::BfmeRectVNI at 0x003BC360 through 0x00027A61,
// Gen_00064110::m at 0x00064110 through 0x0002E1DB, and the tree assignment
// through the full 0x00013ABB -> 0x000650B0 -> 0x00048013 -> 0x00064E90
// thunk chain. The old _M_advance spelling was removed: it was not this call.
//
// The outer Glo012F1024Item vector members are witnessed at +0x78 and +0x84
// by Glo012F1024Entry_bfmeStep.cpp. The target tree's exact template owner is
// still unproven, so Rva00064E90Tree is deliberately address-derived and no
// new pin is claimed for it.
//
// Remaining blocker after correction: the MSVC 7.1 EH/local-allocation order
// still differs from retail while the exact tree specialization is unresolved.

// Stash of the corrected near-miss body only. Do not merge as-is.
// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void *operator new(unsigned int bytes);

// Only the 8-byte object shape is established for this field. Its semantic
// owner and template specialization are intentionally not guessed.
class Rva00064E90Tree
{
public:
	Rva00064E90Tree &operator=(const Rva00064E90Tree &other);
	char m_bfmeBody[0x08];
};

class BfmeFlag24
{
public:
	char m_bfmePad0[0x04];
	unsigned int m_bfmeA;
	unsigned char m_bfmeFlag;
	char m_bfmePad9[0x03];
	Rva00064E90Tree m_bfmeMap;
	char m_bfmeTail14[0x04];
};

struct BfmeVecVNF
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

class BfmeFlag32
{
public:
	char m_bfmePad0[0x04];
	unsigned int m_bfmeA;
	struct BfmeVecVNF m_bfmeVec;
	float m_bfmeN;
	unsigned int m_bfmeH;
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};

// Raw allocation followed by the independently matched initializer is the
// only proven contract for this call site; it is not a constructor claim.
class BfmeBoxVNF
{
public:
	BfmeBoxVNF *bfmeInitVNF(unsigned int w, const BfmeVecVNF *v, int n,
		unsigned int h, char f);
	void *volatile m_bfme00;
	unsigned int m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	unsigned int m_bfme1c;
};

class BfmeBaseVNI
{
public:
	BfmeBaseVNI(unsigned int w, char f);
	virtual ~BfmeBaseVNI();
	virtual void handle();
	unsigned int m_bfme04;
	char m_bfme08;
};

class BfmeRectVNI : public BfmeBaseVNI
{
public:
	BfmeRectVNI(unsigned int w, char f);
	Rva00064E90Tree m_bfmeMap;
	int m_at14;
	int m_at18;
};

class Rva003C2280Item
{
public:
	char m_pad00[8];
	bool m_flag;
};

class Rva003C2280Owner
{
public:
	void append(const Rva003C2280Item *item);
};

class Gen_00064110
{
public:
	void *m(void);
};

class Glo012F1024Item
{
public:
	void j_0002a969(void);
	char m_bfmePad[0x78];
	BfmeFlag32 *m_bfmeFlag32Begin;
	BfmeFlag32 *m_bfmeFlag32End;
	char m_bfmePad80[0x04];
	BfmeFlag24 *m_bfmeFlag24Begin;
	BfmeFlag24 *m_bfmeFlag24End;
};

extern Rva003C2280Owner *Glo012F1028;

void Glo012F1024Item::j_0002a969(void)
{
	Glo012F1024Item *self = this;
	unsigned int index = 0;
	int keep = -1;

	for (; index < (unsigned int)(self->m_bfmeFlag32End - self->m_bfmeFlag32Begin); ++index)
	{
		_ReadWriteBarrier();
		const BfmeFlag32 *begin = self->m_bfmeFlag32Begin;
		char flag = (char)(begin + index)->m_bfmeFlag;
		float n = (begin + index)->m_bfmeN;
		unsigned int h = (begin + index)->m_bfmeH;
		BfmeBoxVNF *node = (BfmeBoxVNF *)operator new(0x20);
		node->bfmeInitVNF(
			(begin + index)->m_bfmeA,
			&(begin + index)->m_bfmeVec,
			*(int *)(void *)&n,
			h,
			flag);
		keep = -1;
		Glo012F1028->append((const Rva003C2280Item *)node);
	}

	for (BfmeFlag24 *element = self->m_bfmeFlag24Begin; element != self->m_bfmeFlag24End; ++element)
	{
		BfmeRectVNI *node = new BfmeRectVNI(element->m_bfmeA, (char)element->m_bfmeFlag);
		node->m_bfmeMap = *(Rva00064E90Tree *)((Gen_00064110 *)&element->m_bfmeMap)->m();
		Glo012F1028->append((const Rva003C2280Item *)node);
	}
}
