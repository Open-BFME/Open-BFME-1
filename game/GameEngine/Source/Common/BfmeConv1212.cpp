// Open-BFME5 conversions.

class BfmeG1212
{
public:
	void bfmeStep1212C();
	int m_bfme00;
	int m_bfme04;
};

extern BfmeG1212 *g_bfme1212;

extern "C" void bfmeStep1212A(int *a, void *b);
extern "C" void bfmeStep1212B(int *a, void *b);

void bfmeGo1212(int *a, void *b)
{
	BfmeG1212 *g;

	bfmeStep1212A(a, b);
	bfmeStep1212B(a, b);
	g = g_bfme1212;
	if (g->m_bfme04 && *a == 0)
		g->bfmeStep1212C();
}
