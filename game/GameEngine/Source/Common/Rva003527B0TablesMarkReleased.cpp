// stlport
#include <algorithm>
// ?markReleased@Rva003527B0Tables@@QAEXXZ
// cl: /DNDEBUG /MD /O2

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

void Rva003527B0Tables::markReleased()
{
	unsigned char mark = 1;
	int index = m_head0;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records0;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0xC) = mark;
			p = (unsigned int)m_records0;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}

	index = m_head1;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records1;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0xC) = mark;
			p = (unsigned int)m_records1;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}
}

// RVA0035E510,108B: retain the bank labels in an address-qualified scope.
// Both 32-byte block swaps are independently matched at00356830/003569D0.
// markReleased must be visible in this TU: its proven body preserves ECX,
// allowing the following member helper0035C9C0 to reuse the receiver.
// Native std::swap supplies the retail ordering of the two leading fields.
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

void BfmeNodeEAT::bfmeSwapEAT(BfmeNodeEAT *other)
{
	BfmeBaseEAT *b = other;
	int *link = &m_bfmeAEAT;

    std::swap(link[0], b->m_bfmeAEAT);
    std::swap(link[1], b->m_bfmeBEAT);

	m_bfmeSubAEAT.bfmeSwapAEAT(&other->m_bfmeSubAEAT);

	m_bfmeSubBEAT.bfmeSwapBEAT(&other->m_bfmeSubBEAT);

	bfmeFixEAT();

	bfmeLinkEAT(other, &other->m_bfmeAEAT, link);

	bfmeRelinkEAT(other, &other->m_bfmeBEAT, &m_bfmeBEAT);
}

} // namespace Rva0035E510
