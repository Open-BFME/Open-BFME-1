// Open-BFME5 conversions.

extern "C" void __identifier("?handle@Rva007F4BA0@@W3AEXXZ")();
extern "C" void __identifier("?eq@Rva007F4B80@@QBEHPBVObj007F4B80@@HH@Z")();
extern "C" void __identifier("?d_007f4bb0@@YAXXZ")();

extern void * const g_bfmeVft969D1[3] =
{
	(void *)&__identifier("?handle@Rva007F4BA0@@W3AEXXZ"),
	(void *)&__identifier("?eq@Rva007F4B80@@QBEHPBVObj007F4B80@@HH@Z"),
	(void *)&__identifier("?d_007f4bb0@@YAXXZ"),
};
extern char g_bfmeVft969D2[];
extern char g_bfmeVft969D3[];

class BfmeD969
{
public:
	void bfmeGo969D();
	void bfmeBase969D();

	char *volatile m_bfmeVft;
	char *volatile m_bfmeVft2;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
};

void BfmeD969::bfmeGo969D()
{
	m_bfmeVft2 = (char *)g_bfmeVft969D1;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfmeVft2 = g_bfmeVft969D2;
	m_bfmeVft = g_bfmeVft969D3;
	bfmeBase969D();
}
