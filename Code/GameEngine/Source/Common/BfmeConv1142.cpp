// Open-BFME5 conversions.

extern "C" char g_bfmeV1142A[];
extern "C" char g_bfmeV1142B[];
extern "C" char g_bfmeV1142C[];
extern "C" char g_bfmeV1142D[];
extern "C" void *g_bfmeS1142;

class BfmeBase1142
{
public:
	BfmeBase1142(void) throw();
	char *volatile m_bfme00;
	int m_bfme04;
};

class BfmeA1142 : public BfmeBase1142
{
public:
	BfmeA1142(char a);
	char *volatile m_bfme08;
	char m_bfmePad0[0xbc];
	char *volatile m_bfmec8;
	char *volatile m_bfmecc;
	char m_bfmePad1[0x3004];
	volatile int m_bfme30d4;
	volatile int m_bfme30d8;
	volatile int m_bfme30dc;
	volatile int m_bfme30e0;
	volatile int m_bfme30e4;
	char m_bfmePad2[0x10];
	volatile char m_bfme30f8;
	char m_bfmePad3[0xb];
	volatile char m_bfme3104;
	char m_bfmePad4[3];
	volatile int m_bfme3108;
	volatile int m_bfme310c;
	volatile int m_bfme3110;
	char m_bfmePad5[0x60];
	volatile char m_bfme3174;
	char m_bfmePad6[3];
	volatile int m_bfme3178;
};

BfmeA1142::BfmeA1142(char a)
{
	char v = a;

	m_bfme30d4 = 0;
	m_bfme30d8 = 0;
	m_bfme30dc = 0;
	m_bfme30e0 = 0;
	m_bfme30e4 = 0;
	m_bfme3104 = 0;
	m_bfme00 = g_bfmeV1142A;
	m_bfme08 = g_bfmeV1142B;
	m_bfmec8 = g_bfmeV1142C;
	m_bfmecc = g_bfmeV1142D;
	m_bfme30f8 = v;
	m_bfme3108 = 0;
	m_bfme310c = 0;
	m_bfme3110 = 0;
	m_bfme3174 = 0;
	m_bfme3178 = 0;
	g_bfmeS1142 = this;
}
