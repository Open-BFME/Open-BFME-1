class BfmeSubDEF;
class BfmeGlobalDEF
{
public:
	virtual void bfmeSpareDEF0();
	virtual void bfmeSpareDEF1();
	virtual void bfmeSpareDEF2();
	virtual void bfmeSpareDEF3();
	virtual void bfmeSpareDEF4();
	virtual void bfmeSpareDEF5();
	virtual void bfmeSpareDEF6();
	virtual void bfmeSpareDEF7();
	virtual void bfmeSpareDEF8();
	virtual void bfmeSpareDEF9();
	virtual void bfmeSpareDEF10();
	virtual void bfmeSpareDEF11();
	virtual void bfmeSpareDEF12();
	virtual void bfmeSpareDEF13();
	virtual void bfmeSpareDEF14();
	virtual void bfmeSpareDEF15();
	virtual void bfmeSpareDEF16();
	virtual void bfmeSpareDEF17();
	virtual void bfmeSpareDEF18();
	virtual void bfmeSpareDEF19();
	virtual void bfmeSpareDEF20();
	virtual void bfmeSpareDEF21();
	virtual void bfmeSpareDEF22();
	virtual void bfmeSpareDEF23();
	virtual void bfmeSpareDEF24();
	virtual void bfmeSpareDEF25();
	virtual void bfmeSpareDEF26();
	virtual void bfmeSpareDEF27();
	virtual void bfmeSpareDEF28();
	virtual void bfmeSpareDEF29();
	virtual void bfmeSpareDEF30();
	virtual void bfmeSpareDEF31();
	virtual void bfmeSpareDEF32();
	virtual void bfmeSpareDEF33();
	virtual void bfmeSpareDEF34();
	virtual void bfmeSpareDEF35();
	virtual void bfmeSpareDEF36();
	virtual void bfmeSpareDEF37();
	virtual void bfmeSpareDEF38();
	virtual void bfmeSpareDEF39();
	virtual void bfmeSpareDEF40();
	virtual void bfmeSpareDEF41();
	virtual void bfmeSpareDEF42();
	virtual void bfmeRunDEF(BfmeSubDEF *sub, int flag);
};

extern BfmeGlobalDEF *bfmeTheDEF;

class BfmeSubDEF
{
	unsigned char m_bfmeHead[4];
};

struct BfmeThingDEF
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubDEF m_bfmeSub;
};

void __stdcall bfmeGoDEF(BfmeThingDEF *a)
{
	bfmeTheDEF->bfmeRunDEF(&a->m_bfmeSub, 1);
}
