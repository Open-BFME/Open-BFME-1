// cl: /DNDEBUG /MD /EHs-c-

struct BfmeSeedPair_001FE050
{
	unsigned char first;
	unsigned char second;
};

class BfmeSeedTarget
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
	virtual void bfmeSeed(BfmeSeedPair_001FE050 *pair);
	virtual void slot0b(void);
	virtual void slot0c(void);
	virtual void slot0d(void);
	virtual void slot0e(void);
	virtual void slot0f(void);
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
	virtual void slot1a(void);
	virtual void takeAt6c(void *item);
	virtual void slot1c(void);
	virtual void takeAt74(void *item);
	virtual void takeAt78(void *item);
	virtual void slot1f(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void takeAt8c(void *item);
};

class BfmeAudioClientUpdate_001FE050
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual void slot6c(void);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual void slot78(void);
	virtual void slot7c(void);
	virtual void slot80(void);
	virtual void slot84(void);
	virtual void slot88(void);
	virtual void slot8c(void);
	virtual void slot90(void);
	virtual void slot94(void);
	virtual void slot98(void);
	virtual void slot9c(void);
	virtual void slota0(void);
	virtual void slota4(void);
	virtual void slota8(void);
	virtual void slotac(void);
	virtual void slotb0(void);
	virtual void slotb4(void);
	virtual void slotb8(void);
	virtual void slotbc(void);
	virtual void slotc0(void);
	virtual void slotc4(void);
	virtual void slotc8(void);
	virtual void slotcc(void);
	virtual void slotd0(void);
	virtual void slotd4(void);
	virtual void slotd8(void);
	virtual void slotdc(void);
	virtual void slote0(void);
	virtual void slote4(void);
	virtual void slote8(void);
	virtual void slotec(void);
	virtual void slotf0(void);
	virtual void slotf4(void);
	virtual void slotf8(void);
	virtual void slotfc(void);
	virtual void slot100(void);
	virtual void slot104(void);
	virtual void slot108(void);
	virtual void slot10c(void);
	virtual void slot110(void);
	virtual void slot114(void);
	virtual void slot118(void);
	virtual void slot11c(void);
	virtual void slot120(void);
	virtual void slot124(void);
	virtual void slot128(void);
	virtual void slot12c(void);
	virtual void slot130(void);
	virtual void slot134(void);
	virtual void slot138(void);
	virtual void slot13c(void);
	virtual void slot140(void);
	virtual void slot144(void);
	virtual void takeItem148(BfmeSeedTarget *target, void *item);
};

extern BfmeAudioClientUpdate_001FE050 *g_Va012ED668;

class Gen_001FE050;

class Gen_001ED0C0
{
	friend class Gen_001FE050;

	private:
	void bfmeAccept(BfmeSeedTarget *target);

private:
	char m_bfmeBase[0x24];
};

class Gen_001FE050 : public Gen_001ED0C0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmeItem24;
	char m_bfmePad0[0x3];
	char m_bfmeItem28;
	char m_bfmePad1[0x3];
	char m_bfmeItem2c;
	char m_bfmePad2[0x3];
	char m_bfmeItem30;
	char m_bfmeItem31;
	char m_bfmeItem32;
	char m_bfmeItem33;
	char m_bfmeItem34;
	char m_bfmeItem35;
	char m_bfmeItem36;
	char m_bfmePad3;
	char m_bfmeItem38;
};

void Gen_001FE050::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair_001FE050 pair;

	pair.first = 1;
	pair.second = 4;

	target->bfmeSeed(&pair);
	bfmeAccept(target);
	target->takeAt8c(&m_bfmeItem30);
	target->takeAt6c(&m_bfmeItem28);
	target->takeAt8c(&m_bfmeItem31);
	target->takeAt8c(&m_bfmeItem32);
	target->takeAt8c(&m_bfmeItem33);
	g_Va012ED668->takeItem148(target, &m_bfmeItem24);
	if (pair.second >= 2)
	{
		target->takeAt74(&m_bfmeItem2c);
		target->takeAt8c(&m_bfmeItem34);
	}
	if (pair.second >= 3)
	{
		target->takeAt8c(&m_bfmeItem35);
		target->takeAt8c(&m_bfmeItem36);
	}
	if (pair.second >= 4)
		target->takeAt78(&m_bfmeItem38);
}
