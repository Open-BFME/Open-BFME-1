// Address-derived cdecl float helper at retail 0x001B40F0 (63 bytes).
// diff = a - b; non-positive diff returns g_rva01075350, otherwise
// (diff * 0.5 + b) * (diff / c + 1) * g_bfmeK2SMA. The half is a pooled
// literal (retail reads it from 0x0107533C); a named extern const would keep
// diff live on the x87 stack instead of retail's fxch/fmul-mem pair.

typedef float Real;

extern const Real g_rva01075350;	// retail 0x01075350, 0.0f
extern float g_bfmeDefaultBU;		// retail 0x01075334, 1.0f
float g_bfmeK2SMA = 1.05f;		// retail 0x0109D11C: 66 66 86 3F

Real rva001B40F0Formula(Real a, Real b, Real c)
{
	Real diff = a - b;
	if (diff <= g_rva01075350)
		return g_rva01075350;
	return (diff * 0.5f + b) * (diff / c + g_bfmeDefaultBU) * g_bfmeK2SMA;
}
