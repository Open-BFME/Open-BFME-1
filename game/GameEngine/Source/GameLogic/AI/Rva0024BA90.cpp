// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport member notification path at retail 0x0024BA90.

class BfmeRvaBA90Member
{
public:
	char m_head[0x74];
	int m_index;

	int getCount(void);
	void setMode(int mode, int value);
	bool check(int value);
	void set(int value);
};

class BfmeRvaBA90AI
{
public:
	char m_head[0x3ac];
	unsigned char m_active;
};

class BfmeRvaBA90Result
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
	virtual BfmeRvaBA90AI *getAI(void) = 0;
};

class BfmeRvaBA90MemberView
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
	virtual BfmeRvaBA90AI *getAI(void) = 0;
};

class BfmeRvaBA90Query
{
public:
	void find(BfmeRvaBA90Member *member);
};

class BfmeRvaBA90GlobalA
{
public:
	char m_head[0xc];
	int m_value;
};

class BfmeRvaBA90GlobalBResult
{
public:
	void consume(int value);
};

class BfmeRvaBA90GlobalB
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
	virtual BfmeRvaBA90GlobalBResult *fetch(int value) = 0;
};

class BfmeRvaBA90GlobalC
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
	virtual void notify(BfmeRvaBA90AI *ai) = 0;
};

class BfmeRvaBA90Manager
{
public:
	void notify(void *value);
};

extern BfmeRvaBA90GlobalA *g_bfmeRvaBA90GlobalA;
extern BfmeRvaBA90GlobalB *g_bfmeRvaBA90GlobalB;
extern BfmeRvaBA90GlobalC *g_bfmeRvaBA90GlobalC;
extern BfmeRvaBA90Manager *g_bfmeRvaBA90Manager;

class Rva0024BA90
{
public:
	void update(BfmeRvaBA90Member *member);
};

void Rva0024BA90::update(BfmeRvaBA90Member *member)
{
	((BfmeRvaBA90Query *)((char *)this + 0x20))->find(member);
	BfmeRvaBA90AI *ai =
		((BfmeRvaBA90MemberView *)member)->getAI();
	if (ai != 0 && ai->m_active != 0)
	{
		int expected = g_bfmeRvaBA90GlobalA->m_value;
		int count = member->getCount();
		if (count == expected)
		{
			BfmeRvaBA90GlobalBResult *value =
				g_bfmeRvaBA90GlobalB->fetch(0x3ec);
			value->consume(member->m_index);
			g_bfmeRvaBA90GlobalC->notify(ai);
		}
		member->setMode(3, 1);
	}
	if (member->check(0x14))
		member->set(0x14);
	g_bfmeRvaBA90Manager->notify((char *)member + 0x6c);
}
