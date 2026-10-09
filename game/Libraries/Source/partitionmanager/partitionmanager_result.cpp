// Open-BFME5 conversions.

struct BfmeElemVJX;

struct BfmeCmpVJX
{
	char m_bfme00;
};

void __cdecl bfmeSortAVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);
void __cdecl bfmeSortBVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);

// Both sorts are matched rows the body calls directly (callees.py): mode 2
// runs ?Rva009F3FD0 and mode 1 ?Rva009F3F80, the eight-byte introsort drivers
// in Q3IntrosortFamilies.cpp. The comparator word goes by value either way.
struct Q3SortElem8;
struct Q3SortCompare;
void __cdecl Rva009F3FD0(Q3SortElem8 *a, Q3SortElem8 *b, Q3SortCompare c);
void __cdecl Rva009F3F80(Q3SortElem8 *a, Q3SortElem8 *b, Q3SortCompare c);
typedef void (__cdecl *BfmeSortVJX)(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);
#define bfmeSortAVJX ((BfmeSortVJX)Rva009F3FD0)
#define bfmeSortBVJX ((BfmeSortVJX)Rva009F3F80)

struct BfmeRangeVJX
{
	BfmeElemVJX *m_bfme00;
	BfmeElemVJX *m_bfme04;
};

class BfmeThingVJX
{
public:
	void bfmeGoVJX(int mode);
	BfmeRangeVJX *m_bfme00;
};

void BfmeThingVJX::bfmeGoVJX(int mode)
{
	BfmeCmpVJX c;
	switch (mode)
	{
	case 2:
		c.m_bfme00 = 0;
		bfmeSortAVJX(m_bfme00->m_bfme00, m_bfme00->m_bfme04, c);
		break;
	case 1:
		c.m_bfme00 = 0;
		bfmeSortBVJX(m_bfme00->m_bfme00, m_bfme00->m_bfme04, c);
		break;
	}
}
