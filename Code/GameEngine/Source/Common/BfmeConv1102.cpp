// Open-BFME5 conversions.

class BfmeSub1102
{
public:
	virtual void bfmeSlot1102S_0(void);
	virtual void bfmeSlot1102S_1(void);
};

class BfmeG1102
{
public:
	virtual void bfmeSlot1102G_0(void);
	virtual void bfmeSlot1102G_1(void);
	virtual void bfmeSlot1102G_2(void);
	virtual void bfmeSlot1102G_3(void);
	virtual void bfmeSlot1102G_4(void);
	virtual void bfmeSlot1102G_5(void);
	virtual void bfmeSlot1102G_6(void);
	virtual void bfmeSlot1102G_7(void);
	virtual void bfmeSlot1102G_8(void);
	virtual void bfmeSlot1102G_9(void);
	virtual void bfmeSlot1102G_10(void);
	virtual void bfmeSlot1102G_11(void);
	virtual void bfmeSlot1102G_12(void);
	virtual void bfmeSlot1102G_13(void);
};

class BfmeTl1102
{
public:
	void bfmeTail1102(void);
};

extern BfmeG1102 *g_bfmeG1102;
extern BfmeTl1102 *g_bfmeT1102;

class BfmeR1102
{
public:
	void bfmeGo1102B(int a);
	char m_bfmePad[0x25c];
	BfmeSub1102 m_bfmeSub;
	char m_bfmePad1[0x13];
	char m_bfme273;
	char m_bfmePad2[0x134];
	int m_bfme3a8;
};

void BfmeR1102::bfmeGo1102B(int a)
{
	if (m_bfme3a8 == 6) {
		m_bfme273 = 0;
		return;
	}
	m_bfmeSub.bfmeSlot1102S_1();
	if (g_bfmeG1102)
		g_bfmeG1102->bfmeSlot1102G_13();
	g_bfmeT1102->bfmeTail1102();
	m_bfme3a8 = 0;
}
