// Open-BFME5 conversions.

struct BfmeS1209
{
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

extern "C" __declspec(dllimport) void __cdecl bfmeNotify1209(void *a);

class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *a);
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

void BfmeA1209::bfmeOp1209(const BfmeS1209 *a)
{
	m_bfme00 = a->m_bfme00 * m_bfme00;
	m_bfme04 = a->m_bfme04 * m_bfme04;
	m_bfme08 = a->m_bfme08 * m_bfme08;
	m_bfme0c = a->m_bfme0c * m_bfme0c;
	m_bfme10 = a->m_bfme10 + m_bfme10;
	m_bfme14 = a->m_bfme14 + m_bfme14;
	m_bfme18 = a->m_bfme18 + m_bfme18;
	m_bfme1c = a->m_bfme1c + m_bfme1c;
	bfmeNotify1209(this);
}
