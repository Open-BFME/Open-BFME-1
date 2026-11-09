// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

// Retail copies the string member through ILT 0x0001400B (?j_0001400b@@YAXXZ,
// jumping to 0x00424F50); call the ILT by its row name rather than a pin.
extern "C" void __identifier("?j_0001400b@@YAXXZ")();

class BfmeStrVTH
{
public:
	typedef void (BfmeStrVTH::*Rva0001400BCall)(const BfmeStrVTH &);
	union Rva0001400BCallAddress
	{
		void *raw;
		Rva0001400BCall member;
	};

	__forceinline void copyFrom(const BfmeStrVTH &other)
	{
		Rva0001400BCallAddress call;
		call.raw = (void *)&__identifier("?j_0001400b@@YAXXZ");
		(this->*call.member)(other);
	}
	char *m_bfme00;
};

struct BfmeEntVTH
{
	__forceinline BfmeEntVTH(const BfmeEntVTH &other)
		: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04),
		  m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c)
	{
		m_bfme10.copyFrom(other.m_bfme10);
	}

	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	BfmeStrVTH m_bfme10;
};

void bfmeConstructVTH(BfmeEntVTH *dest, const BfmeEntVTH *source)
{
	new (dest) BfmeEntVTH(*source);
}
