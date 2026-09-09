// BFME-only no-argument GameClient vtable entry at retail 0x00592B80.
// The address-derived spelling is intentional: the owning class and vtable
// slot are proven, but no surviving source establishes the original name.
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

struct BfmeCfgABO
{
	int m_bfme00ABO;
	int m_bfme04ABO;
	int m_bfme08ABO;
	int m_bfme0CABO;
	int m_bfme10ABO;
	unsigned char m_bfme14ABO;
	unsigned char m_bfme15ABO;
	unsigned char m_bfmePaddingABO[2];
};

struct Gen_p24pod
{
	int m_bfme00ABO;
	int m_bfme04ABO;
	int m_bfme08ABO;
	int m_bfme0CABO;
	int m_bfme10ABO;
	unsigned char m_bfme14ABO;
	unsigned char m_bfme15ABO;
	unsigned char m_bfmePaddingABO[2];
};

namespace _STL
{
	template <class Iterator, class Type>
	void fill(Iterator first, Iterator last, const Type &value);
}

class AptPalantirStore
{
public:
	void clear();
};

class Rva00592A10Owner
{
public:
	void reset();
};

class GameClient;

template <class Type>
class StringBase
{
private:
	friend class GameClient;
	void releaseBuffer();

	void *m_data;
};

struct BfmePairABO
{
	float m_bfmeAABO;
	float m_bfmeBABO;
};

struct BfmeOtherABO
{
	unsigned char m_bfmeHeadABO[0x1f4];
	int m_bfme1F4ABO;
};

class GameClient
{
public:
	void bfmeReset00592B80();

	unsigned char m_bfmeH00[0xc];
	BfmeOtherABO *m_bfme0CABO;
	unsigned char m_bfmeH10[4];
	int m_bfme14ABO;
	unsigned char m_bfmeH18[0x4c - 0x18];
	unsigned char m_bfme4CABO;
	unsigned char m_bfmeH4D[0x58 - 0x4d];
	unsigned char m_bfme58ABO;
	unsigned char m_bfmeH59[0x60 - 0x59];
	int m_bfme60ABO;
	int m_bfme64ABO;
	unsigned char m_bfmeH68[0x154 - 0x68];
	AptPalantirStore m_bfme154ABO;
	unsigned char m_bfmeH155[0x2b8 - 0x155];
	unsigned char m_bfme2B8ABO;
	unsigned char m_bfmeH2B9[3];
	int m_bfme2BCABO;
	unsigned char m_bfme2C0ABO;
	unsigned char m_bfmeH2C1[0x458 - 0x2c1];
	unsigned char m_bfme458ABO;
	unsigned char m_bfmeH459[0x468 - 0x459];
	volatile unsigned char m_bfme468ABO;
	unsigned char m_bfmeH469[3];
	int m_bfme46CABO;
	int m_bfme470ABO;
	int m_bfme474ABO;
	volatile int m_bfme478ABO;
	unsigned char m_bfmeH47C[0x488 - 0x47c];
	Rva00592A10Owner m_bfme488ABO;
	unsigned char m_bfmeH489[0x4c8 - 0x489];
	int m_bfme4C8ABO;
	unsigned char m_bfmeH4CC[4];
	int m_bfme4D0ABO;
	unsigned char m_bfme4D4ABO;
	unsigned char m_bfmeH4D5[3];
	StringBase<char> m_bfme4D8ABO;
	BfmePairABO m_bfme4DCABO[4];
};

void GameClient::bfmeReset00592B80()
{
	m_bfme14ABO = 0;
	m_bfme154ABO.clear();

	Gen_p24pod cfg;

	m_bfme458ABO = 0;
	m_bfme2B8ABO = 0;

	cfg.m_bfme00ABO = m_bfme2BCABO;
	cfg.m_bfme04ABO = 0;
	cfg.m_bfme08ABO = -1;
	cfg.m_bfme0CABO = -1;
	cfg.m_bfme10ABO = -1;
	cfg.m_bfme14ABO = 0;
	cfg.m_bfme15ABO = 0;

	_STL::fill((Gen_p24pod *)&m_bfme2C0ABO, (Gen_p24pod *)&m_bfme458ABO, cfg);

	m_bfme488ABO.reset();

	m_bfme468ABO = 0;
	m_bfme478ABO = 0;
	_ReadWriteBarrier();

	m_bfme46CABO = -2;
	m_bfme470ABO = -2;
	m_bfme474ABO = -2;
	m_bfme58ABO = (unsigned char)(m_bfme58ABO & 0xc4);
	m_bfme64ABO = 1;
	m_bfme4C8ABO = 0;
	m_bfme60ABO = -1;
	m_bfme4D4ABO = 0;
	m_bfme4D0ABO = -1;

	m_bfme4D8ABO.releaseBuffer();

	BfmePairABO value = { 0.0f, 0.0f };
	BfmePairABO *p = m_bfme4DCABO;
	BfmePairABO *end = m_bfme4DCABO + 4;

	if (p != end)
	{
		do
		{
			*p = value;
			++p;
		} while (p != end);
	}

	m_bfme58ABO = (unsigned char)(m_bfme58ABO & 0x3f);

	if (m_bfme0CABO != 0)
		m_bfme0CABO->m_bfme1F4ABO = 0;

	m_bfme4CABO = 1;
}
