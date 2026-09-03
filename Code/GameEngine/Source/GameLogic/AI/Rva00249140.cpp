// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport member mode update at retail 0x00249140.

class BfmeRva9140Member
{
public:
	char m_head[0x74];
	int m_index;
	char m_gap[0x368 - 0x78];
	unsigned char m_flag;

	int getCount(void);
	void setMode(int mode, int value);
	void finish(void);
};

class BfmeRva9140AI
{
public:
	char m_head[0x3ac];
	unsigned char m_active;
};

class BfmeRva9140MemberView
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual BfmeRva9140AI *getAI(void) = 0;
};

class BfmeRva9140Query
{
public:
	void find(BfmeRva9140Member *member);
};

class BfmeRva9140GlobalA
{
public:
	char m_head[0xc];
	int m_value;
};

class BfmeRva9140GlobalBResult
{
public:
	void consume(int value);
};

class BfmeRva9140GlobalB
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused11(void) = 0;
	virtual void unused12(void) = 0;
	virtual BfmeRva9140GlobalBResult *fetch(int value) = 0;
};

class BfmeRva9140GlobalC
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused11(void) = 0;
	virtual void unused12(void) = 0;
	virtual void unused13(void) = 0;
	virtual void unused14(void) = 0;
	virtual void unused15(void) = 0;
	virtual void unused16(void) = 0;
	virtual void unused17(void) = 0;
	virtual void unused18(void) = 0;
	virtual void unused19(void) = 0;
	virtual void unused20(void) = 0;
	virtual void unused21(void) = 0;
	virtual void unused22(void) = 0;
	virtual void unused23(void) = 0;
	virtual void unused24(void) = 0;
	virtual void unused25(void) = 0;
	virtual void unused26(void) = 0;
	virtual void unused27(void) = 0;
	virtual void unused28(void) = 0;
	virtual void unused29(void) = 0;
	virtual void unused30(void) = 0;
	virtual void unused31(void) = 0;
	virtual void unused32(void) = 0;
	virtual void unused33(void) = 0;
	virtual void unused34(void) = 0;
	virtual void unused35(void) = 0;
	virtual void unused36(void) = 0;
	virtual void unused37(void) = 0;
	virtual void unused38(void) = 0;
	virtual void unused39(void) = 0;
	virtual void unused40(void) = 0;
	virtual void unused41(void) = 0;
	virtual void unused42(void) = 0;
	virtual void unused43(void) = 0;
	virtual void unused44(void) = 0;
	virtual void unused45(void) = 0;
	virtual void unused46(void) = 0;
	virtual void unused47(void) = 0;
	virtual void unused48(void) = 0;
	virtual void unused49(void) = 0;
	virtual void unused50(void) = 0;
	virtual void unused51(void) = 0;
	virtual void unused52(void) = 0;
	virtual void unused53(void) = 0;
	virtual void unused54(void) = 0;
	virtual void unused55(void) = 0;
	virtual void unused56(void) = 0;
	virtual void notify(BfmeRva9140AI *ai) = 0;
};

extern BfmeRva9140GlobalA *g_bfmeRva9140GlobalA;
extern BfmeRva9140GlobalB *g_bfmeRva9140GlobalB;
extern BfmeRva9140GlobalC *g_bfmeRva9140GlobalC;

class Rva00249140
{
public:
	void update(BfmeRva9140Member *member);
};

void Rva00249140::update(BfmeRva9140Member *member)
{
	((BfmeRva9140Query *)((char *)this + 0x20))->find(member);
	BfmeRva9140AI *ai =
		((BfmeRva9140MemberView *)member)->getAI();
	if (ai != 0 && ai->m_active != 0)
	{
		int expected = g_bfmeRva9140GlobalA->m_value;
		int count = member->getCount();
		if (count == expected)
		{
			BfmeRva9140GlobalBResult *value =
				g_bfmeRva9140GlobalB->fetch(0x3ec);
			value->consume(member->m_index);
			g_bfmeRva9140GlobalC->notify(ai);
		}
		member->setMode(3, 1);
	}
	if (member->m_flag)
		member->finish();
}
