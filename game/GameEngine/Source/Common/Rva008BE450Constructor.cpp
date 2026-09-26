// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??0Rva008BE450SizedDeleting@@QAE@XZ
// Constructor of the class whose destructor is 0x008BE480 (same vtable
// 0x01136E00). The inlined base constructor matches the standalone base
// constructor at 0x008AB8B0 (vtable 0x01136854); its vtable store is dead and
// the compiler drops it, which is why fields +0x04..+0x14 precede the store.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned char m_unreconstructed_02[6];
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern unsigned char g_bfmeFlag1281;

class BfmeString1286
{
public:
	BfmeString1286() : m_data(&g_bfmeDefaultString1284)
	{
		++m_data->m_refCount;
	}

private:
	BfmeStringData3AF0 *m_data;
};

class BfmeBase1286
{
public:
	BfmeBase1286() : m_bfme04(-1), m_bfme08(0), m_bfme0c(0), m_bfme10(0), m_bfme14(0) {}
	virtual ~BfmeBase1286();

protected:
	int m_bfme04;
	int m_bfme08;
	void *m_bfme0c;
	void *m_bfme10;
	unsigned char m_bfme14;
};

class Rva008BE450SizedDeleting : public BfmeBase1286
{
public:
	Rva008BE450SizedDeleting();
	virtual ~Rva008BE450SizedDeleting();

private:
	BfmeString1286 m_bfme18;
	BfmeString1286 m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	unsigned int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	int m_bfme44;
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	int m_bfme5c;
	int m_bfme60;
	int m_bfme64;
	int m_bfme68;
	int m_bfme6c;
	int m_bfme70;
	unsigned int m_lowBits : 3;
	unsigned int m_globalBit : 1;
	unsigned int m_remainingBits : 28;
};

Rva008BE450SizedDeleting::Rva008BE450SizedDeleting()
{
	m_bfme24 = -1;
	m_bfme28 = 1;
	m_bfme2c = 1;
	m_bfme30 = -1;
	m_bfme38 = 3;
	m_bfme3c = 3;
	m_lowBits = 0;
	m_bfme20 = 0;
	m_bfme34 = 0xff000000;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme6c = 0;
	m_bfme70 = 0;
	m_globalBit = g_bfmeFlag1281;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
}
