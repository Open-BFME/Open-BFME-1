// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Rva007A0290::scale, retail 0x007A0290, 93 bytes on d_00770ed0.
// Unrolled *= of nine floats at this+0..+0x20 by the stack float arg.
// Returns this so MSVC keeps eax as the member base (retail mov eax,ecx).

class Rva007A0290
{
public:
	Rva007A0290 *scale( float s );

private:
	float m_v[ 9 ];
};

// ?scale@Rva007A0290@@QAEPAV1@M@Z
Rva007A0290 *Rva007A0290::scale( float s )
{
	m_v[ 0 ] *= s;
	m_v[ 1 ] *= s;
	m_v[ 2 ] *= s;
	m_v[ 3 ] *= s;
	m_v[ 4 ] *= s;
	m_v[ 5 ] *= s;
	m_v[ 6 ] *= s;
	m_v[ 7 ] *= s;
	m_v[ 8 ] *= s;
	return this;
}
