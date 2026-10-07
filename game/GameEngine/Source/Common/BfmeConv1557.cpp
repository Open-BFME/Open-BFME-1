// Open-BFME5 conversions.

// ILT 0x08FCB -> 0x002E0D70, matched
// ?gen002E0D70@@YAXPAXPAUGen002E0D70Rec@@H0@Z (Gen002E0D70.cpp).
struct Gen002E0D70Rec;
void gen002E0D70(void *a, Gen002E0D70Rec *b, int n, void *c);
static inline void bfmeStepVOZ(void *a, void *b, int n, void *c) { gen002E0D70(a, (Gen002E0D70Rec *)b, n, c); }

void bfmeSortVOZ(void *a, void *b, void *c)
{
	char *p = (char *)b;
	int d = (int)(p - (char *)a);

	while (d / 12 > 1)
	{
		bfmeStepVOZ(a, p, 0, c);
		d -= 12;
		p -= 12;
	}
}
