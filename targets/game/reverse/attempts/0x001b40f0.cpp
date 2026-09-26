// ?rva001B40F0Formula@@YAMMMM@Z
// partial score=0.85 date=2026-09-06
// ?rva001B40F0Formula@@YAMMMM@Z
typedef float Real;
extern const Real BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern const Real g_bfmeK1253;
extern float g_bfmeK2SMA;

Real rva001B40F0Formula(Real a, Real b, Real c)
{
	Real diff = a - b;
	if (diff <= BfmeZeroRange)
		return BfmeZeroRange;

	Real q = c;
	q /= diff;
	Real sum = c + g_bfmeDefaultBU;
	return (q * g_bfmeK1253 + b) * sum * g_bfmeK2SMA;
}
