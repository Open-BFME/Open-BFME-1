// cl: /O2 /DNDEBUG /MD /EHsc
// RVA 008A2F30, 246B: destructor of the object constructed at 008A2CF0.
// Matched caller 00891D70 destroys then frees the same 0x12B4-byte object.
// Five member cleanups follow reverse construction order; array element
// size 0x20 and cookie count come from the retail delete[] sequence.
// Owner name remains address-derived; older caller/ctor uses BfmeThingUEW.

extern void (__cdecl *TheBfmeFree)(void *block, unsigned int bytes);

extern void (__cdecl *Rva008A30A0ReleasePtr)(void *block);

class Rva008A0DC0Entry;

class Rva008A0DC0Owner
{
public:
	~Rva008A0DC0Owner();

private:
	int m_liveCount;
	Rva008A0DC0Entry *m_entries[512];
};

class Rva008A0E70Entry;

class Rva008A0E70Owner
{
public:
	void sweep();

	~Rva008A0E70Owner()
	{
		sweep();
	}

private:
	int m_liveCount;
	Rva008A0E70Entry *m_entries[0x40];
};

class BfmeE1046;

class BfmeD1046
{
public:
	void bfmeGo1046E(void);

	BfmeE1046 *m_bfmeP;
};

class Gen_008BE660
{
public:
	~Gen_008BE660()
	{
		m_value.bfmeGo1046E();
	}

private:
	BfmeD1046 m_value;
};

class BfmeVecEVE
{
public:
	~BfmeVecEVE();

	void *operator new[](unsigned int bytes);

	void operator delete[](void *block)
	{
		Rva008A30A0ReleasePtr(block);
	}

private:
	unsigned char m_data[0x20];
};

struct FiveDwordElem008A2CF0;
struct SevenDwordElem008A2CF0;

class Rva008A2CF0Owner
{
public:
	~Rva008A2CF0Owner();

private:
	FiveDwordElem008A2CF0 *m_value00;
	FiveDwordElem008A2CF0 *m_value04;
	FiveDwordElem008A2CF0 *m_value08;
	void *m_value0c;							///< m_value12a0 * 4 bytes
	int m_value10;
	Rva008A0DC0Owner m_zero14;
	int m_value818;
	SevenDwordElem008A2CF0 *m_value81c;
	Rva008A0E70Owner m_zero820;
	Rva008A0E70Owner m_zero924;
	Rva008A0DC0Owner m_zeroa28;
	Gen_008BE660 m_owned;						///< +0x122C
	BfmeVecEVE *m_vectors;
	int m_value1234;
	int m_value1238;
	void *m_value123c;							///< m_value12a8 * 4 bytes
	void *m_value1240;
	unsigned char m_pad1244[0x1c];
	void *m_value1260;
	void *m_value1264;
	int m_value1268;
	int m_value126c;
	int m_value1270;
	int m_value1274;
	int m_value1278;
	int m_value127c;
	unsigned char m_pad1280[0x1c];
	int m_value129c;
	int m_value12a0;
	int m_value12a4;
	int m_value12a8;
	int m_value12ac;
	int m_value12b0;
};

Rva008A2CF0Owner::~Rva008A2CF0Owner()
{
	TheBfmeFree(m_value123c, m_value12a8 * 4);

	BfmeVecEVE *vectors = m_vectors;
	delete[] vectors;

	void *elements = m_value81c;
	Rva008A30A0ReleasePtr(elements);
	Rva008A30A0ReleasePtr(m_value00);

	void *bytes = m_value0c;
	unsigned int size = m_value12a0 * 4;
	TheBfmeFree(bytes, size);
}