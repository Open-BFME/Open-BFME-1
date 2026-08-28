class BfmeSinkSB
{
public:
	virtual void bfmeSpareSB0();
	virtual void bfmeSpareSB1();
	virtual void bfmeSpareSB2();
	virtual void bfmeSpareSB3();
	virtual void bfmeSpareSB4();
	virtual void bfmeSpareSB5();
	virtual void bfmeSpareSB6();
	virtual void bfmeSpareSB7();
	virtual void bfmeSpareSB8();
	virtual void bfmeSpareSB9();
	virtual void bfmeSpareSB10();
	virtual void bfmeSpareSB11();
	virtual void bfmeSpareSB12();
	virtual void bfmeSpareSB13();
	virtual void bfmeSpareSB14();
	virtual void bfmeSpareSB15();
	virtual void bfmeSpareSB16();
	virtual void bfmeSpareSB17();
	virtual void bfmeSpareSB18();
	virtual void bfmeSpareSB19();
	virtual void bfmeSpareSB20();
	virtual void bfmeSpareSB21();
	virtual void bfmeSpareSB22();
	virtual void bfmeSpareSB23();
	virtual void bfmeSpareSB24();
	virtual void bfmeSpareSB25();
	virtual void bfmeSpareSB26();
	virtual void bfmeSpareSB27();
	virtual void bfmeSpareSB28();
	virtual void bfmeSpareSB29();
	virtual void bfmeSpareSB30();
	virtual void bfmeSpareSB31();
	virtual void bfmeSpareSB32();
	virtual void bfmeSpareSB33();
	virtual void bfmeSpareSB34();
	virtual void bfmeSpareSB35();
	virtual void bfmeSpareSB36();
	virtual void bfmeSpareSB37();
	virtual void bfmeSpareSB38();
	virtual void bfmeSpareSB39();
	virtual void bfmeSpareSB40();
	virtual void bfmeSpareSB41();
	virtual void bfmeSpareSB42();
	virtual void bfmeSpareSB43();
	virtual void bfmeSpareSB44();
	virtual void bfmeSpareSB45();
	virtual void bfmeSpareSB46();
	virtual void bfmeSpareSB47();
	virtual void bfmeSpareSB48();
	virtual void bfmeSpareSB49();
	virtual void bfmeSpareSB50();
	virtual void bfmeSpareSB51();
	virtual void bfmeSpareSB52();
	virtual void bfmeSpareSB53();
	virtual void bfmeSpareSB54();
	virtual void bfmeSpareSB55();
	virtual void bfmeSpareSB56();
	virtual void bfmeSpareSB57();
	virtual void bfmeSpareSB58();
	virtual void bfmeSpareSB59();
	virtual void bfmeSpareSB60();
	virtual void bfmeSpareSB61();
	virtual void bfmeSpareSB62();
	virtual void bfmeSpareSB63();
	virtual void bfmeSpareSB64();
	virtual void bfmeSpareSB65();
	virtual void bfmeSpareSB66();
	virtual void bfmeSpareSB67();
	virtual void bfmeSpareSB68();
	virtual void bfmeSpareSB69();
	virtual void bfmeSpareSB70();
	virtual void bfmeSpareSB71();
	virtual void bfmeSpareSB72();
	virtual void bfmeSpareSB73();
	virtual void bfmeSpareSB74();
	virtual void bfmeSpareSB75();
	virtual void bfmeSpareSB76();
	virtual void bfmeSpareSB77();
	virtual void bfmeSpareSB78();
	virtual void bfmeSpareSB79();
	virtual void bfmeSpareSB80();
	virtual void bfmeSpareSB81();
	virtual void bfmeSpareSB82();
	virtual void bfmeSpareSB83();
	virtual void bfmeSpareSB84();
	virtual void bfmeSpareSB85();
	virtual void bfmeSpareSB86();
	virtual void bfmeSpareSB87();
	virtual void bfmeSpareSB88();
	virtual void bfmeSpareSB89();
	virtual void bfmeSpareSB90();
	virtual void bfmeSpareSB91();
	virtual void bfmeNoteSB();
};

extern BfmeSinkSB *g_bfmeSinkSB;

class BfmeThingSB
{
public:
	void bfmeSetSB(int mode);
	unsigned char m_bfmeHead[0x16cc];
	int m_bfmeMode;
};

void BfmeThingSB::bfmeSetSB(int mode)
{
	if (mode < 0)
		return;
	if (mode >= 2)
		return;
	if (m_bfmeMode == mode)
		return;
	m_bfmeMode = mode;
	BfmeSinkSB *sink = g_bfmeSinkSB;
	if (sink != 0)
		sink->bfmeNoteSB();
}
