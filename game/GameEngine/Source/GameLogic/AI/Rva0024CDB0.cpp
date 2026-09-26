// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde contain member state transition at retail 0x0024CDB0.

class BfmeRvaCDB0Member
{
public:
	char m_head[0x12c];
	unsigned int m_status;

	bool check(int value);
	void set(int value);
	void notify(void);
};

class BfmeRvaCDB0Result
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
	virtual void doTransition(BfmeRvaCDB0Member *member) = 0;
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
	virtual bool ready(void) = 0;
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
	virtual bool canContinue(void) = 0;
};

class BfmeRvaCDB0Owner
{
public:
	BfmeRvaCDB0Result *find(BfmeRvaCDB0Member *member);
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
	virtual void notify(void) = 0;
};

class BfmeRvaCDB0Callback
{
public:
	void finish(BfmeRvaCDB0Member *member, int value);
};

class Rva0024CDB0 : public BfmeRvaCDB0Owner
{
public:
	void update(BfmeRvaCDB0Member *member);
};

void Rva0024CDB0::update(BfmeRvaCDB0Member *member)
{
	BfmeRvaCDB0Result *result = find(member);
	if (result == 0)
		return;
	if (!result->ready())
		return;
	if (result->canContinue() == true)
		return;

	if (member->check(0x14))
	{
		member->set(0x14);
		unsigned char status = (unsigned char)member->m_status;
		unsigned int mask = 0x80;
		if ((status & mask) == 0)
		{
			member->m_status |= mask;
			member->notify();
		}
	}

	result->doTransition(member);
	notify();
	((BfmeRvaCDB0Callback *)((char *)this + 0x20))->finish(member, 0);
}
