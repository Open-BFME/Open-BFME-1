// bfmeVftCIA is ??_7Gen_000B5240@@6B@ at 0x010827DC, the vftable of the
// Gen_000B5240 class (see dir32_addresses.csv).
extern "C" unsigned char __identifier("??_7Gen_000B5240@@6B@")[];
#define bfmeVftCIA __identifier("??_7Gen_000B5240@@6B@")

struct AudioEventInfo
{
	AudioEventInfo();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x94];
};

struct Rva000B5450Thing : public AudioEventInfo
{
	explicit Rva000B5450Thing(void *what);
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	void *volatile m_bfmeC;
};

Rva000B5450Thing::Rva000B5450Thing(void *what)
{
	m_bfmeVft = bfmeVftCIA;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = what;
}
