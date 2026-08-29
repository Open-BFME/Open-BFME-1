// Open-BFME5 conversions.

struct BfmeG1144
{
	char m_bfmePad0000[0x18];
	char m_bfme018;
	char m_bfmePad0019[0x3];
	char m_bfme01c;
	char m_bfmePad001d[0x1];
	char m_bfme01e;
	char m_bfme01f;
	char m_bfmePad0020[0x8];
	char m_bfme028;
	char m_bfmePad0029[0x1b];
	char m_bfme044;
	char m_bfmePad0045[0x2];
	char m_bfme047;
	char m_bfmePad0048[0x10];
	char m_bfme058;
	char m_bfmePad0059[0xb];
	char m_bfme064;
	char m_bfme065;
	char m_bfmePad0066[0x2];
	int m_bfme068;
	char m_bfmePad006c[0x20];
	char m_bfme08c;
	char m_bfmePad008d[0x167];
	int m_bfme1f4;
	int m_bfme1f8;
	int m_bfme1fc;
	char m_bfmePad0200[0x98c];
	int m_bfmeb8c;
};

struct BfmeH1144
{
	char m_bfmePad0000[0x170c];
	int m_bfme170c;
};

extern "C" BfmeG1144 *volatile g_bfmeG1144;
extern "C" BfmeH1144 *volatile g_bfmeH1144;

class BfmeA1144
{
public:
	void bfmeGo1144(void);
	char m_bfmePad0000[0xf0];
	volatile int m_bfme0f0;
	volatile char m_bfme0f4;
	volatile char m_bfme0f5;
	volatile char m_bfme0f6;
	volatile char m_bfme0f7;
	volatile char m_bfme0f8;
	volatile char m_bfme0f9;
	char m_bfmePad00fa[0x2];
	volatile int m_bfme0fc;
	volatile int m_bfme100;
	volatile int m_bfme104;
	volatile char m_bfme108;
	volatile char m_bfme109;
	char m_bfmePad010a[0x2];
	volatile int m_bfme10c;
	volatile char m_bfme110;
	volatile char m_bfme111;
	volatile char m_bfme112;
	volatile char m_bfme113;
	volatile int m_bfme114;
	volatile int m_bfme118;
	volatile int m_bfme11c;
	char m_bfmePad0120[0x15c4];
	volatile int m_bfme16e4;
	volatile int m_bfme16e8;
};

void BfmeA1144::bfmeGo1144(void)
{
	m_bfme0f0 = g_bfmeG1144->m_bfmeb8c;
	m_bfme0f4 = g_bfmeG1144->m_bfme064;
	m_bfme0f5 = g_bfmeG1144->m_bfme065;
	m_bfme0f6 = g_bfmeG1144->m_bfme047;
	m_bfme0f7 = (char)(g_bfmeG1144->m_bfme028 == 0);
	m_bfme114 = g_bfmeH1144->m_bfme170c;
	m_bfme0f8 = g_bfmeG1144->m_bfme044;
	m_bfme0f9 = g_bfmeG1144->m_bfme08c;
	m_bfme0fc = g_bfmeG1144->m_bfme1f4;
	m_bfme100 = g_bfmeG1144->m_bfme1f8;
	m_bfme104 = g_bfmeG1144->m_bfme1fc;

	char b = (char)(g_bfmeG1144->m_bfme01c == 0);

	m_bfme108 = b;
	m_bfme109 = b;
	m_bfme10c = g_bfmeG1144->m_bfme068;
	m_bfme110 = g_bfmeG1144->m_bfme01e;
	m_bfme111 = g_bfmeG1144->m_bfme058;
	m_bfme112 = g_bfmeG1144->m_bfme018;
	m_bfme113 = g_bfmeG1144->m_bfme01f;
	m_bfme118 = m_bfme16e4;
	m_bfme11c = m_bfme16e8;
}
