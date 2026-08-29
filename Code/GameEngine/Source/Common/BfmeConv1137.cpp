// Open-BFME5 conversions.

extern "C" char g_bfmeV1137A[];

class BfmeBase1137A
{
public:
	BfmeBase1137A(void) throw();
	char *volatile m_bfme00;
	int m_bfme04;
};

class BfmeA1137 : public BfmeBase1137A
{
public:
	BfmeA1137(void);
	char m_bfmePad[0x60];
	volatile int m_bfme68;
	volatile int m_bfme6c;
	volatile int m_bfme70;
	volatile int m_bfme74;
	volatile int m_bfme78;
	volatile int m_bfme7c;
	volatile int m_bfme80;
	volatile int m_bfme84;
	volatile int m_bfme88;
	volatile int m_bfme8c;
	volatile int m_bfme90;
	volatile int m_bfme94;
	volatile int m_bfme98;
};

BfmeA1137::BfmeA1137(void)
{
	m_bfme68 = 0;
	m_bfme00 = g_bfmeV1137A;
	m_bfme6c = 0;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme78 = 0;
	m_bfme7c = 0;
	m_bfme80 = 0;
	m_bfme84 = 0;
	m_bfme88 = 0;
	m_bfme8c = 0;
	m_bfme90 = 0;
	m_bfme94 = 0;
	m_bfme98 = 0;
}

extern "C" char g_bfmeV1137B[];

class BfmeBase1137B
{
public:
	BfmeBase1137B(void) throw();
	char *volatile m_bfme00;
	int m_bfme04;
};

class BfmeB1137 : public BfmeBase1137B
{
public:
	BfmeB1137(void);
	char m_bfmePad[0x30];
	volatile int m_bfme38;
	volatile int m_bfme3c;
	volatile int m_bfme40;
	volatile int m_bfme44;
	volatile int m_bfme48;
	volatile int m_bfme4c;
	volatile int m_bfme50;
	volatile char m_bfme54;
	char m_bfmePad2[3];
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
	volatile int m_bfme64;
	volatile char m_bfme68;
	volatile char m_bfme69;
	volatile char m_bfme6a;
	char m_bfmePad3[0x75];
	volatile int m_bfmee0;
	volatile int m_bfmee4;
};

BfmeB1137::BfmeB1137(void)
{
	m_bfme38 = 0;
	m_bfme3c = 0;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;
	m_bfme50 = 0;
	m_bfme00 = g_bfmeV1137B;
	m_bfme54 = 1;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme69 = 0;
	m_bfme6a = 0;
	m_bfmee0 = 0;
	m_bfmee4 = 0;
}

extern "C" char g_bfmeV1137C[];

class BfmeBase1137C
{
public:
	BfmeBase1137C(void) throw();
	char *volatile m_bfme00;
	volatile int m_bfme04;
};

class BfmeC1137 : public BfmeBase1137C
{
public:
	BfmeC1137(void);
	char m_bfme08;
	volatile char m_bfme09;
	char m_bfmePad[2];
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
	volatile int m_bfme38;
	volatile int m_bfme3c;
};

BfmeC1137::BfmeC1137(void)
{
	m_bfme00 = g_bfmeV1137C;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = -1;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme2c = 0;
	m_bfme30 = 0;
	m_bfme34 = 0;
	m_bfme38 = 0;
	m_bfme3c = 0;
	m_bfme0c = 0;
	m_bfme04 = 6;
	m_bfme09 = 1;
}
