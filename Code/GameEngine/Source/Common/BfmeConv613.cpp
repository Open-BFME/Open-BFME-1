class BfmeSubCLB
{
public:
	virtual void bfmeSpareCLB0();
	virtual void bfmeSpareCLB1();
	virtual void bfmeSpareCLB2();
	virtual void bfmeSpareCLB3();
	virtual void bfmeSpareCLB4();
	virtual void bfmeSpareCLB5();
	virtual void bfmeSpareCLB6();
	virtual void bfmeSpareCLB7();
	virtual void bfmeSpareCLB8();
	virtual void bfmeSpareCLB9();
	virtual void bfmeSpareCLB10();
	virtual void bfmeSpareCLB11();
	virtual void bfmeSpareCLB12();
	virtual void bfmeSpareCLB13();
	virtual void bfmeSpareCLB14();
	virtual void bfmeSpareCLB15();
	virtual void bfmeSpareCLB16();
	virtual void bfmeSpareCLB17();
	virtual void bfmeSpareCLB18();
	virtual void bfmeSpareCLB19();
	virtual void bfmeSpareCLB20();
	virtual void bfmeSpareCLB21();
	virtual void bfmeSpareCLB22();
	virtual void bfmeSpareCLB23();
	virtual void bfmeSpareCLB24();
	virtual void bfmeSpareCLB25();
	virtual void bfmeSpareCLB26();
	virtual void bfmeSpareCLB27();
	virtual void bfmeSpareCLB28();
	virtual void bfmeSpareCLB29();
	virtual void bfmeSpareCLB30();
	virtual void bfmeSpareCLB31();
	virtual void bfmeSpareCLB32();
	virtual void bfmeSpareCLB33();
	virtual void bfmeSpareCLB34();
	virtual void bfmeSpareCLB35();
	virtual void bfmeSpareCLB36();
	virtual void bfmeSpareCLB37();
	virtual void bfmeSpareCLB38();
	virtual void bfmeSpareCLB39();
	virtual void bfmeSpareCLB40();
	virtual void bfmeSpareCLB41();
	virtual void bfmeSpareCLB42();
	virtual void bfmeSpareCLB43();
	virtual void bfmeSpareCLB44();
	virtual void bfmeSpareCLB45();
	virtual void bfmeSpareCLB46();
	virtual void bfmeSpareCLB47();
	virtual void bfmeSpareCLB48();
	virtual void bfmeSpareCLB49();
	virtual void bfmeSpareCLB50();
	virtual void bfmeSpareCLB51();
	virtual void bfmeSpareCLB52();
	virtual void bfmeSpareCLB53();
	virtual void bfmeSpareCLB54();
	virtual void bfmeSpareCLB55();
	virtual void bfmeSpareCLB56();
	virtual void bfmeSpareCLB57();
	virtual void bfmeSpareCLB58();
	virtual void bfmeSpareCLB59();
	virtual void bfmeSpareCLB60();
	virtual void bfmeSpareCLB61();
	virtual void bfmeSpareCLB62();
	virtual void bfmeSpareCLB63();
	virtual void bfmeSpareCLB64();
	virtual void bfmeSpareCLB65();
	virtual void bfmeSpareCLB66();
	virtual void bfmeSpareCLB67();
	virtual void bfmeSpareCLB68();
	virtual void bfmeSpareCLB69();
	virtual void bfmeSpareCLB70();
	virtual void bfmeSpareCLB71();
	virtual void bfmeSpareCLB72();
	virtual void bfmeSpareCLB73();
	virtual void bfmeSpareCLB74();
	virtual void bfmeSpareCLB75();
	virtual void bfmeSpareCLB76();
	virtual void bfmeSpareCLB77();
	virtual void bfmeSpareCLB78();
	virtual void bfmeSpareCLB79();
	virtual void bfmeSpareCLB80();
	virtual void bfmeSpareCLB81();
	virtual void bfmeSpareCLB82();
	virtual void bfmeSpareCLB83();
	virtual void bfmeSpareCLB84();
	virtual void bfmeSpareCLB85();
	virtual void bfmeSpareCLB86();
	virtual void bfmeSpareCLB87();
	virtual void bfmeSpareCLB88();
	virtual void bfmeSpareCLB89();
	virtual void bfmeSpareCLB90();
	virtual void bfmeSpareCLB91();
	virtual void bfmeSpareCLB92();
	virtual void bfmeSpareCLB93();
	virtual void bfmeSpareCLB94();
	virtual void bfmeSpareCLB95();
	virtual void bfmeSpareCLB96();
	virtual void bfmeSpareCLB97();
	virtual void bfmeSpareCLB98();
	virtual void bfmeSpareCLB99();
	virtual void bfmeSpareCLB100();
	virtual void bfmeSpareCLB101();
	virtual void bfmeSpareCLB102();
	virtual void bfmeSpareCLB103();
	virtual void bfmeSpareCLB104();
	virtual void bfmeSpareCLB105();
	virtual void bfmeSpareCLB106();
	virtual void bfmeSpareCLB107();
	virtual void bfmeSpareCLB108();
	virtual void bfmeSpareCLB109();
	virtual void bfmeSpareCLB110();
	virtual void bfmeSpareCLB111();
	virtual void bfmeSpareCLB112();
	virtual void bfmeSpareCLB113();
	virtual void bfmeSpareCLB114();
	virtual void bfmeSpareCLB115();
	virtual void bfmeSpareCLB116();
	virtual void bfmeSpareCLB117();
	virtual void bfmeSpareCLB118();
	virtual void bfmeSpareCLB119();
	virtual void bfmeSpareCLB120();
	virtual void bfmeSpareCLB121();
	virtual void bfmeSpareCLB122();
	virtual void bfmeSpareCLB123();
	virtual void bfmeSpareCLB124();
	virtual void bfmeSpareCLB125();
	virtual void bfmeSpareCLB126();
	virtual void bfmeRunCLB(void *what);
};

struct BfmeMidCLB
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubCLB *m_bfmeSub;
};

struct BfmeOwnerCLB
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidCLB *m_bfmeMid;
};

class BfmeThingCLB
{
public:
	void bfmeBaseCLB(void *what);
	void bfmeGoCLB(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCLB *m_bfmeOwner;
};

void BfmeThingCLB::bfmeGoCLB(void *what)
{
	bfmeBaseCLB(what);
	BfmeMidCLB *mid = m_bfmeOwner->m_bfmeMid;
	if (mid != 0)
	{
		BfmeSubCLB *sub = mid->m_bfmeSub;
		if (sub != 0)
			sub->bfmeRunCLB(0);
	}
}
