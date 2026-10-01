// ?rva00880AF0@Rva00880AF0@@QBE_NPBV1@@Z
// partial score=0.7365 date=2026-10-01
// RVA 0x00880AF0: independently bounded 296-byte thiscall float predicate.
// Historical bank's BfmeBoxF0::intersects is an unwitnessed private spelling.
// This address-derived borrowed view names no native owner or lifetime.
// Eight consecutive float words are accessed; the declared transport view
// does not establish native complete object size or field declarations.
// Source bool models the witnessed AL predicate result; caller storage must
// permit every observed float access. No constructor, destructor or parent.
// Inline dot utilities are pure local arithmetic, not aliases of retail callees.
// cl: /DNDEBUG /MD /EHsc
typedef float Real;

class Rva00880AF0
{
public:
 bool rva00880AF0(const Rva00880AF0 *other) const;
 float values[8];
};

#include <math.h>
#pragma intrinsic(fabs)

__forceinline float Rva00880AF0DotArray(const float *a, const float *b)
{
 return a[0]*b[0] + a[1]*b[1];
}

bool Rva00880AF0::rva00880AF0(const Rva00880AF0 *other) const
{
	Real coefficients[4];
	Real delta[2];
	delta[1] = other->values[1];
	delta[0] = other->values[0] - values[0];
	delta[1] -= values[1];

	coefficients[0] = (Real)fabs(Rva00880AF0DotArray(other->values+2, values+2));
	coefficients[1] = (Real)fabs(Rva00880AF0DotArray(other->values+4, values+2));
	if ((Real)fabs(delta[1] * values[3] + delta[0] * values[2]) >
		coefficients[1] * other->values[7] + coefficients[0] * other->values[6] + values[6])
		return false;

	coefficients[2] = (Real)fabs(Rva00880AF0DotArray(other->values+2, values+4));
	coefficients[3] = (Real)fabs(Rva00880AF0DotArray(other->values+4, values+4));
	if ((Real)fabs(delta[1] * values[5] + delta[0] * values[4]) >
		coefficients[3] * other->values[7] + coefficients[2] * other->values[6] + values[7])
		return false;

	if ((Real)fabs(delta[1] * other->values[3] + delta[0] * other->values[2]) >
		coefficients[0] * values[6] + coefficients[2] * values[7] + other->values[6])
		return false;

	if ((Real)fabs(delta[1] * other->values[5] + delta[0] * other->values[4]) >
		coefficients[1] * values[6] + coefficients[3] * values[7] + other->values[7])
		return false;

	return true;
}
