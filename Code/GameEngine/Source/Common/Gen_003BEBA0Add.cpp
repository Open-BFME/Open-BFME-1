// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

void * __cdecl operator new(unsigned int);

class AsciiStringWI
{
public:
	AsciiStringWI(const AsciiStringWI &other);
	~AsciiStringWI(void);

private:
	char *m_bfmeData;
};

class BfmeStrWI : private AsciiStringWI
{
public:
	BfmeStrWI(const AsciiStringWI &other) : AsciiStringWI(other) {}
	~BfmeStrWI(void) {}
};

struct BfmePairWI
{
	float m_bfmeA;
	float m_bfmeB;
};

class Gen_003BEA30
{
public:
	Gen_003BEA30(const BfmePairWI &pair, int kind, const AsciiStringWI &first,
		bool flag, const AsciiStringWI &second);

	BfmePairWI m_bfmePair;
	int m_bfmeKind;
	BfmeStrWI m_bfmeFirst;
	BfmeStrWI m_bfmeSecond;
	bool m_bfmeFlag;
};

class BfmeSinkAM
{
public:
	void registerItem(int handle, Gen_003BEA30 *item, int variant);
};

extern BfmeSinkAM *g_bfmeSinkAM;

class BfmeCounterAM
{
public:
	int allocId() { return ++m_next; }

	char m_pad[0x20];
	int m_next;
};

class Gen_003BEBA0
{
public:
	void add(BfmePairWI pair, const AsciiStringWI &first, bool flag,
		const AsciiStringWI &second);

private:
	char m_head[0x28];
	BfmeCounterAM *m_counter;
	char m_gap[0x0C];
	_STL::vector<Gen_003BEA30 *> m_vec;
};

void Gen_003BEBA0::add(BfmePairWI pair, const AsciiStringWI &first, bool flag,
	const AsciiStringWI &second)
{
	Gen_003BEA30 *item = new Gen_003BEA30(pair, m_counter->allocId(), first,
		flag, second);
	g_bfmeSinkAM->registerItem(item->m_bfmeKind, item, 1);
	m_vec.push_back(item);
}
