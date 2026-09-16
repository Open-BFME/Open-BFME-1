// ??0Rva009A45A0CollisionData@@QAE@XZ
// partial score=0.97 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc
//
// Rva009A45A0CollisionData::Rva009A45A0CollisionData, retail 0x009A45A0,
// 117 bytes. CollisionManager::CollisionManager at 0x009A25B0 calls it, and
// the 460-byte body at 0x009A2750 merges the buckets at +0x0C and +0xC068.
// The product class name is not recovered, so the address stays in the name.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

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
	int m_bfmeA1JU[0x2b7c];
	volatile int m_bfmeAe08JU;
	volatile int m_bfmeAe0cJU;
	int m_bfmeA2JU[0x494];
	volatile int m_bfmeC060JU;
	volatile int m_bfmeC064JU;
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
	m_bfmeAe08JU = 0;
	m_bfmeAe0cJU = 0;

	_ReadWriteBarrier();

	int *a1 = m_bfmeA1JU;

	memset(a1, 0, 0x2b7b * 4);

	a1[0x2b7b] = 0;
	m_bfmeC060JU = 0;
	m_bfmeC064JU = 0;

	int *a2 = m_bfmeA2JU;

	memset(a2, 0, 0x493 * 4);

	a2[0x493] = 0;
	m_bfmeC06cJU = 0;
	m_bfmeC06dJU = 0;
	m_bfmeC068JU = 3;
	m_bfme0cJU = 0;
	m_bfme10JU = 0;
	m_bfme14JU = 0;
}
