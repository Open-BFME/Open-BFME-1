// ??0BfmeThingUEW@@QAE@PAUBfmeThingUEWConfig@@@Z
// partial score=0.6 date=2026-09-10
// cl: /O2 /DNDEBUG /MD /EHsc

// This is the BFME constructor at 0x008A2CF0.  Its caller-visible layout is
// recovered from the matching bfmeGoUE/clearLN family and from the retail
// constructor's field stores; the large arrays are deliberately represented
// as raw words so their zeroing remains the compiler's intrinsic rep stosd.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);

extern "C" void *memset(void *destination, int value, unsigned int bytes);
#pragma intrinsic(memset)

class AptValue;
extern AptValue *g_bfmeFallbackDB;

class Gen_008BE660
{
public:
	Gen_008BE660();

private:
	void *m_value;
};

template <int Words>
class BfmeZeroWords
{
public:
	BfmeZeroWords()
	{
		memset(m_words, 0, Words * 4);
	}

private:
	unsigned int m_words[Words];
};

__forceinline void *__cdecl operator new[](unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void __cdecl operator delete[](void *block) throw();

class BfmeVecEVE
{
public:
	BfmeVecEVE();
	~BfmeVecEVE();

private:
	unsigned char m_data[0x20];
};

class BfmeThingLN
{
public:
	void bfmeClearLN();
};

struct BfmeThingUEWConfig
{
	unsigned char m_pad00[0x0c];
	int m_value0c;
	int m_value10;
	int m_value14;
	int m_value18;
	int m_value1c;
};

class BfmeThingUEW
{
public:
	BfmeThingUEW(BfmeThingUEWConfig *config);

private:
	void *m_value00;
	void *m_value04;
	void *m_value08;
	void *m_value0c;
	int m_value10;
	int m_value14;
	BfmeZeroWords<0x200> m_zero18;
	int m_value818;
	void *m_value81c;
	int m_value820;
	BfmeZeroWords<0x40> m_zero824;
	int m_value924;
	BfmeZeroWords<0x40> m_zero928;
	int m_valuea28;
	BfmeZeroWords<0x200> m_zeroa2c;
	Gen_008BE660 m_owned;
	BfmeVecEVE *m_vectors;
	int m_value1234;
	int m_value1238;
	void *m_value123c;
	void *m_value1240;
	unsigned char m_pad1244[0x18];
	void *m_value125c;
	void *m_value1260;
	unsigned char m_value1264;
	unsigned char m_pad1265[7];
	int m_value126c;
	int m_value1270;
	int m_value1274;
	int m_value1278;
	unsigned char m_pad127c[0x20];
	int m_value129c;
	int m_value12a0;
	int m_value12a4;
	int m_value12a8;
	int m_value12ac;
	int m_value12b0;
};

BfmeThingUEW::BfmeThingUEW(BfmeThingUEWConfig *config)
	: m_value14(0),
	  m_zero18(),
	  m_value820(0),
	  m_zero824(),
	  m_value924(0),
	  m_zero928(),
	  m_valuea28(0),
	  m_zeroa2c(),
	  m_owned()
{
	m_value12a0 = config->m_value18;
	m_value12a4 = config->m_value10;
	m_value12a8 = config->m_value1c;
	m_value12ac = config->m_value14;

	m_value12b0 = config->m_value0c;
	m_value0c = Rva008C5D70Alloc(m_value12a0 * 4);

	m_value00 = Rva008C5D70Alloc(m_value12b0 * 5 * 4);
	m_value81c = Rva008C5D70Alloc(m_value12ac * 0x1c);

	if (m_value81c != 0)
		m_vectors = new BfmeVecEVE[m_value12a4];
	else
		m_vectors = 0;

	m_value123c = Rva008C5D70Alloc(m_value12a8 * 4);
	m_value08 = m_value00;
	m_value04 = m_value00;
	m_value10 = 0;
	((BfmeThingLN *)this)->bfmeClearLN();
	m_value1238 = 0;
	m_value126c = 0;
	m_value1270 = 0;
	m_value1274 = 0;
	m_value1278 = 0;
	m_value818 = 0;
	m_value1234 = 0;
	m_value129c = 0;
	m_value1240 = g_bfmeFallbackDB;
	m_value125c = g_bfmeFallbackDB;
	m_value1260 = g_bfmeFallbackDB;
	m_value1264 = 0;
}
