class BfmeSubDEG;
class BfmeGlobalDEG
{
public:
	virtual void bfmeSpareDEG0();
	virtual void bfmeSpareDEG1();
	virtual void bfmeSpareDEG2();
	virtual void bfmeSpareDEG3();
	virtual void bfmeSpareDEG4();
	virtual void bfmeSpareDEG5();
	virtual void bfmeSpareDEG6();
	virtual void bfmeSpareDEG7();
	virtual void bfmeSpareDEG8();
	virtual void bfmeSpareDEG9();
	virtual void bfmeSpareDEG10();
	virtual void bfmeSpareDEG11();
	virtual void bfmeSpareDEG12();
	virtual void bfmeSpareDEG13();
	virtual void bfmeSpareDEG14();
	virtual void bfmeSpareDEG15();
	virtual void bfmeSpareDEG16();
	virtual void bfmeSpareDEG17();
	virtual void bfmeSpareDEG18();
	virtual void bfmeSpareDEG19();
	virtual void bfmeSpareDEG20();
	virtual void bfmeSpareDEG21();
	virtual void bfmeSpareDEG22();
	virtual void bfmeSpareDEG23();
	virtual void bfmeSpareDEG24();
	virtual void bfmeSpareDEG25();
	virtual void bfmeSpareDEG26();
	virtual void bfmeSpareDEG27();
	virtual void bfmeSpareDEG28();
	virtual void bfmeSpareDEG29();
	virtual void bfmeSpareDEG30();
	virtual void bfmeSpareDEG31();
	virtual void bfmeSpareDEG32();
	virtual void bfmeSpareDEG33();
	virtual void bfmeSpareDEG34();
	virtual void bfmeSpareDEG35();
	virtual void bfmeSpareDEG36();
	virtual void bfmeSpareDEG37();
	virtual void bfmeSpareDEG38();
	virtual void bfmeSpareDEG39();
	virtual void bfmeSpareDEG40();
	virtual void bfmeSpareDEG41();
	virtual void bfmeSpareDEG42();
	virtual void bfmeSpareDEG43();
	virtual void bfmeRunDEG(BfmeSubDEG *sub, int flag);
};

extern BfmeGlobalDEG *bfmeTheDEG;

class BfmeSubDEG
{
	unsigned char m_bfmeHead[4];
};

struct BfmeThingDEG
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubDEG m_bfmeSub;
};

void __stdcall bfmeGoDEG(BfmeThingDEG *a)
{
	bfmeTheDEG->bfmeRunDEG(&a->m_bfmeSub, 1);
}
