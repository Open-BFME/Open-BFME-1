// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde contain transition helper, retail 0x0024BBD0.

class BfmeRvaBBD0AI
{
public:
	virtual void unused0(void) = 0;
	virtual void unused1(void) = 0;
	virtual void unused2(void) = 0;
	virtual void unused3(void) = 0;
	virtual void setState(int state) = 0;
	virtual void unused5(void) = 0;
	virtual void unused6(void) = 0;
	virtual void unused7(void) = 0;
	virtual void unused8(void) = 0;
	virtual void unused9(void) = 0;
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
	virtual void unused57(void) = 0;
	virtual void unused58(void) = 0;
	virtual void unused59(void) = 0;
	virtual void unused60(void) = 0;
	virtual void unused61(void) = 0;
	virtual void unused62(void) = 0;
	virtual void unused63(void) = 0;
	virtual void unused64(void) = 0;
	virtual void notify(void) = 0;
};

class BfmeRvaBBD0Contain
{
public:
	virtual void unused0(void) = 0;
	virtual void unused1(void) = 0;
	virtual void unused2(void) = 0;
	virtual void unused3(void) = 0;
	virtual void unused4(void) = 0;
	virtual void unused5(void) = 0;
	virtual void unused6(void) = 0;
	virtual void unused7(void) = 0;
	virtual void unused8(void) = 0;
	virtual void unused9(void) = 0;
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
	virtual BfmeRvaBBD0AI *getAI(void) = 0;
};

class BfmeRvaBBD0Object
{
public:
	char m_head[0x1fc];
	BfmeRvaBBD0Contain *m_contain;
};

class BfmeRvaBBD0Owner
{
public:
	void onContaining(BfmeRvaBBD0Object *object);
	void onRemoving(BfmeRvaBBD0Object *object);
};

class Rva0024BBD0
{
public:
	void transition(BfmeRvaBBD0Object *object, int unused);
};

void Rva0024BBD0::transition(BfmeRvaBBD0Object *object, int unused)
{
	if (object)
	{
		BfmeRvaBBD0Contain *contain = object->m_contain;
		if (contain)
		{
			BfmeRvaBBD0AI *ai = contain->getAI();
			if (ai)
			{
				((BfmeRvaBBD0Owner *)((char *)this - 0x20))->onContaining(object);
				ai->notify();
				ai->setState(1);
				return;
			}
		}
	}
	((BfmeRvaBBD0Owner *)((char *)this - 0x20))->onRemoving(object);
}
