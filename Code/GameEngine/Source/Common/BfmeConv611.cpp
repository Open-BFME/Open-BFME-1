class BfmeSubCLA
{
public:
	virtual void bfmeSpareCLA0();
	virtual void bfmeSpareCLA1();
	virtual void bfmeSpareCLA2();
	virtual void bfmeSpareCLA3();
	virtual void bfmeSpareCLA4();
	virtual void bfmeSpareCLA5();
	virtual void bfmeSpareCLA6();
	virtual void bfmeSpareCLA7();
	virtual void bfmeSpareCLA8();
	virtual void bfmeSpareCLA9();
	virtual void bfmeSpareCLA10();
	virtual void bfmeSpareCLA11();
	virtual void bfmeSpareCLA12();
	virtual void bfmeSpareCLA13();
	virtual void bfmeSpareCLA14();
	virtual void bfmeSpareCLA15();
	virtual void bfmeSpareCLA16();
	virtual void bfmeSpareCLA17();
	virtual void bfmeSpareCLA18();
	virtual void bfmeSpareCLA19();
	virtual void bfmeSpareCLA20();
	virtual void bfmeSpareCLA21();
	virtual void bfmeSpareCLA22();
	virtual void bfmeSpareCLA23();
	virtual void bfmeSpareCLA24();
	virtual void bfmeSpareCLA25();
	virtual void bfmeSpareCLA26();
	virtual void bfmeSpareCLA27();
	virtual void bfmeSpareCLA28();
	virtual void bfmeSpareCLA29();
	virtual void bfmeSpareCLA30();
	virtual void bfmeSpareCLA31();
	virtual void bfmeSpareCLA32();
	virtual void bfmeSpareCLA33();
	virtual void bfmeSpareCLA34();
	virtual void bfmeSpareCLA35();
	virtual void bfmeSpareCLA36();
	virtual void bfmeSpareCLA37();
	virtual void bfmeSpareCLA38();
	virtual void bfmeSpareCLA39();
	virtual void bfmeSpareCLA40();
	virtual void bfmeSpareCLA41();
	virtual void bfmeSpareCLA42();
	virtual void bfmeSpareCLA43();
	virtual void bfmeSpareCLA44();
	virtual void bfmeSpareCLA45();
	virtual void bfmeSpareCLA46();
	virtual void bfmeSpareCLA47();
	virtual void bfmeSpareCLA48();
	virtual void bfmeSpareCLA49();
	virtual void bfmeSpareCLA50();
	virtual void bfmeSpareCLA51();
	virtual void bfmeSpareCLA52();
	virtual void bfmeSpareCLA53();
	virtual void bfmeSpareCLA54();
	virtual void bfmeSpareCLA55();
	virtual void bfmeSpareCLA56();
	virtual void bfmeSpareCLA57();
	virtual void bfmeSpareCLA58();
	virtual void bfmeSpareCLA59();
	virtual void bfmeSpareCLA60();
	virtual void bfmeSpareCLA61();
	virtual void bfmeSpareCLA62();
	virtual void bfmeSpareCLA63();
	virtual void bfmeSpareCLA64();
	virtual void bfmeSpareCLA65();
	virtual void bfmeSpareCLA66();
	virtual void bfmeSpareCLA67();
	virtual void bfmeSpareCLA68();
	virtual void bfmeSpareCLA69();
	virtual void bfmeSpareCLA70();
	virtual void bfmeSpareCLA71();
	virtual void bfmeSpareCLA72();
	virtual void bfmeSpareCLA73();
	virtual void bfmeSpareCLA74();
	virtual void bfmeSpareCLA75();
	virtual void bfmeSpareCLA76();
	virtual void bfmeSpareCLA77();
	virtual void bfmeSpareCLA78();
	virtual void bfmeSpareCLA79();
	virtual void bfmeSpareCLA80();
	virtual void bfmeSpareCLA81();
	virtual void bfmeSpareCLA82();
	virtual void bfmeSpareCLA83();
	virtual void bfmeSpareCLA84();
	virtual void bfmeSpareCLA85();
	virtual void bfmeSpareCLA86();
	virtual void bfmeSpareCLA87();
	virtual void bfmeSpareCLA88();
	virtual void bfmeSpareCLA89();
	virtual void bfmeSpareCLA90();
	virtual void bfmeSpareCLA91();
	virtual void bfmeSpareCLA92();
	virtual void bfmeSpareCLA93();
	virtual void bfmeSpareCLA94();
	virtual void bfmeSpareCLA95();
	virtual void bfmeSpareCLA96();
	virtual void bfmeSpareCLA97();
	virtual void bfmeSpareCLA98();
	virtual void bfmeSpareCLA99();
	virtual void bfmeSpareCLA100();
	virtual void bfmeSpareCLA101();
	virtual void bfmeSpareCLA102();
	virtual void bfmeSpareCLA103();
	virtual void bfmeSpareCLA104();
	virtual void bfmeSpareCLA105();
	virtual void bfmeSpareCLA106();
	virtual void bfmeSpareCLA107();
	virtual void bfmeSpareCLA108();
	virtual void bfmeSpareCLA109();
	virtual void bfmeSpareCLA110();
	virtual void bfmeSpareCLA111();
	virtual void bfmeSpareCLA112();
	virtual void bfmeSpareCLA113();
	virtual void bfmeSpareCLA114();
	virtual void bfmeSpareCLA115();
	virtual void bfmeSpareCLA116();
	virtual void bfmeSpareCLA117();
	virtual void bfmeSpareCLA118();
	virtual void bfmeSpareCLA119();
	virtual void bfmeSpareCLA120();
	virtual void bfmeSpareCLA121();
	virtual void bfmeSpareCLA122();
	virtual void bfmeSpareCLA123();
	virtual void bfmeSpareCLA124();
	virtual void bfmeSpareCLA125();
	virtual void bfmeSpareCLA126();
	virtual void bfmeRunCLA(void *what);
};

struct BfmeMidCLA
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubCLA *m_bfmeSub;
};

struct BfmeOwnerCLA
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidCLA *m_bfmeMid;
};

class BfmeThingCLA
{
public:
	void bfmeBaseCLA(void *what);
	void bfmeGoCLA(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCLA *m_bfmeOwner;
};

void BfmeThingCLA::bfmeGoCLA(void *what)
{
	bfmeBaseCLA(what);
	BfmeSubCLA *sub = m_bfmeOwner->m_bfmeMid->m_bfmeSub;
	if (sub != 0)
		sub->bfmeRunCLA(0);
}
