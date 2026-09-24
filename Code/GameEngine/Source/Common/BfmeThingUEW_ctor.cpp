// ??0BfmeThingUEW@@QAE@PAUBfmeThingUEWConfig@@@Z
// cl: /O2 /DNDEBUG /MD /EHsc
// BfmeThingUEW constructor at 0x008A2CF0; member types follow the retail unwind map.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern void (__cdecl *Rva008A30A0ReleasePtr)(void *block);

extern "C" void *memset(void *destination, int value, unsigned int bytes);
#pragma intrinsic(memset)

class AptValue;
extern AptValue *g_bfmeFallbackDB;

class Rva008A0DC0Entry;
class Rva008A0E70Entry;

// Unwind states 0 and 3 release these through 0x008A0DC0.
class Rva008A0DC0Owner
{
public:
	Rva008A0DC0Owner()
		: m_liveCount(0)
	{
		memset(m_entries, 0, sizeof(m_entries));
	}
	~Rva008A0DC0Owner();

private:
	int m_liveCount;
	Rva008A0DC0Entry *m_entries[512];
};

// Unwind states 1 and 2 release these through 0x008A0E70.
class Rva008A0E70Owner
{
public:
	Rva008A0E70Owner()
		: m_liveCount(0)
	{
		memset(m_entries, 0, sizeof(m_entries));
	}
	~Rva008A0E70Owner();

private:
	int m_liveCount;
	Rva008A0E70Entry *m_entries[0x40];
};

class Gen_008BE660
{
public:
	Gen_008BE660();
	~Gen_008BE660();

private:
	void *m_value;
};

// Unwind state 5 hands the new[] block to the out-of-line delete[] at 0x008A05B0.
class BfmeVecEVE
{
public:
	BfmeVecEVE();
	~BfmeVecEVE();

	void *operator new[](unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	void operator delete[](void *block)
	{
		Rva008A30A0ReleasePtr(block);
	}

private:
	unsigned char m_data[0x20];
};

struct FiveDwordElem008A2CF0
{
	void *operator new[](unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	int m_words[5];
};

struct SevenDwordElem008A2CF0
{
	void *operator new[](unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	int m_words[7];
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
	FiveDwordElem008A2CF0 *m_value00;
	FiveDwordElem008A2CF0 *m_value04;
	FiveDwordElem008A2CF0 *m_value08;
	void *m_value0c;
	int m_value10;
	Rva008A0DC0Owner m_zero18;
	int m_value818;
	SevenDwordElem008A2CF0 *m_value81c;
	Rva008A0E70Owner m_zero824;
	Rva008A0E70Owner m_zero928;
	Rva008A0DC0Owner m_zeroa2c;
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
{
	m_value12a0 = config->m_value18;
	m_value12a4 = config->m_value10;
	m_value12a8 = config->m_value1c;
	m_value12ac = config->m_value14;
	m_value12b0 = config->m_value0c;
	m_value0c = Rva008C5D70Alloc(m_value12a0 * 4);
	m_value00 = new FiveDwordElem008A2CF0[m_value12b0];
	m_value81c = new SevenDwordElem008A2CF0[m_value12ac];
	m_vectors = new BfmeVecEVE[m_value12a4];
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
