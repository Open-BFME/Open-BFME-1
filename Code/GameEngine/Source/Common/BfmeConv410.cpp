struct BfmeStateAMA
{
	unsigned char m_bfmeHead[0x10];
	int m_bfmeKind;
	unsigned char m_bfmeGap[8];
	int m_bfmeCount;
	bool m_bfmeOn;
};

class BfmeThingAMA
{
public:
	virtual void bfmeSpareAMA0();
	virtual void bfmeSpareAMA1();
	virtual void bfmeSpareAMA2();
	virtual void bfmeSpareAMA3();
	virtual void bfmeSpareAMA4();
	virtual void bfmeSpareAMA5();
	virtual void bfmeSpareAMA6();
	virtual void bfmeSpareAMA7();
	virtual void bfmeSpareAMA8();
	virtual void bfmeSpareAMA9();
	virtual void bfmeSpareAMA10();
	virtual void bfmeSpareAMA11();
	virtual void bfmeSpareAMA12();
	virtual void bfmeSpareAMA13();
	virtual void bfmeSpareAMA14();
	virtual void bfmeSpareAMA15();
	virtual void bfmeSpareAMA16();
	virtual void bfmeSpareAMA17();
	virtual void bfmeSpareAMA18();
	virtual void bfmeSpareAMA19();
	virtual void bfmeSpareAMA20();
	virtual void bfmeSpareAMA21();
	virtual void bfmeSpareAMA22();
	virtual void bfmeSpareAMA23();
	virtual void bfmeSpareAMA24();
	virtual void bfmeSpareAMA25();
	virtual void bfmeSpareAMA26();
	virtual void bfmeSpareAMA27();
	virtual void bfmeSpareAMA28();
	virtual void bfmeSpareAMA29();
	virtual void bfmeSpareAMA30();
	virtual void bfmeSpareAMA31();
	virtual void bfmeSpareAMA32();
	virtual void bfmeSpareAMA33();
	virtual void bfmeSpareAMA34();
	virtual void bfmeSpareAMA35();
	virtual void bfmeSendAMA(void *one, int what);
	void bfmeGoAMA(void *one, void *two, BfmeStateAMA *st);
};

void BfmeThingAMA::bfmeGoAMA(void *one, void *two, BfmeStateAMA *st)
{
	if (one != 0 && two != 0 && st != 0)
	{
		int kind = st->m_bfmeKind;
		if (kind != 0xe && kind != 8)
		{
			st->m_bfmeCount = 0;
			st->m_bfmeOn = false;
			return;
		}
		if (st->m_bfmeOn == 1)
			bfmeSendAMA(one, 0);
	}
}
