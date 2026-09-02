// cl: /DNDEBUG /MD /EHsc

class BfmeStateReceiver
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual void slot52(void);
	virtual void slot53(void);
	virtual void slot54(void);
	virtual void slot55(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual void slot65(void);
	virtual void slot66(void);
	virtual void slot67(void);
	virtual void slot68(void);
	virtual void slot69(void);
	virtual void slot70(void);
	virtual void slot71(void);
	virtual void slot72(void);
	virtual void slot73(void);
	virtual void slot74(void);
	virtual void slot75(void);
	virtual void slot76(void);
	virtual void slot77(void);
	virtual void slot78(void);
	virtual void slot79(void);
	virtual void slot80(void);
	virtual void slot81(void);
	virtual void slot82(void);
	virtual void slot83(void);
	virtual void slot84(void);
	virtual void slot85(void);
	virtual void slot86(void);
	virtual void slot87(void);
	virtual void slot88(void);
	virtual void slot89(void);
	virtual void slot90(void);
	virtual void slot91(void);
	virtual void slot92(void);
	virtual void slot93(void);
	virtual void slot94(void);
	virtual void slot95(void);
	virtual void slot96(void);
	virtual void slot97(void);
	virtual void slot98(void);
	virtual void slot99(void);
	virtual void stop(int one);
};

class BfmeThingDY
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void bfmeDoDY(void);

	void bfmeAdvanceDY(void);
	void bfmeSetDY(int value, int one);
	void bfmeSetRectDY(int x, int y, int z, int w, int one);

private:
	unsigned char m_afterVtable[4];
	BfmeStateReceiver *m_receiver;
	unsigned char m_beforeState[0x18];
	int m_state;
	unsigned char m_beforeValue[4];
	int m_value;
	int m_zero;
	int m_x;
	int m_y;
	int m_z;
	int m_w;
	int m_mode;
	int m_active;
};

void BfmeThingDY::bfmeAdvanceDY(void)
{
	if (!m_active)
	{
		if (m_receiver && (m_state == 2 || m_state == 3))
		{
			m_receiver->stop(1);
		}

		m_state = 0;
		return;
	}

	if (m_active != 1)
		return;

	if (m_state == 1)
	{
		m_state = 2;
		m_mode = 2;
		m_active = 1;
		m_zero = 0;
		bfmeDoDY();
		return;
	}

	if (m_state == 2)
	{
		bfmeSetDY(m_value, 1);
		return;
	}

	if (m_state == 3)
		bfmeSetRectDY(m_x, m_y, m_z, m_w, 1);
}
