// ?evaluateSpline@U4Curve006095D0@@QBEMM@Z
// partial score=0.9 date=2026-09-06
// cl: /EHs-c-

extern const float g_bfmeK1266A;

struct Rva00069DF0Element
{
	float time;
	float value;
	float tangentIn;
	float tangentOut;
};

typedef Rva00069DF0Element U4CurveKey006095D0;

struct U4CurveKeyRange006095D0
{
	U4CurveKey006095D0 *begin;
	U4CurveKey006095D0 *end;
	char m_pad08[ 5 ];
	unsigned char flag;
	char m_pad0E[ 2 ];
};

extern U4CurveKey006095D0 *Rva00069DF0UpperBound(
	U4CurveKey006095D0 *, U4CurveKey006095D0 *,
	const U4CurveKey006095D0 &);

class U4Curve006095D0
{
public:
	float evaluateSpline( float t ) const;

	int m_before;
	int m_after;
	U4CurveKeyRange006095D0 m_keys;
	mutable U4CurveKey006095D0 *m_current;
	mutable float m_coefficientA;
	mutable float m_coefficientB;
	mutable float m_coefficientC;
	mutable float m_coefficientD;
};

float U4Curve006095D0::evaluateSpline( float t ) const
{
	U4CurveKey006095D0 *end = m_keys.end;
	U4CurveKey006095D0 *next = m_current + 1;
	U4CurveKey006095D0 *current =
		*reinterpret_cast<U4CurveKey006095D0 * volatile *>(&m_current);
	if ( current == end || t < current->time || next == end ||
		t >= next->time )
	{
		typedef U4CurveKey006095D0 *(*UpperBoundCall)(
			U4CurveKey006095D0 *, U4CurveKey006095D0 *,
			const U4CurveKey006095D0 &, int, int);
		UpperBoundCall upperBound = (UpperBoundCall)Rva00069DF0UpperBound;
		const U4CurveKey006095D0 &key =
			*reinterpret_cast<const U4CurveKey006095D0 *>(&t);
		U4CurveKey006095D0 *found = upperBound(
			m_keys.begin, end, key, m_keys.flag, 0 );
		if ( found == end )
		{
			next = end - 1;
			current = next - 1;
		}
		else
		{
			next = found;
			current = next - 1;
		}
		m_current = current;
	}

	volatile float delta = next->time - current->time;
	float leftValue = current->value;
	float leftTangent = delta * current->tangentOut;
	float rightValue = next->value;
	float rightTangent = delta * next->tangentIn;
	m_coefficientA = leftValue + leftValue - rightValue - rightValue
		+ leftTangent + rightTangent;
	m_coefficientB = (rightValue - leftValue) * g_bfmeK1266A
		- leftTangent - leftTangent - rightTangent;
	m_coefficientC = leftTangent;
	m_coefficientD = leftValue;

	current = *reinterpret_cast<U4CurveKey006095D0 * volatile *>(&m_current);
	float u = (t - current->time) /
		(next->time - current->time);
	return (((u * m_coefficientA + m_coefficientB) * u
		+ m_coefficientC) * u + m_coefficientD);
}
