// cl: /EHs-c- /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// This body evaluates the cached segment in U4Curve006095D0. The matched
// evaluate(int) overload, the two blend callers, and retail RVA 0x0006A400
// identify the class and method.

#include "wwmath.h"

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
	float evaluate( int t ) const;
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
		m_coefficientB = (rightValue - leftValue) * 3.0f
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

// Retail 0x0006A520 (611 B plus two five-entry case tables, 652 B): the
// keyed curve evaluator, reached through ILT 0x00038EBF (pinned name, whose
// matched blend callers pass the time as this int-typed argument; the body
// reads it as a float and rewrites it in place). Before/after-range modes
// 0..4 are constant, linear, cycle, cycle-with-offset and oscillate.
// Retail CSEs (float)cycle and (float)cycle * range into stack slots: naming
// either as a local flips the x87 operand order of the products that use it.
float U4Curve006095D0::evaluate( int t ) const
{
	float &time = *(float *)&t;
	Rva00069DF0Element *first = m_keys.begin;
	if ( first == m_keys.end )
		return 0.0f;

	float firstTime = first->time;
	Rva00069DF0Element *last = m_keys.end - 1;
	if ( first == last )
	{
		if ( time < firstTime )
		{
			if ( m_before == 1 )
				return ( time - firstTime ) * first->tangentIn + first->value;
			return first->value;
		}
		if ( time > firstTime && m_after == 1 )
			return ( time - firstTime ) * first->tangentOut + first->value;
		return first->value;
	}

	float lastTime = last->time;
	if ( time < firstTime || time >= lastTime )
	{
		float range = lastTime - firstTime;
		float cycleReal = (float)floor( ( time - firstTime ) / range );
		int cycle = WWMath::Float_To_Long( cycleReal );
		time -= (float)cycle * range;
		if ( cycle < 0 )
		{
			switch ( m_before )
			{
				case 0:
					return first->value;
				case 1:
					return ( time + (float)cycle * range - firstTime ) * first->tangentIn + first->value;
				case 2:
					return evaluateSpline( time );
				case 3:
				{
					float base = first->value;
					float delta = last->value - base;
					return evaluateSpline( time ) + (float)cycle * delta + base;
				}
				case 4:
					if ( time != firstTime && ( cycle & 1 ) )
						return evaluateSpline( lastTime - time );
					return evaluateSpline( time );
			}
		}
		else if ( cycle > 0 )
		{
			switch ( m_after )
			{
				case 0:
					return last->value;
				case 1:
					return ( (float)( cycle - 1 ) * range + time - firstTime ) * last->tangentOut + last->value;
				case 2:
					return evaluateSpline( time );
				case 3:
				{
					float base = last->value;
					float delta = base - first->value;
					return evaluateSpline( time ) + (float)cycle * delta + base;
				}
				case 4:
					if ( time != firstTime && ( cycle & 1 ) )
						return evaluateSpline( lastTime - time );
					return evaluateSpline( time );
			}
		}
	}
	return evaluateSpline( time );
}
