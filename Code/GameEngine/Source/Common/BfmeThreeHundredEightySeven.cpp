class BfmeTargetAED
{
public:
	virtual void bfmeSpareAEDa0();
	virtual void bfmeSpareAEDa1();
	virtual void bfmeSpareAEDa2();
	virtual void bfmeSpareAEDa3();
	virtual void bfmeSpareAEDa4();
	virtual void bfmeSpareAEDa5();
	virtual void bfmeSpareAEDa6();
	virtual void bfmeSpareAEDa7();
	virtual void bfmeSpareAEDa8();
	virtual void bfmeSpareAEDa9();
	virtual void bfmeSpareAEDa10();
	virtual void bfmeSpareAEDa11();
	virtual void bfmeSpareAEDa12();
	virtual void bfmeSpareAEDa13();
	virtual void bfmeSpareAEDa14();
	virtual void bfmeSpareAEDa15();
	virtual void bfmeSpareAEDa16();
	virtual void bfmeSpareAEDa17();
	virtual void bfmeSpareAEDa18();
	virtual void bfmeSpareAEDa19();
	virtual void bfmeSpareAEDa20();
	virtual void bfmeSpareAEDa21();
	virtual void bfmeSpareAEDa22();
	virtual void bfmeSpareAEDa23();
	virtual void bfmeSpareAEDa24();
	virtual void bfmeSpareAEDa25();
	virtual void bfmeSpareAEDa26();
	virtual void bfmeSpareAEDa27();
	virtual void bfmeSpareAEDa28();
	virtual void bfmeSpareAEDa29();
	virtual void bfmeSpareAEDa30();
	virtual void bfmeSpareAEDa31();
	virtual void bfmeSpareAEDa32();
	virtual void bfmeSpareAEDa33();
	virtual void bfmeSpareAEDa34();
	virtual void bfmeSpareAEDa35();
	virtual void bfmeSpareAEDa36();
	virtual void bfmeSpareAEDa37();
	virtual void bfmeSpareAEDa38();
	virtual void bfmeSpareAEDa39();
	virtual void bfmeSpareAEDa40();
	virtual void bfmeSpareAEDa41();
	virtual void bfmeSpareAEDa42();
	virtual void bfmeSpareAEDa43();
	virtual void bfmeSpareAEDa44();
	virtual void bfmeSpareAEDa45();
	virtual void bfmeSpareAEDa46();
	virtual void bfmeSpareAEDa47();
	virtual void bfmeSpareAEDa48();
	virtual void bfmeSpareAEDa49();
	virtual void bfmeSpareAEDa50();
	virtual void bfmeSpareAEDa51();
	virtual void bfmeSpareAEDa52();
	virtual void bfmeSpareAEDa53();
	virtual void bfmeSpareAEDa54();
	virtual void bfmeSpareAEDa55();
	virtual void bfmeSpareAEDa56();
	virtual void bfmeSpareAEDa57();
	virtual void bfmeSpareAEDa58();
	virtual void bfmeSpareAEDa59();
	virtual void bfmeSpareAEDa60();
	virtual void bfmeSpareAEDa61();
	virtual void bfmeSpareAEDa62();
	virtual void bfmeSpareAEDa63();
	virtual void bfmeSpareAEDa64();
	virtual void bfmeSpareAEDa65();
	virtual void bfmeSpareAEDa66();
	virtual void bfmeSpareAEDa67();
	virtual void bfmeSpareAEDa68();
	virtual void bfmeSpareAEDa69();
	virtual void bfmeSpareAEDa70();
	virtual void bfmeSpareAEDa71();
	virtual void bfmeSpareAEDa72();
	virtual void bfmeSpareAEDa73();
	virtual void bfmeSpareAEDa74();
	virtual void bfmeSpareAEDa75();
	virtual void bfmeSpareAEDa76();
	virtual void bfmeSpareAEDa77();
	virtual void bfmeSpareAEDa78();
	virtual void bfmeSpareAEDa79();
	virtual void bfmeSpareAEDa80();
	virtual void bfmeSpareAEDa81();
	virtual void bfmeSpareAEDa82();
	virtual void bfmeSpareAEDa83();
	virtual void bfmeSpareAEDa84();
	virtual void bfmeSpareAEDa85();
	virtual void bfmeSpareAEDa86();
	virtual void bfmeSpareAEDa87();
	virtual void bfmeSpareAEDa88();
	virtual void bfmeSpareAEDa89();
	virtual void bfmeSpareAEDa90();
	virtual void bfmeSpareAEDa91();
	virtual void bfmeSendAED(int what);
};

class BfmeFinderAED
{
public:
	virtual void bfmeSpareAEDb0();
	virtual void bfmeSpareAEDb1();
	virtual void bfmeSpareAEDb2();
	virtual void bfmeSpareAEDb3();
	virtual void bfmeSpareAEDb4();
	virtual void bfmeSpareAEDb5();
	virtual void bfmeSpareAEDb6();
	virtual void bfmeSpareAEDb7();
	virtual void bfmeSpareAEDb8();
	virtual void bfmeSpareAEDb9();
	virtual void bfmeSpareAEDb10();
	virtual void bfmeSpareAEDb11();
	virtual void bfmeSpareAEDb12();
	virtual void bfmeSpareAEDb13();
	virtual void bfmeSpareAEDb14();
	virtual void bfmeSpareAEDb15();
	virtual void bfmeSpareAEDb16();
	virtual void bfmeSpareAEDb17();
	virtual void bfmeSpareAEDb18();
	virtual void bfmeSpareAEDb19();
	virtual void bfmeSpareAEDb20();
	virtual void bfmeSpareAEDb21();
	virtual void bfmeSpareAEDb22();
	virtual void bfmeSpareAEDb23();
	virtual void bfmeSpareAEDb24();
	virtual void bfmeSpareAEDb25();
	virtual BfmeTargetAED *bfmeFindAED();
};

class Rva0028EF00Clear
{
public:
	void clearAt(int what);
};

class BfmeSubAED
{
public:
	__declspec(noinline) void bfmeStepAED(int what);
	unsigned char m_bfmeHead[0x1f8];
	Rva0028EF00Clear *m_bfmeClear;
	BfmeFinderAED *m_bfmeFinder;
	unsigned char m_bfmeMiddle[0x14];
	BfmeSubAED *m_bfmeNext;
};

struct BfmeOwnerAED
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubAED *m_bfmeSub;
};

class BfmeThingAED
{
public:
	void bfmeGoAED(void *what);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerAED *m_bfmeOwner;
};

void BfmeThingAED::bfmeGoAED(void *what)
{
	BfmeSubAED *sub = m_bfmeOwner->m_bfmeSub;
	if (sub == 0)
		return;
	sub->bfmeStepAED(4);
	BfmeFinderAED *finder = sub->m_bfmeFinder;
	if (finder == 0)
		return;
	BfmeTargetAED *target = finder->bfmeFindAED();
	if (target == 0)
		return;
	target->bfmeSendAED(0);
}

void BfmeSubAED::bfmeStepAED(int what)
{
	BfmeSubAED *last = this;
	while (last->m_bfmeNext != 0)
		last = last->m_bfmeNext;

	if (last->m_bfmeClear != 0)
		last->m_bfmeClear->clearAt(what);
}
