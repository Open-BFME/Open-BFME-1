// ?rva0090FE40ExtractReset@@YAXPAURva0090FE40Pair@@0@Z
// Address-derived: save *src into *dest, then reset *src in place: if
// src->x == BfmeZeroRange, set src->x = 1.0f; otherwise set src->x = 0.0f and
// src->y = g_bfmeDefaultBU - src->y.
typedef float Real;
extern const Real BfmeZeroRange;
extern float g_bfmeDefaultBU;

struct Rva0090FE40Pair
{
	float x;
	float y;
};

void rva0090FE40ExtractReset(Rva0090FE40Pair* dest, Rva0090FE40Pair* src)
{
	Real zeroConst = BfmeZeroRange;
	*dest = *src;

	if (src->x != zeroConst)
	{
		src->y = g_bfmeDefaultBU - src->y;
		src->x = 0.0f;
		return;
	}

	src->x = 1.0f;
}
