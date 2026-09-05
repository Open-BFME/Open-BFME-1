// ?init@Rva0040B5A0@@QAEXXZ
// cl: /O2 /Ob0

class AsciiString
{
public:
	void set(const AsciiString &other);
	char m_data[4];
};

struct Triple
{
	int a, b, c;
};

extern AsciiString g_s08;
extern AsciiString g_s0C;
extern AsciiString g_s10;
extern float g_f14;
extern float g_msToSec;
extern int g_i18;
extern float g_degToRad;
extern AsciiString g_s20;
extern int g_i24;
extern float g_f28;
extern double g_dScale;
extern Triple g_t2C;
extern int g_i38;
extern int g_i3C;
extern int g_i48;
extern char g_b4C;
extern char g_b80;
extern char g_b81;
extern int g_i50;
extern Triple g_t54;
extern int g_i60;
extern Triple g_t64;
extern int g_i70;
extern Triple g_t74;
extern int g_i84;
extern int g_i88;
extern int g_i8C;
extern int g_i90;
extern int g_i94;
extern int g_i98;
extern AsciiString g_s9C;
extern float g_012F11CC;
extern float g_010F0ADC;
extern float g_01076C24;

float Cos(float);
float Sin(float);

class Rva0040B5A0
{
public:
	void init();
	char m_00[8];
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	float m_14;
	float m_18;
	char m_1C[4];
	AsciiString m_20;
	int m_24;
	float m_28;
	Triple m_2C;
	int m_38;
	int m_3C;
	float m_40;
	float m_44;
	int m_48;
	char m_4C;
	char m_4D[3];
	int m_50;
	Triple m_54;
	int m_60;
	Triple m_64;
	int m_70;
	Triple m_74;
	char m_80;
	char m_81;
	char m_82[2];
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
	AsciiString m_9C;
};

void Rva0040B5A0::init()
{
	m_08.set(g_s08);
	m_0C.set(g_s0C);
	m_10.set(g_s10);
	m_14 = g_msToSec * g_f14;
	m_18 = (float)g_i18 * g_degToRad;
	m_20.set(g_s20);
	m_24 = g_i24;
	m_28 = (float)(g_f28 * g_dScale);
	m_2C = g_t2C;
	m_38 = g_i38;
	m_3C = g_i3C;
	m_48 = g_i48;
	m_4C = g_b4C;
	m_80 = g_b80;
	m_81 = g_b81;
	m_50 = g_i50;
	m_54 = g_t54;
	m_60 = g_i60;
	m_64 = g_t64;
	m_70 = g_i70;
	m_74 = g_t74;
	m_84 = g_i84;
	m_88 = g_i88;
	m_8C = g_i8C;
	m_90 = g_i90;
	m_94 = g_i94;
	m_98 = g_i98;
	m_9C.set(g_s9C);
	m_40 = (Cos(m_18) * g_012F11CC) * g_010F0ADC;
	m_44 = (Sin(m_18) * g_012F11CC) * g_01076C24;
}
