class BfmeSinkBHD
{
public:
	virtual void bfmeSpareBHD0();
	virtual void bfmeSpareBHD1();
	virtual void bfmeSpareBHD2();
	virtual void bfmeSpareBHD3();
	virtual void bfmeSpareBHD4();
	virtual void bfmeSpareBHD5();
	virtual void bfmeSpareBHD6();
	virtual void bfmeSpareBHD7();
	virtual void bfmeSpareBHD8();
	virtual void bfmeSpareBHD9();
	virtual void bfmeSpareBHD10();
	virtual void bfmeSpareBHD11();
	virtual void bfmeSpareBHD12();
	virtual void bfmeSpareBHD13();
	virtual void bfmeSpareBHD14();
	virtual void bfmeSpareBHD15();
	virtual void bfmeSpareBHD16();
	virtual void bfmeSpareBHD17();
	virtual void bfmeSpareBHD18();
	virtual void bfmeSpareBHD19();
	virtual void bfmeSpareBHD20();
	virtual void bfmeSpareBHD21();
	virtual void bfmeSpareBHD22();
	virtual void bfmeSpareBHD23();
	virtual void bfmeSpareBHD24();
	virtual void bfmeSpareBHD25();
	virtual void bfmeSpareBHD26();
	virtual void bfmeSpareBHD27();
	virtual void bfmeSpareBHD28();
	virtual void bfmeSpareBHD29();
	virtual void bfmeSpareBHD30();
	virtual void bfmeSpareBHD31();
	virtual void bfmeSpareBHD32();
	virtual void bfmeSpareBHD33();
	virtual void bfmeSpareBHD34();
	virtual void bfmeSpareBHD35();
	virtual void bfmeSpareBHD36();
	virtual void bfmeSpareBHD37();
	virtual void bfmeSpareBHD38();
	virtual void bfmeSpareBHD39();
	virtual void bfmeSpareBHD40();
	virtual void bfmeSpareBHD41();
	virtual void bfmeSpareBHD42();
	virtual void bfmeSpareBHD43();
	virtual void bfmeSpareBHD44();
	virtual void bfmeSpareBHD45();
	virtual void bfmeSpareBHD46();
	virtual void bfmeSpareBHD47();
	virtual void bfmeSpareBHD48();
	virtual void bfmeSpareBHD49();
	virtual void bfmeSpareBHD50();
	virtual void bfmeSpareBHD51();
	virtual void bfmeSpareBHD52();
	virtual void bfmeSpareBHD53();
	virtual void bfmeSpareBHD54();
	virtual void bfmeSpareBHD55();
	virtual void bfmeSpareBHD56();
	virtual void bfmeSpareBHD57();
	virtual void bfmeDoBHD(int what);
};

extern BfmeSinkBHD *g_bfmeSinkBHD;

void bfmeGoBHD()
{
	BfmeSinkBHD *sink = g_bfmeSinkBHD;
	if (sink != 0)
		sink->bfmeDoBHD(0);
}
