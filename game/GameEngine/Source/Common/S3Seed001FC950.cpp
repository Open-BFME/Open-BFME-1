// cl: /DNDEBUG /MD /O2
// Gen_001FC950 is the S3 seeder at retail 0x001FC950.
// The direct thunk at 0x00007E5F reaches this body.  Its seed pair, accept
// helpers, target slots, and TheAudioClientUpdate hand-over identify this
// member as the next body in the S3 seeder family.

struct BfmeSeedPair
{
	unsigned char m_first;
	unsigned char m_second;
};

class BfmeSeedTarget
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
	virtual void takeAt24(void *item, int size);
	virtual void seed(BfmeSeedPair *pair);
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
	virtual void takeAt6c(void *item);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual void takeAt78(void *item);
	virtual void slot7c(void);
	virtual void slot80(void);
	virtual void slot84(void);
	virtual void slot88(void);
	virtual void takeAt8c(void *item);
};

class Rva005A00B0AudioClient
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

extern Rva005A00B0AudioClient *TheAudioClientUpdate;
void bfmeCalcTGC(void *target, int *item);

class Gen_001F61B0
{
	friend class Gen_001FC950;

	private:
	void bfmeAccept(BfmeSeedTarget *target);

	char m_base[0x1c];
	int m_item1c;
	int m_item20;
};

class Gen_001ED0C0
{
	friend class Gen_001FC950;

private:
	void bfmeAccept(BfmeSeedTarget *target);
};

class Gen_001FC950 : public Gen_001F61B0
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	int m_item24;
	int m_item28;
	int m_item2c;
	int m_item30;
	int m_item34;
	int m_item38;
	int m_item3c;
	int m_item40;
	int m_item44;
};

// ?bfmeSeed@Gen_001FC950@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_001FC950::bfmeSeed(BfmeSeedTarget *target)
{
	bfmeAccept(target);

	BfmeSeedPair pair;
	pair.m_first = 1;
	pair.m_second = 3;
	target->seed(&pair);

	if (pair.m_second >= 3)
		((Gen_001ED0C0 *)this)->bfmeAccept(target);

	int item24 = m_item24;
	target->takeAt78(&item24);
	m_item24 = item24;
	int item28 = m_item28;
	target->takeAt78(&item28);
	m_item28 = item28;

	target->takeAt8c(&m_item2c);
	target->takeAt78(&m_item38);
	bfmeCalcTGC(target, &m_item20);
	target->takeAt78(&m_item3c);
	TheAudioClientUpdate->takeItem148(target, &m_item40);
	target->takeAt8c(&m_item44);

	if (pair.m_second >= 2)
	{
		target->takeAt24(&m_item28, 4);
		target->takeAt6c(&m_item30);
		target->takeAt6c(&m_item34);
	}
}
