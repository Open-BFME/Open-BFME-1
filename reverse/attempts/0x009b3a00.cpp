// ?bfmeStep1_009A75E0@@YAXXZ
// partial score=0.8 date=2026-09-09
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
extern unsigned short Rva009B3A00Table[48];
extern unsigned short Rva009B3A00Source[7];

void bfmeStep1_009A75E0(void)
{
	unsigned short *clear = Rva009B3A00Table + 16;
	while (clear != Rva009B3A00Table)
	{
		--clear;
		*clear = 0;
	}

	unsigned short allBits = 0xffff;
	Rva009B3A00Table[15] = allBits;
	Rva009B3A00Table[10] = allBits;
	Rva009B3A00Table[5] = allBits;
	Rva009B3A00Table[0] = allBits;

	unsigned short *destination = Rva009B3A00Table + 18;
	unsigned short *source = Rva009B3A00Source;
	while (destination <= Rva009B3A00Table + 42)
	{
		unsigned short value = *source;
		destination[1] = value;
		destination[0] = value;
		destination[-1] = value;
		destination[-2] = value;
		destination += 4;
		++source;
	}

	unsigned short stride = 8;
	Rva009B3A00Table[47] = stride;
	Rva009B3A00Table[46] = stride;
	Rva009B3A00Table[45] = stride;
	Rva009B3A00Table[44] = stride;
}
void bfmeStep2_009A75E0(void);					// retail 0x009B3B40

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
