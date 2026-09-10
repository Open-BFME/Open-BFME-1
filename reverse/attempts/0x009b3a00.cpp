// ?bfmeStep1_009A75E0@@YAXXZ
// partial score=0.98 date=2026-09-10
// Six more one-liners: 0x001FB570, 0x001FBF60 and 0x00204450, then
// 0x004647E0, 0x00589680 and 0x009A75E0.
//
// The first three are the same eleven bytes apart from where the linker put
// them, and all three jump to the same slot. They read a pointer at a NEGATIVE
// displacement, this-0x1C, which is the enclosing object reached by walking
// back out of an embedded sub-object; then add eight to land on a sub-object
// of what that pointer names, and tail-jump. Both steps are plain adds because
// both offsets are known at compile time.
//
// The last three are a call followed by a tail jump with no arguments in
// sight, which is just two statements in a void function -- the second one is
// in tail position so it becomes a jump rather than a call plus ret.

class Gen_0002644FTarget
{
public:
	void bfmeForward(void);					// ILT 0x0002644F
};

class Gen_001FB570Holder
{
public:
	char m_bfmeHead[8];
	Gen_0002644FTarget m_bfmeSub;				// +0x08
};

class Gen_001FB570
{
public:
	void bfmeForward(void);
};

class Gen_001FBF60
{
public:
	void bfmeForward(void);
};

class Gen_00204450
{
public:
	void bfmeForward(void);
};

void bfmeStep1_004647E0(void);					// ILT 0x0002B314
void bfmeStep2_004647E0(void);					// ILT 0x00039F1D
void bfmeStep1_00589680(void);					// ILT 0x0003643A
void bfmeStep2_00589680(void);					// ILT 0x000216D9
void bfmeStep1_009A75E0(void);					// retail 0x009B3A00
void bfmeStep2_009A75E0(void);					// retail 0x009B3B40

// ?bfmeStep1_009A75E0@@YAXXZ
// The runner at 0x009A75E0 calls this table initializer first.  Retail's
// complete body is 140 bytes through ret at 0x009B3A8B; the older 131-byte
// reloc-derived extent stopped before the full epilogue.  The four sentinel
// rows and seven four-word copies are kept as explicit indexed stores so the
// compiler retains the same absolute table/source addresses and loop shape.
extern unsigned short Rva009B3A00Table[48];
extern unsigned short Rva009B3A00Source[7];

struct FourWords { unsigned short a,b,c,d; };

void bfmeStep1_009A75E0(void)
{
	unsigned short *table = Rva009B3A00Table;
	unsigned short *clear = table + 16;
	while (clear != table)
	{
		--clear;
		*clear = 0;
	}

	unsigned short allBits = 0xffff;
	table[15] = allBits;
	table[10] = allBits;
	table[5] = allBits;
	table[0] = allBits;

	int stride = 8;
	FourWords *destination = (FourWords *)(table + 16);
	unsigned short *source = Rva009B3A00Source;
	do
	{
		unsigned short value = *source;
		destination->d = value;
		destination->c = value;
		destination->b = value;
		destination->a = value;
		destination = (FourWords *)((int)destination + stride);
		++source;
	} while ((int)&destination->c <= (int)(table + 42));

	table[47] = stride;
	table[46] = stride;
	table[45] = stride;
	table[44] = stride;
}

// ?bfmeForward@Gen_001FB570@@QAEXXZ
void Gen_001FB570::bfmeForward(void)
{
	Gen_001FB570Holder *holder = *(Gen_001FB570Holder **)((char *)this - 0x1C);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_001FBF60@@QAEXXZ
void Gen_001FBF60::bfmeForward(void)
{
	Gen_001FB570Holder *holder = *(Gen_001FB570Holder **)((char *)this - 0x1C);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeForward@Gen_00204450@@QAEXXZ
void Gen_00204450::bfmeForward(void)
{
	Gen_001FB570Holder *holder = *(Gen_001FB570Holder **)((char *)this - 0x1C);

	holder->m_bfmeSub.bfmeForward();
}

// ?bfmeRun_004647E0@@YAXXZ
void bfmeRun_004647E0(void)
{
	bfmeStep1_004647E0();
	bfmeStep2_004647E0();
}

// ?bfmeRun_00589680@@YAXXZ
void bfmeRun_00589680(void)
{
	bfmeStep1_00589680();
	bfmeStep2_00589680();
}

// ?bfmeRun_009A75E0@@YAXXZ
void bfmeRun_009A75E0(void)
{
	bfmeStep1_009A75E0();
	bfmeStep2_009A75E0();
}
