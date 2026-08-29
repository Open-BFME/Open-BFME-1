// Open-BFME5 conversions.

extern "C" double __cdecl bfmeCall1128A(int);
extern "C" double __cdecl bfmeCall1128B(int);

struct BfmeS1128
{
	int m_bfme00;
};

void bfmeGo1128A(BfmeS1128 *a, float *out)
{
	int v = a->m_bfme00;

	*out = (float)bfmeCall1128A(v);
}

void bfmeGo1128B(BfmeS1128 *a, double *out)
{
	int v = a->m_bfme00;

	*out = bfmeCall1128A(v);
}

void bfmeGo1128C(BfmeS1128 *a, double *out)
{
	int v = a->m_bfme00;

	*out = bfmeCall1128B(v);
}
