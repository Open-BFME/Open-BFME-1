// ??0Rva009A45A0CollisionData@@QAE@XZ
// partial score=0.8 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)

class Rva009A45A0CollisionData
{
public:
	Rva009A45A0CollisionData();

private:
	struct TripleZero
	{
		TripleZero() : first(0), second(0), third(0) {}
		unsigned int first;
		unsigned int second;
		unsigned int third;
	};
	struct PairZero
	{
		PairZero() : first(0), second(0) {}
		unsigned int first;
		unsigned int second;
	};

	TripleZero m_firstThree;
	unsigned int m_000c;
	unsigned int m_0010;
	unsigned int m_0014;
	unsigned int m_first[0x2b7c];
	PairZero m_ae08;
	unsigned int m_second[0x494];
	unsigned int m_c060;
	unsigned int m_c064;
	unsigned int m_c068;
	unsigned char m_c06c;
	unsigned char m_c06d;
	unsigned char m_c06e[2];
};

Rva009A45A0CollisionData::Rva009A45A0CollisionData()
{
	unsigned int *first = m_first;
	memset(first, 0, sizeof(m_first) - sizeof(*first));
	first[0x2b7b] = 0;
	m_c060 = 0;
	m_c064 = 0;

	unsigned int *second = m_second;
	memset(second, 0, sizeof(m_second) - sizeof(*second));
	second[0x493] = 0;
	m_c06c = 0;
	m_c06d = 0;
	m_c068 = 3;
	m_000c = 0;
	m_0010 = 0;
	m_0014 = 0;
}
