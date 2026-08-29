// cl: /Od
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeSwapC1151(int *a, int *b);

class BfmeA1151
{
public:
	void bfmeSwap1151(BfmeA1151 *o);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

void BfmeA1151::bfmeSwap1151(BfmeA1151 *o)
{
	int n1;
	int n4;
	int *n3;
	int *n2;

	n1 = m_bfme00;
	m_bfme00 = o->m_bfme00;
	o->m_bfme00 = n1;

	n3 = &o->m_bfme04;
	n2 = &m_bfme04;
	n4 = *n2;
	*n2 = *n3;
	*n3 = n4;

	bfmeSwapC1151(&m_bfme08, &o->m_bfme08);
}
