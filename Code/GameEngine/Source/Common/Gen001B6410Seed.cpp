// cl: /DNDEBUG /MD /EHs-c-

// BFME's Snapshot seeder at 0x001B6410 is the long hand-over form whose
// version pair is materialised inside the !bfmeSkip guard.  The surrounding
// seeders use this same retail Xfer vtable layout and the same two-byte pair.
struct BfmeSeedPair
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeSkip(void);                         // vtable +0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);     // vtable +0x24
	virtual void bfmeSeed(BfmeSeedPair *pair);           // vtable +0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);               // vtable +0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt6C(void *item);               // vtable +0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);               // vtable +0x74
	virtual void bfmeTakeAt78(void *item);               // vtable +0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeTakeAt8C(void *item);               // vtable +0x8C
};

class Gen_001B6410
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x08];
	char m_bfmeItem0;                                    // +0x08
	char m_bfmePad1[0x0B];
	char m_bfmeItem1;                                    // +0x14
	char m_bfmePad2[0x0B];
	char m_bfmeItem2;                                    // +0x20
	char m_bfmePad3[0x03];
	char m_bfmeItem3;                                    // +0x24
	char m_bfmePad4[0x03];
	char m_bfmeItem4;                                    // +0x28
	char m_bfmePad5[0x03];
	char m_bfmeItem5;                                    // +0x2C
	char m_bfmePad6[0x03];
	char m_bfmeItem6;                                    // +0x30
	char m_bfmePad7[0x03];
	char m_bfmeItem7;                                    // +0x34
	char m_bfmePad8[0x03];
	char m_bfmeItem8;                                    // +0x38
	char m_bfmePad9[0x03];
	char m_bfmeItem9;                                    // +0x3C
	char m_bfmePad10[0x03];
	char m_bfmeItem10;                                   // +0x40
	char m_bfmePad11[0x03];
	char m_bfmeItem11;                                   // +0x44
	char m_bfmePad12[0x03];
	char m_bfmeItem12;                                   // +0x48
	char m_bfmePad13[0x03];
	char m_bfmeItem13;                                   // +0x4C
	char m_bfmePad14[0x03];
	char m_bfmeItem14;                                   // +0x50
	char m_bfmePad15[0x03];
	char m_bfmeItem15;                                   // +0x54
	char m_bfmePad16[0x03];
	char m_bfmeItem16;                                   // +0x58
	char m_bfmePad17[0x03];
	char m_bfmeItem17;                                   // +0x5C
	char m_bfmePad18[0x03];
	char m_bfmeItem18;                                   // +0x60
	char m_bfmePad19[0x33];
	char m_bfmeItem19;                                   // +0x94
	char m_bfmeItem20;                                   // +0x95
	char m_bfmeItem21;                                   // +0x96
	char m_bfmePad20[0x01];
	char m_bfmeRaw[0x04];                                // +0x98
	char m_bfmeItem22;                                   // +0x9C
	char m_bfmePad21[0x03];
	char m_bfmeItem23;                                   // +0xA0
};

// ?bfmeSeed@Gen_001B6410@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_001B6410::bfmeSeed(BfmeSeedTarget *target)
{
	if (!target->bfmeSkip())
	{
		BfmeSeedPair pair;
		pair.m_bfmeFirst = 1;
		pair.m_bfmeSecond = 2;

		target->bfmeSeed(&pair);
		target->bfmeTakeAt60(&m_bfmeItem0);
		target->bfmeTakeAt6C(&m_bfmeItem2);
		target->bfmeTakeAt6C(&m_bfmeItem3);
		target->bfmeTakeAt6C(&m_bfmeItem4);
		target->bfmeTakeAt6C(&m_bfmeItem5);
		target->bfmeTakeAt6C(&m_bfmeItem6);
		target->bfmeTakeAt6C(&m_bfmeItem7);
		target->bfmeTakeAt6C(&m_bfmeItem8);
		target->bfmeTakeAt6C(&m_bfmeItem9);
		target->bfmeTakeAt74(&m_bfmeItem10);
		target->bfmeTakeAt6C(&m_bfmeItem11);
		target->bfmeTakeAt6C(&m_bfmeItem12);
		target->bfmeTakeAt6C(&m_bfmeItem13);
		target->bfmeTakeAt6C(&m_bfmeItem14);
		target->bfmeTakeAt6C(&m_bfmeItem15);
		target->bfmeTakeAt8C(&m_bfmeItem19);
		target->bfmeTakeAt6C(&m_bfmeItem22);
		target->bfmeTakeAt6C(&m_bfmeItem23);
		target->bfmeTakeAt60(&m_bfmeItem1);
		target->bfmeTakeAt6C(&m_bfmeItem16);
		target->bfmeTakeAt74(&m_bfmeItem17);
		target->bfmeTakeAt74(&m_bfmeItem18);
		target->bfmeTakeAt8C(&m_bfmeItem20);
		target->bfmeTakeAt24(m_bfmeRaw, 4);
		if (pair.m_bfmeSecond > 1)
			target->bfmeTakeAt8C(&m_bfmeItem21);
	}
}
