// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

void __cdecl j_0001ab86(void);

class BfmeStrVSY
{
public:
	__forceinline BfmeStrVSY(const BfmeStrVSY &other)
	{
		union CopyCall
		{
			void (__cdecl *freeCall)(void);
			void (BfmeStrVSY::*memberCall)(const BfmeStrVSY &);
		} copyCall;
		copyCall.freeCall = &j_0001ab86;
		(this->*copyCall.memberCall)(other);
	}

	~BfmeStrVSY() { ((StringBase<char> *)this)->clear(); }
	char *m_bfme00;
	int m_bfme04;
};

struct BfmeEntVSY
{
	__forceinline BfmeEntVSY(const BfmeEntVSY &other)
		: m_bfme00(other.m_bfme00), m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c)
	{
	}

	BfmeStrVSY m_bfme00;
	int m_bfme08;
	int m_bfme0c;
};

void bfmeConstructVSY(BfmeEntVSY *dest, const BfmeEntVSY *source)
{
	new (dest) BfmeEntVSY(*source);
}
