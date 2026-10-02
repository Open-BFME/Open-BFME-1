// Open-BFME5 conversions.

// The +0 member is a narrow string copied through the ONE narrow copy
// constructor, 0x00887B60 (StringBase<char>'s, which the ledger's ICF group
// also spells BuddyInfo / FXNugget-list).  AsciiString's copy constructor is
// inline and forwards to exactly that body, which is what retail call sites do.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value) throw();

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

typedef AsciiString BfmeStrVTC;

class BfmeTargetVTC
{
public:
	int m_bfme00;
	long m_bfme04;
};

struct BfmeEntVTC
{
	__forceinline BfmeEntVTC(const BfmeEntVTC &other)
		: m_bfme00(other.m_bfme00)
	{
		m_bfme04 = other.m_bfme04;

		if (m_bfme04 != 0)
			InterlockedIncrement(&m_bfme04->m_bfme04);
	}

	BfmeStrVTC m_bfme00;
	BfmeTargetVTC *m_bfme04;
};

void bfmeConstructVTC(BfmeEntVTC *dest, const BfmeEntVTC *source)
{
	new (dest) BfmeEntVTC(*source);
}
