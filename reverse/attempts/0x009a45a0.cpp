// ??0BfmeBigJU@@QAE@XZ
// partial score=0.95 date=2026-09-08
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class Rva009A45A0CollisionData
{
public:
	Rva009A45A0CollisionData();

	volatile int m_bfme00JU;
	volatile int m_bfme04JU;
	volatile int m_bfme08JU;
	int m_bfme0cJU;
	int m_bfme10JU;
	int m_bfme14JU;
	int m_bfmeA1JU[0x2b7c];
	volatile int m_bfmeAe08JU;
	volatile int m_bfmeAe0cJU;
	int m_bfmeA2JU[0x494];
	int m_bfmeC060JU;
	int m_bfmeC064JU;
	int m_bfmeC068JU;
	char m_bfmeC06cJU;
	char m_bfmeC06dJU;
	unsigned char m_bfmePadJU[2];
};

Rva009A45A0CollisionData::Rva009A45A0CollisionData()
{
	m_bfme00JU = 0;
	m_bfme04JU = 0;
	m_bfme08JU = 0;
	m_bfmeAe08JU = 0;
	m_bfmeAe0cJU = 0;

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
