// ?evaluate@U4Curve006095D0@@QBEMH@Z
// partial score=0.63 date=2026-09-09
// cl: /EHs-c-
//
// Three unrelated small bodies from the 0x005E97B0..0x0060D680 slice, each
// decided by its own bytes plus one pinned callee.
//
// 0x0060D680 (39 bytes) -- a copy constructor with a base and three members:
//
//     push esi / push edi / mov edi,[esp+0xC] / push edi / mov esi,ecx
//     call 0x00094900
//     mov eax,[edi+0x0C] / mov [esi+0x0C],eax
//     mov ecx,[edi+0x10] / mov [esi+0x10],ecx
//     mov edx,[edi+0x14] / pop edi / mov [esi+0x14],edx
//     mov eax,esi / pop esi / ret 4
//
// The argument is pushed UNADJUSTED to the callee and then read at 0x0C, 0x10
// and 0x14 -- a copy constructor over its own class, with the base subobject at
// offset 0.  NO VFTABLE STORE SURVIVES, and a polymorphic class always stamps
// its own in its constructor, so neither this class nor its base carries a
// vptr.  The first copied member is at 0x0C, so the base occupies 0..0x0B.
//
// 0x005F0D40 (50 bytes) -- reference-counted hand-over:
//
//     mov edi,[esp+0xC] / mov eax,[edi] / test eax,eax / mov esi,ecx / je S
//     inc word ptr [eax+4]
//   S: mov ecx,[esi+0x14] / test ecx,ecx / je L / call 0x009EB7A0
//     mov eax,[edi] / mov [esi+0x14],eax / ret 4
//   L: mov ecx,[edi] / mov [esi+0x14],ecx / ret 4
//
// A SIXTEEN-BIT increment at +4 of the pointed-at object, guarded by a null
// test, then a no-argument __thiscall on the receiver's own +0x14 slot, also
// null-guarded, and only then the store.  Retain-before-release with a 16-bit
// counter.  THE SOURCE POINTER IS RE-READ AFTER THE CALL -- retail loads
// `[edi]` again on the path that called, and reuses the register on the path
// that did not.  That is the compiler refusing to keep a value across an opaque
// call that might have written through it, and it is why the argument is a
// reference to a struct holding the pointer rather than the pointer itself: a
// by-value pointer parameter lives in the caller's frame and would not need
// re-reading.
//
// 0x006095D0 (30 bytes) -- a linear blend:
//
//     mov eax,[esp+0xC] / push eax / add ecx,0x18 / call 0x0006A520
//     fld [esp+8] / fsub [esp+4] / fmulp st(1) / fadd [esp+4] / ret 0xC
//
// `add ecx,0x18` with no null guard is a member subobject, not a base
// conversion, and the callee leaves its result on the x87 stack: a float-valued
// __thiscall on a member at +0x18 taking the third argument.  The arithmetic
// that follows is `(arg2 - arg1) * result + arg1` with arg1 read twice, which
// is `lo + (hi - lo) * f(t)` -- written the other way round (`lo * (1 - k) + hi
// * k`) it needs a load of 1.0f and two multiplies.  `ret 0xC` with the first
// two slots read as floats fixes the parameter list at (float, float, dword).
//
// IDENTITY IS NOT RECOVERED.  All three callees are pinned by the addresses
// their REL32s resolve to and carry address-derived names; `char m_pad[]`
// carries an offset and nothing else.

class U4Base00094900
{
public:
	U4Base00094900( const U4Base00094900 &other );
	int m_f00;
	int m_f04;
	int m_f08;
};
class U4Ctor0060D680 : public U4Base00094900
{
public:
	U4Ctor0060D680( const U4Ctor0060D680 &other );
	int m_f0C;
	int m_f10;
	int m_f14;
};
U4Ctor0060D680::U4Ctor0060D680( const U4Ctor0060D680 &other )
	: U4Base00094900( other ),
	  m_f0C( other.m_f0C ),
	  m_f10( other.m_f10 ),
	  m_f14( other.m_f14 )
{
}

class U4Counted005F0D40
{
public:
	void release( void );
	int m_f00;
	unsigned short m_count;
};
struct U4Handle005F0D40
{
	U4Counted005F0D40 *m_target;
};
class U4Holder005F0D40
{
public:
	void assign( const U4Handle005F0D40 &handle );
	char m_pad[ 0x14 ];
	U4Counted005F0D40 *m_held;
};
void U4Holder005F0D40::assign( const U4Handle005F0D40 &handle )
{
	if ( handle.m_target != 0 )
		++handle.m_target->m_count;
	if ( m_held != 0 )
		m_held->release();
	m_held = handle.m_target;
}

extern "C" __declspec(dllimport) double BfmeFloorER( double value );

__forceinline long BfmeFistp006095D0( float value )
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct U4CurveKey006095D0
{
	float time;
	float value;
	float tangentIn;
	float tangentOut;
};

struct U4CurveKeyRange006095D0
{
	U4CurveKey006095D0 *begin;
	U4CurveKey006095D0 *end;
	char pad[ 8 ];
};

class U4Curve006095D0
{
public:
	float evaluate( int t ) const;
	float evaluateSpline( float t ) const;

	int m_before;
	int m_after;
	U4CurveKeyRange006095D0 m_keys;
	int m_field14;
	mutable U4CurveKey006095D0 *m_current;
	mutable float m_coefficientA;
	mutable float m_coefficientB;
	mutable float m_coefficientC;
	mutable float m_coefficientD;
};

extern const float BfmeZeroRange;

#pragma comment(linker, "/alternatename:?evaluateSpline@U4Curve006095D0@@QBEMM@Z=?j_00005fce@@YAXXZ")

float U4Curve006095D0::evaluate( int t ) const
{
	float &time = *(float *)&t;
	U4CurveKey006095D0 *finish = m_keys.end;
	U4CurveKey006095D0 *start = m_keys.begin;
	if( start == finish )
		return BfmeZeroRange;

	float firstTime = start->time;
	U4CurveKey006095D0 *last = finish - 1;
	if( start == last )
	{
		if( time < firstTime )
		{
			if( m_before == 1 )
				return start->value + ( time - firstTime ) * start->tangentIn;
			return start->value;
		}
		if( time <= firstTime )
			return start->value;
		if( m_after != 1 )
			return start->value;
		return start->value + ( time - firstTime ) * start->tangentOut;
	}

	float lastTime = last->time;
	if( time < firstTime )
		goto normalize;
	if( time >= lastTime )
		goto normalize;
	goto raw_spline;

	normalize:
	float span = lastTime - firstTime;
	int cycle = (int)BfmeFistp006095D0(
		(float)BfmeFloorER( (double)(( time - firstTime ) / span) ) );
	time -= (float)cycle * span;
	if( cycle < 0 )
	{
		switch( m_before )
		{
			case 0:
				return start->value;
			case 1:
				return start->value +
					( time + (float)cycle * span - firstTime ) *
					start->tangentIn;
			case 2:
				return evaluateSpline( time );
			case 3:
				return evaluateSpline( time ) +
					(float)cycle * ( last->value - start->value );
			case 4:
				if( time == firstTime || !( cycle & 1 ) )
					return evaluateSpline( time );
				return evaluateSpline( lastTime - time );
		}
	}
	else
	{
		switch( m_after )
		{
			case 0:
				return last->value;
			case 1:
				return last->value +
					( (float)( cycle - 1 ) * span + time - firstTime ) *
					last->tangentOut;
			case 2:
				return evaluateSpline( time );
			case 3:
				return evaluateSpline( time ) +
					(float)cycle * ( last->value - start->value );
			case 4:
				if( time == firstTime || !( cycle & 1 ) )
					return evaluateSpline( time );
				return evaluateSpline( lastTime - time );
		}
	}
raw_spline:
	return evaluateSpline( *(float *)&t );
}
struct U4Blend006095D0
{
	char m_pad[ 0x18 ];
	U4Curve006095D0 m_curve;
	float blend( float lo, float hi, int t ) const;
};
float U4Blend006095D0::blend( float lo, float hi, int t ) const
{
	return lo + ( hi - lo ) * m_curve.evaluate( t );
}
