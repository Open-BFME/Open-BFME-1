// ??0Rva009A45A0CollisionData@@QAE@XZ
// partial score=0.99 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc
//
// Rva009A45A0CollisionData::Rva009A45A0CollisionData, retail 0x009A45A0,
// 117 bytes. CollisionManager::CollisionManager at 0x009A25B0 calls it, and
// the 460-byte body at 0x009A2750 merges the buckets at +0x0C and +0xC068.
// The product class name is not recovered, so the address stays in the name.
//
// The object holds two cell buckets. Each bucket keeps its cells first and
// two volatile counters right after them, so the pair at +0xAE08 closes the
// bucket at +0x18 and the pair at +0xC060 closes the bucket at +0xAE10.
// Retail zeroes both counters, then clears the cells, in both buckets. That
// repeat is what proves the bucket is one type used twice.
//
// Seven bytes still differ. Retail pops ESI right after the store of 3 to
// +0xC068, and this source pops it two stores later. Every other byte
// matches, including the whole prologue.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

template <int N>
struct Rva009A45A0Bucket
{
	int m_cellsJU[N];
	volatile int m_headJU;
	volatile int m_tailJU;

	void bfmeClear()
	{
		m_headJU = 0;
		m_tailJU = 0;

		int *cells = m_cellsJU;

		memset(cells, 0, (N - 1) * 4);

		cells[N - 1] = 0;
	}
};

class Rva009A45A0CollisionData
{
public:
	Rva009A45A0CollisionData();

	volatile int m_bfme00JU;
	volatile int m_bfme04JU;
	volatile int m_bfme08JU;
	volatile int m_bfme0cJU;
	volatile int m_bfme10JU;
	volatile int m_bfme14JU;
	Rva009A45A0Bucket<0x2b7c> m_bfmeB1JU;
	Rva009A45A0Bucket<0x494> m_bfmeB2JU;
	volatile int m_bfmeC068JU;
	volatile char m_bfmeC06cJU;
	volatile char m_bfmeC06dJU;
	unsigned char m_bfmePadJU[2];
};

Rva009A45A0CollisionData::Rva009A45A0CollisionData()
{
	m_bfme00JU = 0;
	m_bfme04JU = 0;
	m_bfme08JU = 0;

	m_bfmeB1JU.bfmeClear();
	m_bfmeB2JU.bfmeClear();

	m_bfmeC06cJU = 0;
	m_bfmeC06dJU = 0;
	m_bfmeC068JU = 3;
	m_bfme0cJU = 0;
	m_bfme10JU = 0;
	m_bfme14JU = 0;
}
