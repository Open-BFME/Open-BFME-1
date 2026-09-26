class BfmeResCPE
{
public:
	virtual void bfmeSpareCPE0();
	virtual void bfmeSpareCPE1();
	virtual void bfmeSpareCPE2();
	virtual void bfmeSpareCPE3();
	virtual void bfmeSpareCPE4();
	virtual void bfmeSpareCPE5();
	virtual void bfmeSpareCPE6();
	virtual void bfmeSpareCPE7();
	virtual void bfmeSpareCPE8();
	virtual void bfmeSpareCPE9();
	virtual void bfmeSpareCPE10();
	virtual void bfmeSpareCPE11();
	virtual void bfmeSpareCPE12();
	virtual void bfmeSpareCPE13();
	virtual void bfmeSpareCPE14();
	virtual void bfmeSpareCPE15();
	virtual void bfmeSpareCPE16();
	virtual void bfmeSpareCPE17();
	virtual void bfmeSpareCPE18();
	virtual void bfmeSpareCPE19();
	virtual void bfmeSpareCPE20();
	virtual void bfmeSpareCPE21();
	virtual void bfmeSpareCPE22();
	virtual void bfmeSpareCPE23();
	virtual void bfmeSpareCPE24();
	virtual void bfmeSpareCPE25();
	virtual void bfmeSpareCPE26();
	virtual void bfmeSpareCPE27();
	virtual void bfmeSpareCPE28();
	virtual void bfmeSpareCPE29();
	virtual void bfmeSpareCPE30();
	virtual void bfmeSpareCPE31();
	virtual void bfmeSpareCPE32();
	virtual void bfmeSpareCPE33();
	virtual void bfmeSpareCPE34();
	virtual void bfmeSpareCPE35();
	virtual void bfmeSpareCPE36();
	virtual void bfmeSpareCPE37();
	virtual void bfmeSpareCPE38();
	virtual void bfmeSpareCPE39();
	virtual void bfmeSpareCPE40();
	virtual void bfmeSpareCPE41();
	virtual void bfmeSpareCPE42();
	virtual void bfmeSpareCPE43();
	virtual void bfmeSpareCPE44();
	virtual void bfmeSpareCPE45();
	virtual void bfmeSpareCPE46();
	virtual void bfmeSpareCPE47();
	virtual void bfmeSpareCPE48();
	virtual void bfmeSpareCPE49();
	virtual void bfmeSpareCPE50();
	virtual void bfmeSpareCPE51();
	virtual void bfmeSpareCPE52();
	virtual void bfmeSpareCPE53();
	virtual void bfmeSpareCPE54();
	virtual bool bfmeAskCPE();
};

class BfmeSubCPE
{
public:
	virtual void bfmeSpareCPEb0();
	virtual void bfmeSpareCPEb1();
	virtual void bfmeSpareCPEb2();
	virtual void bfmeSpareCPEb3();
	virtual void bfmeSpareCPEb4();
	virtual void bfmeSpareCPEb5();
	virtual void bfmeSpareCPEb6();
	virtual void bfmeSpareCPEb7();
	virtual void bfmeSpareCPEb8();
	virtual void bfmeSpareCPEb9();
	virtual void bfmeSpareCPEb10();
	virtual void bfmeSpareCPEb11();
	virtual void bfmeSpareCPEb12();
	virtual void bfmeSpareCPEb13();
	virtual void bfmeSpareCPEb14();
	virtual void bfmeSpareCPEb15();
	virtual void bfmeSpareCPEb16();
	virtual void bfmeSpareCPEb17();
	virtual void bfmeSpareCPEb18();
	virtual void bfmeSpareCPEb19();
	virtual void bfmeSpareCPEb20();
	virtual void bfmeSpareCPEb21();
	virtual void bfmeSpareCPEb22();
	virtual void bfmeSpareCPEb23();
	virtual void bfmeSpareCPEb24();
	virtual void bfmeSpareCPEb25();
	virtual BfmeResCPE *bfmeFindCPE();
};

struct BfmeMidCPE
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubCPE *m_bfmeSub;
};

struct BfmeOwnerCPE
{
	unsigned char m_bfmeHead[0x214];
	BfmeMidCPE *m_bfmeMid;
};

class BfmeThingCPE
{
public:
	bool bfmeGoCPE();
	unsigned char m_bfmeHead[8];
	BfmeOwnerCPE *m_bfmeOwner;
};

bool BfmeThingCPE::bfmeGoCPE()
{
	BfmeOwnerCPE *o = m_bfmeOwner;
	if (o == 0)
		return false;
	BfmeMidCPE *mid = o->m_bfmeMid;
	if (mid == 0)
		return false;
	BfmeSubCPE *sub = mid->m_bfmeSub;
	if (sub == 0)
		return false;
	BfmeResCPE *r = sub->bfmeFindCPE();
	if (r == 0)
		return false;
	return r->bfmeAskCPE();
}
