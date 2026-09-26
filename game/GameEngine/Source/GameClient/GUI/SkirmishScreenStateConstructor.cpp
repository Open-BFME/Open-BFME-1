// Recovered constructor for SkirmishScreenState at retail RVA 0x00528F60.
// This source is intentionally kept separate from the existing destructor
// translation while the owner interface is being identified.

class Gen00529110Owner
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual bool bfmeShouldRestore();
    virtual void slot13();
    virtual void bfmeSetVisible(bool visible);
    virtual void bfmeRestore();
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
	Gen00529110Member10C(int value)
	{
		m_required = 0;
		m_data0 = 0;
		m_data1 = 0;
		m_data2 = 0;
		m_data5 = value;
		m_data3 = 0;
		m_data4 = 0;
		m_flag = false;
	}
	~Gen00529110Member10C();

public:
	volatile int m_required;
	volatile int m_data0;
	volatile int m_data1;
	volatile int m_data2;
	volatile int m_data3;
	volatile int m_data4;
	volatile int m_data5;
	bool m_flag;
    unsigned char m_padding[3];
};

extern "C" void * __cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)

class SkirmishScreenState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();

    SkirmishScreenState(Gen00529110Owner *owner, int value);

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
    unsigned char m_padding19[3];
    int m_value1c;
    int m_value20;
    int m_value24;
    Gen00529110Member28 m_member28;
    void *m_first[8];
    Gen00529110Element m_elements[8];
    void *m_second[8];
    void *m_third[8];
    void *m_fourth[8];
    Gen00529110Member10C m_member10c;
    int m_value128;
};

SkirmishScreenState *TheSkirmishScreenState;

SkirmishScreenState::SkirmishScreenState(Gen00529110Owner *owner, int value)
    : m_owner(owner),
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
      m_value1c(0),
      m_value20(0),
      m_value24(0),
      m_member28(),
      m_member10c(value),
      m_value128(0)
{
    TheSkirmishScreenState = this;

    memset(m_first, 0, sizeof(m_first));
    memset(m_second, 0, sizeof(m_second));
    memset(m_third, 0, sizeof(m_third));
    memset(m_fourth, 0, sizeof(m_fourth));
}
