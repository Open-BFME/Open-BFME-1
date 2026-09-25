// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x002324A0, 90 bytes through the int3 run at +0x5A (`ret 8`, both
// arguments read from the stack).  Nothing calls it or its ILT 0x0003D8CA
// directly, so the names keep the address.  It reports whether b lies strictly
// inside the radius a reaches through +0x204 -> +0x1CC -> +0x38, measured in
// the plane of the floats at +0x38/+0x3C.  The null exit returns 8-bit and
// the compare a 32-bit 0/1, hence the split return arms.

struct Rva002324A0Radius
{
	char m_unmodelled00[ 0x38 ];
	float m_radius38;
};

struct Rva002324A0Info
{
	char m_unmodelled00[ 0x1CC ];
	Rva002324A0Radius *m_radius1CC;
};

struct Rva002324A0Thing
{
	char m_unmodelled00[ 0x38 ];
	float m_x38;
	float m_y3C;
	char m_unmodelled40[ 0x204 - 0x40 ];
	Rva002324A0Info *m_info204;
};

class Rva002324A0Owner
{
public:
	bool test( const Rva002324A0Thing *a, const Rva002324A0Thing *b );
};

bool Rva002324A0Owner::test( const Rva002324A0Thing *a, const Rva002324A0Thing *b )
{
	float dx = a->m_x38 - b->m_x38;
	float dy = a->m_y3C - b->m_y3C;
	Rva002324A0Info *info = a->m_info204;
	if( !info )
		return false;
	float r = info->m_radius1CC->m_radius38;
	return dx * dx + dy * dy < r * r;
}
