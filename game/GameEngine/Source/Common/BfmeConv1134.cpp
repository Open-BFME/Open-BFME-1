// Open-BFME5 conversions.

extern "C" char g_bfmeV1134[];

class BfmeBase1134
{
public:
	BfmeBase1134(void) throw();
	char *volatile m_bfme00;
	int m_bfme04;
};

class BfmeA1134 : public BfmeBase1134
{
public:
	BfmeA1134(void);
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile char m_bfme1c;
	char m_bfmePad1d[3];
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
	volatile int m_bfme38;
	volatile int m_bfme3c;
	volatile int m_bfme40;
	volatile int m_bfme44;
	volatile float m_bfme48;
	volatile char m_bfme4c;
	char m_bfmePad4d[3];
	volatile int m_bfme50;
	volatile int m_bfme54;
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
	volatile int m_bfme64;
	volatile int m_bfme68;
	volatile int m_bfme6c;
	volatile int m_bfme70;
	volatile int m_bfme74;
	volatile int m_bfme78;
	volatile int m_bfme7c;
	volatile char m_bfme80;
	volatile char m_bfme81;
	char m_bfmePad82[2];
	volatile int m_bfme84;
	volatile int m_bfme88;
	volatile int m_bfme8c;
	volatile int m_bfme90;
	volatile int m_bfme94;
	volatile int m_bfme98;
	volatile int m_bfme9c;
	volatile int m_bfmea0;
	volatile int m_bfmea4;
	volatile int m_bfmea8;
};

BfmeA1134::BfmeA1134(void)
{
	m_bfme00 = g_bfmeV1134;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme38 = 0;
	m_bfme3c = 0;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme4c = 0;
	m_bfme50 = 0;
	m_bfme60 = 0;
	m_bfme48 = 1.0f;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme6c = 0;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme78 = 0;
	m_bfme7c = 0;
	m_bfme80 = 0;
	m_bfme81 = 0;
	m_bfme84 = 0;
	m_bfme88 = 0;
	m_bfme8c = 0;
	m_bfme90 = 0;
	m_bfme94 = 0;
	m_bfme98 = 0;
	m_bfme9c = 0;
	m_bfmea0 = 0;
	m_bfmea4 = 0;
	m_bfmea8 = 0;
	m_bfme34 = 0;
	m_bfme30 = 0;
	m_bfme2c = 0;
	m_bfme5c = 0;
	m_bfme58 = 0;
	m_bfme54 = 0;
}
