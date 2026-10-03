// stlport
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

class Rva003527B0Tables
{
public:
	void markReleased();

private:
	char m_pad0[0x18];
	unsigned char *m_records0;
	char m_pad1[0x0C];
	int m_head0;
	char m_pad2[0x0C];
	unsigned char *m_records1;
	char m_pad3[0x0C];
	int m_head1;
};

extern void j_0000cec8();

struct BfmeNodeZN
{
	BfmeNodeZN *m_bfmeNextZN;
};

class Rva0035E710Owner
{
public:
	void bfmeDoZN(void *a, BfmeNodeZN **link, void *what);
};

namespace Rva0035E510 {

class BfmeHeadEAT
{
public:
	int m_bfmeHeadEAT;
};

class BfmeBaseEAT
{
public:
	int m_bfmeAEAT;
	int m_bfmeBEAT;
};

class BfmeSubAEAT
{
public:
	void bfmeSwapAEAT(BfmeSubAEAT *other);
	unsigned char m_bfmeBodyAEAT[0x20];
};

class BfmeSubBEAT
{
public:
	void bfmeSwapBEAT(BfmeSubBEAT *other);
	unsigned char m_bfmeBodyBEAT[0x20];
};

class BfmeNodeEAT : public BfmeHeadEAT, public BfmeBaseEAT
{
public:
	void bfmeSwapEAT(BfmeNodeEAT *other);
	inline void bfmeFixEAT()
	{
		reinterpret_cast<Rva003527B0Tables *>(this)->markReleased();
	}
	void bfmeLinkEAT(BfmeNodeEAT *node, int *a, int *b);
	void bfmeRelinkEAT(BfmeNodeEAT *node, int *a, int *b);

	BfmeSubAEAT m_bfmeSubAEAT;
	BfmeSubBEAT m_bfmeSubBEAT;
};

void BfmeNodeEAT::bfmeLinkEAT(BfmeNodeEAT *node, int *a, int *b)
{
	_STL::deque<BfmeNodeZN **> links;
	for (BfmeNodeZN **link = reinterpret_cast<BfmeNodeZN **>(a); *link; link = &(*link)->m_bfmeNextZN)
		links.push_back(link);
	Rva0035E710Owner *owner = reinterpret_cast<Rva0035E710Owner *>(this);
	while (!links.empty()) {
		// Retail calls helper 0x0035E5A0 through its ILT thunk 0x0000CEC8.
		typedef void (Rva0035E710Owner::*DoZN)(void *, BfmeNodeZN **, void *);
		union { void (*fn)(); DoZN call; } doZN = { j_0000cec8 };
		(owner->*doZN.call)(node, links.back(), b);
		links.pop_back();
	}
}

}
