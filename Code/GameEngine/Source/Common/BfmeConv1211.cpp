// Open-BFME5 conversions.

class BfmeG1211
{
public:
	void bfmeStep1211C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1211 *g_bfme1211;

extern "C" void bfmeStep1211A(int *a, void *b);
extern "C" void bfmeStep1211B(int *a, void *b);

void bfmeGo1211(int *a, void *b)
{
	BfmeG1211 *g;

	bfmeStep1211A(a, b);
	bfmeStep1211B(a, b);
	g = g_bfme1211;
	if (g->m_bfme04 && *a == 0)
		g->bfmeStep1211C();
}
