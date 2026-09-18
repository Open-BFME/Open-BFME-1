// ?method@Rva006E1BE0@@UBEMMMM@Z
// partial score=0.93 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc
//
// Identity review: the exact constructor 0x006E2310 and destructor
// 0x006E2480 install vtable 0x0111E250, whose slot 16 reaches 0x006E1BE0
// through thunk 0x0002B53F.  No caller, literal, or layout witness recovers
// the original method spelling, so this is an address-derived opaque virtual
// member rather than the prior free __stdcall claim.

struct Rva006E1BE0Vec4
{
	float x;
	float y;
	float z;
	float w;
};

#define g_bfmeDefault006e1be0 (*(float *)0x0111E238)
#define g_bfmeObj006e1be0 (*(char * volatile *)0x012F8048)

class Rva006E1BE0
{
public:
	virtual float method(float x, float y, float z) const;
};

float Rva006E1BE0::method(float x, float y, float z) const
{
	char *object = g_bfmeObj006e1be0;
	float result = g_bfmeDefault006e1be0;
	if (object)
	{
		const int offset = 0x84;
		Rva006E1BE0Vec4 row = *(Rva006E1BE0Vec4 *)(object + offset);
		result = row.z * z;
		result += row.y * y;
		result += row.x * x;
		result += row.w;
	}
	return result;
}
