// cl: /EHs-c-
//
// This body evaluates the cached segment in U4Curve006095D0. The matched
// evaluate(int) overload, the two blend callers, and retail RVA 0x0006A400
// identify the class and method.

extern const float g_bfmeK1266A;

struct Rva00069DF0Element
{
	float time;
	float value;
	float tangentIn;
	float tangentOut;
};

struct U4CurveKeyRange006095D0
{
	Rva00069DF0Element *begin;
	Rva00069DF0Element *end;
	char m_pad08[ 5 ];
	unsigned char flag;
	char m_pad0E[ 2 ];
};

extern void j_000023e2();

class U4Curve006095D0
{
public:
	float evaluateSpline( float t ) const;

	int m_before;
	int m_after;
	U4CurveKeyRange006095D0 m_keys;
	mutable Rva00069DF0Element * volatile m_current;
	mutable float m_coefficientA;
	mutable float m_coefficientB;
	mutable float m_coefficientC;
	mutable float m_coefficientD;
};

float U4Curve006095D0::evaluateSpline( float t ) const
{
	Rva00069DF0Element *end = m_keys.end;
	Rva00069DF0Element *next = m_current + 1;
	Rva00069DF0Element *current = m_current;
	if ( current == end || t < current->time || next == end ||
		t >= next->time )
	{
		typedef Rva00069DF0Element *(*UpperBoundCall)(
			Rva00069DF0Element *, Rva00069DF0Element *,
			const Rva00069DF0Element &, int, int);
		UpperBoundCall upperBound = (UpperBoundCall)j_000023e2;
		const Rva00069DF0Element &key =
			*reinterpret_cast<const Rva00069DF0Element *>(&t);
		U4CurveKeyRange006095D0 *keys =
			reinterpret_cast<U4CurveKeyRange006095D0 *>(
				(reinterpret_cast<char *>(const_cast<U4Curve006095D0 *>(this))) + 8);
		unsigned char *flag = keys ? &keys->flag : 0;
		next = upperBound(
			keys->begin, keys->end, key, *flag, 0 );
		if ( next == end )
			next = end - 1;
		current = next - 1;
		m_current = current;

		volatile float delta = next->time - current->time;
		float leftValue = current->value;
		float leftTangent = delta * current->tangentOut;
		float rightValue = next->value;
		float rightTangent = delta * next->tangentIn;
		m_coefficientA = (leftValue - rightValue) +
			(leftValue - rightValue) + leftTangent + rightTangent;
		m_coefficientB = (rightValue - leftValue) * g_bfmeK1266A
			- (leftTangent + leftTangent) - rightTangent;
		m_coefficientC = leftTangent;
		m_coefficientD = leftValue;
	}

	current = m_current;
	float currentTime = current->time;
	float u = (t - currentTime) / (next->time - currentTime);
	return (((u * m_coefficientA + m_coefficientB) * u
		+ m_coefficientC) * u + m_coefficientD);
}
