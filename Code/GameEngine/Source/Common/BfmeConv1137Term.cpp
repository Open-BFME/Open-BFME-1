// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 conversions.
// ghidra: FUN_00b23f30 retail @ 0x00723F30 size 96 (BfmeA1137's own destructor;
// releases the m_bfme6c texture-like reference, then delegates to the base
// class subobject destructor -- see BfmeConv1137.cpp for the sibling ctor).

// matched gen-thunk row (Code/gen_small/thunks_035.cpp) tail-jumping to
// ?d_00723ac0@@YAXXZ / BfmeA1137Term's own sibling destructor at 0x00723AC0
void __cdecl j_000491c5();

class BfmeTex1137Term
{
public:
	void Release_Ref();
};

class BfmeTexRefTerm1137
{
public:
	~BfmeTexRefTerm1137();
	BfmeTex1137Term *p;
};

BfmeTexRefTerm1137::~BfmeTexRefTerm1137()
{
	if (p)
		p->Release_Ref();
}

class BfmeBaseTerm1137A
{
public:
	virtual ~BfmeBaseTerm1137A();
	int m_base04;
};

class BfmeA1137Term : public BfmeBaseTerm1137A
{
public:
	virtual ~BfmeA1137Term();
	char m_bfmePad[0x64];
	BfmeTexRefTerm1137 m_bfme6c;
};

BfmeA1137Term::~BfmeA1137Term()
{
	j_000491c5();
}
