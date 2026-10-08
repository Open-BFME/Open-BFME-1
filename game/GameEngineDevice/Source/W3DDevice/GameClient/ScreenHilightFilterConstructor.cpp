// cl: /O2 /Ob0

// Retail 0x01128B88: the highlight filter's seven-cell dispatch table.
// The retail constructor installs this physical table as its vptr.
extern void *g_01128B88[7];

void j_0004831a();
void j_0002960e();
void j_0000e24b();
void j_00028498();
void j_000171bb();
void j_00018f20();
void j_0001aeba();

extern "C" void *__identifier("?g_01128B88@@3PAPAXA")[7] =
{
	(void *)&j_0004831a,
	(void *)&j_0002960e,
	(void *)&j_0000e24b,
	(void *)&j_00028498,
	(void *)&j_000171bb,
	(void *)&j_00018f20,
	(void *)&j_0001aeba,
};

class ScreenHilightFilter
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	char m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;

public:
	ScreenHilightFilter();
};

ScreenHilightFilter::ScreenHilightFilter()
{
	m_vptr = (void *)g_01128B88;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
}
