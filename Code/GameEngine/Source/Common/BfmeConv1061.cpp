// Open-BFME5 conversions.

class BfmeSubA1061
{
public:
	virtual void bfmeSlot1061S_0(void);
	virtual void bfmeSlot1061S_1(void);
};

class BfmeG1061
{
public:
	virtual void bfmeSlot1061G_0(void);
	virtual void bfmeSlot1061G_1(void);
	virtual void bfmeSlot1061G_2(void);
	virtual void bfmeSlot1061G_3(void);
	virtual void bfmeSlot1061G_4(void);
	virtual void bfmeSlot1061G_5(void);
	virtual void bfmeSlot1061G_6(void);
	virtual void bfmeSlot1061G_7(void);
	virtual void bfmeSlot1061G_8(void);
	virtual void bfmeSlot1061G_9(void);
	virtual void bfmeSlot1061G_10(void);
	virtual void bfmeSlot1061G_11(void);
	virtual void bfmeSlot1061G_12(void);
	virtual void bfmeSlot1061G_13(void);
};

extern BfmeG1061 *g_bfmeG1061;

class BfmeT1061
{
public:
	void bfmeTail1061(void);
};

extern BfmeT1061 *g_bfmeT1061;

class BfmeA1061
{
public:
	void bfmeGo1061A(void);
	char m_bfmePad[0x25c];
	BfmeSubA1061 m_bfmeSub;
};

void BfmeA1061::bfmeGo1061A(void)
{
	m_bfmeSub.bfmeSlot1061S_1();
	if (g_bfmeG1061)
		g_bfmeG1061->bfmeSlot1061G_13();
	g_bfmeT1061->bfmeTail1061();
}

class BfmeS1061
{
public:
	int bfmeAdd1061(char *s);
};

extern BfmeS1061 *g_bfmeS1061;
extern char g_bfmeLit1061[];

class BfmeB1061
{
public:
	void bfmeGo1061B(void);
	void bfmeInit1061(void);
	char m_bfmePad[0x58];
	int m_bfme58;
	char *m_bfme5c;
};

void BfmeB1061::bfmeGo1061B(void)
{
	bfmeInit1061();
	char *s;

	if (m_bfme5c)
		s = m_bfme5c + 8;
	else
		s = g_bfmeLit1061;
	m_bfme58 = g_bfmeS1061->bfmeAdd1061(s);
}

