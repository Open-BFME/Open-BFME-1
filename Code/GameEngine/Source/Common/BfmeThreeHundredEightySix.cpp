class BfmeThingAFA;

class BfmeTargetAFA
{
public:
	virtual void bfmeSpareAFAa0();
	virtual void bfmeSpareAFAa1();
	virtual void bfmeSpareAFAa2();
	virtual void bfmeSpareAFAa3();
	virtual void bfmeSpareAFAa4();
	virtual void bfmeSpareAFAa5();
	virtual void bfmeSpareAFAa6();
	virtual void bfmeSpareAFAa7();
	virtual void bfmeSpareAFAa8();
	virtual void bfmeSpareAFAa9();
	virtual void bfmeSpareAFAa10();
	virtual void bfmeSpareAFAa11();
	virtual void bfmeSpareAFAa12();
	virtual void bfmeSpareAFAa13();
	virtual void bfmeSpareAFAa14();
	virtual void bfmeSpareAFAa15();
	virtual void bfmeSpareAFAa16();
	virtual void bfmeSpareAFAa17();
	virtual void bfmeSpareAFAa18();
	virtual void bfmeSpareAFAa19();
	virtual void bfmeSpareAFAa20();
	virtual void bfmeSpareAFAa21();
	virtual void bfmeSpareAFAa22();
	virtual void bfmeSpareAFAa23();
	virtual void bfmeSpareAFAa24();
	virtual void bfmeSpareAFAa25();
	virtual void bfmeSpareAFAa26();
	virtual void bfmeSpareAFAa27();
	virtual void bfmeSpareAFAa28();
	virtual void bfmeSpareAFAa29();
	virtual void bfmeSpareAFAa30();
	virtual void bfmeSpareAFAa31();
	virtual void bfmeSpareAFAa32();
	virtual void bfmeSpareAFAa33();
	virtual void bfmeSpareAFAa34();
	virtual void bfmeSpareAFAa35();
	virtual void bfmeSpareAFAa36();
	virtual void bfmeSpareAFAa37();
	virtual void bfmeSpareAFAa38();
	virtual void bfmeSpareAFAa39();
	virtual void bfmeSpareAFAa40();
	virtual void bfmeSpareAFAa41();
	virtual void bfmeSpareAFAa42();
	virtual void bfmeSpareAFAa43();
	virtual void bfmeSpareAFAa44();
	virtual void bfmeSpareAFAa45();
	virtual void bfmeSpareAFAa46();
	virtual void bfmeSpareAFAa47();
	virtual void bfmeSpareAFAa48();
	virtual void bfmeSpareAFAa49();
	virtual void bfmeSpareAFAa50();
	virtual void bfmeSpareAFAa51();
	virtual void bfmeSpareAFAa52();
	virtual void bfmeSpareAFAa53();
	virtual void bfmeSpareAFAa54();
	virtual void bfmeSpareAFAa55();
	virtual void bfmeSpareAFAa56();
	virtual void bfmeSpareAFAa57();
	virtual void bfmeSpareAFAa58();
	virtual void bfmeSpareAFAa59();
	virtual void bfmeSpareAFAa60();
	virtual void bfmeSpareAFAa61();
	virtual void bfmeSpareAFAa62();
	virtual void bfmeSpareAFAa63();
	virtual void bfmeSpareAFAa64();
	virtual void bfmeSpareAFAa65();
	virtual void bfmeSpareAFAa66();
	virtual void bfmeSpareAFAa67();
	virtual void bfmeSpareAFAa68();
	virtual void bfmeSpareAFAa69();
	virtual void bfmeSpareAFAa70();
	virtual void bfmeSpareAFAa71();
	virtual bool bfmeTestAFA(BfmeThingAFA *who, void *what);
};

class BfmeFinderAFA
{
public:
	virtual void bfmeSpareAFAb0();
	virtual void bfmeSpareAFAb1();
	virtual void bfmeSpareAFAb2();
	virtual void bfmeSpareAFAb3();
	virtual void bfmeSpareAFAb4();
	virtual void bfmeSpareAFAb5();
	virtual void bfmeSpareAFAb6();
	virtual void bfmeSpareAFAb7();
	virtual void bfmeSpareAFAb8();
	virtual void bfmeSpareAFAb9();
	virtual void bfmeSpareAFAb10();
	virtual void bfmeSpareAFAb11();
	virtual void bfmeSpareAFAb12();
	virtual void bfmeSpareAFAb13();
	virtual void bfmeSpareAFAb14();
	virtual void bfmeSpareAFAb15();
	virtual void bfmeSpareAFAb16();
	virtual void bfmeSpareAFAb17();
	virtual void bfmeSpareAFAb18();
	virtual void bfmeSpareAFAb19();
	virtual void bfmeSpareAFAb20();
	virtual void bfmeSpareAFAb21();
	virtual void bfmeSpareAFAb22();
	virtual void bfmeSpareAFAb23();
	virtual void bfmeSpareAFAb24();
	virtual void bfmeSpareAFAb25();
	virtual BfmeTargetAFA *bfmeFindAFA();
};

struct BfmeOwnerAFA
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeFinderAFA *m_bfmeFinder;
};

class BfmeThingAFA
{
public:
	bool bfmeAskAFA(void *what);
	unsigned char m_bfmeHead[0x214];
	BfmeOwnerAFA *m_bfmeOwner;
};

bool BfmeThingAFA::bfmeAskAFA(void *what)
{
	BfmeOwnerAFA *owner = m_bfmeOwner;
	if (owner != 0)
	{
		BfmeFinderAFA *finder = owner->m_bfmeFinder;
		if (finder != 0)
		{
			BfmeTargetAFA *target = finder->bfmeFindAFA();
			if (target != 0)
			{
				if (!target->bfmeTestAFA(this, what))
					return false;
			}
		}
	}
	return true;
}
