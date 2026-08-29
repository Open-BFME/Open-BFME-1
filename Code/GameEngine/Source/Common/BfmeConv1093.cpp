// Open-BFME5 conversions.

class BfmeR1093
{
public:
	char bfmeHas1093(int a);
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeD1093
{
public:
	BfmeR1093 *bfmeLook1093(short *h);
};

class BfmeP1093
{
public:
	int bfmeNext1093(int a);
};

extern BfmeD1093 *g_bfmeD1093;
extern BfmeP1093 *g_bfmeP1093;

char __stdcall bfmeGo1093A(int a, int b)
{
	int h;

	a = g_bfmeP1093->bfmeNext1093(a);
	h = g_bfmeP1093->bfmeNext1093(b);
	while ((short)a) {
		BfmeR1093 *r = g_bfmeD1093->bfmeLook1093((short *)&a);

		if (r) {
			b = h;
			while ((short)b) {
				BfmeR1093 *q = g_bfmeD1093->bfmeLook1093((short *)&b);

				if (q) {
					int m = q->m_bfme24;

					if (r->bfmeHas1093(m))
						return 1;
				}
			}
		}
	}
	return 0;
}
