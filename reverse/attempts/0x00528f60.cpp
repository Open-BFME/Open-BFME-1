// ??0Gen00529110@@QAE@PAVGen00529110Owner@@H@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Gen00529110Owner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual bool bfmeShouldRestore(void) = 0;
	virtual void slot13(void) = 0;
	virtual void bfmeSetVisible(bool visible) = 0;
	virtual void bfmeRestore(void) = 0;
};

class Gen00529110Member28
{
public:
	Gen00529110Member28();
	~Gen00529110Member28();
private:
	unsigned char m_data[0x40];
};

class Gen00529110Element
{
public:
	Gen00529110Element();
	~Gen00529110Element();
private:
	int m_data;
};

class Gen00529110Member10C
{
public:
	Gen00529110Member10C(int value) : m_flag(false)
	{
		m_data[0] = 0;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[5] = value;
		m_data[3] = 0;
		m_data[4] = 0;
	}
	~Gen00529110Member10C();
	int m_data[6];
	bool m_flag;
	unsigned char m_padding[3];
};

class Gen00529110
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	Gen00529110(Gen00529110Owner *owner, int value);
	~Gen00529110();

private:
	Gen00529110Owner *m_owner;
	void *m_firstGame;
	void *m_secondGame;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;
	bool m_visible;
	unsigned char m_unmodelled19[3];
	int m_value1C;
	int m_value20;
	int m_value24;
	Gen00529110Member28 m_member28;
	void *m_first[8];
	Gen00529110Element m_elements[8];
	void *m_second[8];
	void *m_third[8];
	void *m_fourth[8];
	void *m_required;
	Gen00529110Member10C m_member10C;
	void *m_field128;
};

extern Gen00529110 *TheGen00529110;

// ??0Gen00529110@@QAE@PAVGen00529110Owner@@H@Z
Gen00529110::Gen00529110(Gen00529110Owner *owner, int value) :
	m_owner(owner),
	m_firstGame(0),
	m_secondGame(0),
	m_flag10(false),
	m_flag11(false),
	m_flag12(false),
	m_flag13(false),
	m_flag14(false),
	m_flag15(false),
	m_flag16(true),
	m_flag17(true),
	m_visible(false),
	m_value1C(0),
	m_value20(0),
	m_value24(0),
	m_required(0),
	m_member10C(value),
	m_field128(0)
{
	TheGen00529110 = this;

	void **first = reinterpret_cast<void **>((unsigned int)this + 0x68);
	for (int i = 0; i < 8; ++i)
		first[i] = 0;
	void **second = reinterpret_cast<void **>((unsigned int)this + 0xA8);
	for (int j = 0; j < 8; ++j)
		second[j] = 0;
	void **third = reinterpret_cast<void **>((unsigned int)this + 0xC8);
	for (int k = 0; k < 8; ++k)
		third[k] = 0;
	void **fourth = reinterpret_cast<void **>((unsigned int)this + 0xE8);
	for (int n = 0; n < 8; ++n)
		fourth[n] = 0;
}

// Tear down the UI controller after restoring its owner's presentation state.
// ??1Gen00529110@@QAE@XZ
Gen00529110::~Gen00529110()
{
	if (m_visible)
	{
		m_visible = false;
		m_owner->bfmeSetVisible(false);
		if (m_owner->bfmeShouldRestore())
			m_owner->bfmeRestore();
	}
	if (TheGen00529110 == this)
		TheGen00529110 = 0;
}
