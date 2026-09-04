// ?j_0002a969@Glo012F1024Item@@QAEXXZ
// partial score=0.9 date=2026-09-04
// ?j_0002a969@Glo012F1024Item@@QAEXXZ
// partial score=0.9 date=2026-09-04
// ?j_0002a969@Glo012F1024Item@@QAEXXZ
// partial score=0.96 date=2026-09-03
// ?j_0002a969@Glo012F1024Item@@QAEXXZ
// partial score=0.96 date=2026-09-03
// closest 314 vs retail 313; push-first SEH matches /EHsc
// retail allocates before ctor-arg loads and emits `or ebp,-1` plus short jbe
// MSVC evaluates new-args first when flag/float temps are present; those temps
// are also what produce the matching 0x10 frame and xor edi, edi
// t=28 model=cursor-grok-4.6

// Stash of the near-miss body only. Do not merge as-is.
// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeMap12
{
public:
	BfmeMap12 *self(void);
	BfmeMap12 &operator=(const BfmeMap12 &other);
	int m_bfmeBody[3];
};

class BfmeFlag24
{
public:
	char m_bfmePad0[0x04];
	unsigned int m_bfmeA;
	unsigned char m_bfmeFlag;
	char m_bfmePad9[0x03];
	BfmeMap12 m_bfmeMap;
};

class BfmeFlag32
{
public:
	char m_bfmePad0[0x04];
	unsigned int m_bfmeA;
	char m_bfmeVec[0x0C];
	float m_bfmeN;
	unsigned int m_bfmeH;
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};

class BfmeNode20
{
public:
	BfmeNode20(unsigned int w, const void *v, float n, unsigned int h, char f);
	char m_bfmeBody[0x20];
};

class BfmeNode1C
{
public:
	BfmeNode1C(unsigned int a, char f);
	char m_bfmeHead[0x0C];
	BfmeMap12 m_bfmeMap;
	char m_bfmeTail[0x04];
};

class Glo012F1028Type
{
public:
	void j_00003f0d(void *item);
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

extern Glo012F1028Type *Glo012F1028;

void Glo012F1024Item::j_0002a969(void)
{
	Glo012F1024Item *self = this;
	unsigned int index = 0;
  int keep = -1;

	for (; index < (unsigned int)(self->m_bfmeFlag32End - self->m_bfmeFlag32Begin); ++index)
	{
		_ReadWriteBarrier();
		const BfmeFlag32 *begin = self->m_bfmeFlag32Begin;
		char flag;
		float n;
		unsigned int h;
		BfmeNode20 *node = new BfmeNode20(
			(begin + index)->m_bfmeA,
			(begin + index)->m_bfmeVec,
			n = (begin + index)->m_bfmeN,
			h = (begin + index)->m_bfmeH,
			flag = (char)(begin + index)->m_bfmeFlag);
		keep = -1;
		Glo012F1028->j_00003f0d(node);
	}

	for (BfmeFlag24 *element = self->m_bfmeFlag24Begin; element != self->m_bfmeFlag24End; ++element)
	{
		BfmeNode1C *node = new BfmeNode1C(element->m_bfmeA, (char)element->m_bfmeFlag);
		node->m_bfmeMap = *element->m_bfmeMap.self();
		Glo012F1028->j_00003f0d(node);
	}
}
