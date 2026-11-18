// cl: /DNDEBUG /MD
// BFME retail 0x00730E20 (48 bytes, ret 0x10): a vtable slot (ILT 0x000212DD)
// that forwards a 12-byte value and a float to the owner at +0x10 when it is
// set. The callee is the matched Rva006CB1E0Owner::scan (0x006CB1E0, ILT
// 0x00019C7C).
//
// Retail copies the value field by field through EDX after pushing the float,
// which is what MSVC emits for a by-value argument whose type has a
// user-declared copy constructor (as WWMath's Vector3 does); a trivially
// copyable struct is copied with a different register order.

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"

struct Rva006CB1E0Value
{
	Rva006CB1E0Value(const Rva006CB1E0Value &other) : x(other.x), y(other.y), z(other.z) {}

	Real x;
	Real y;
	Real z;
};

class Rva006CB1E0Owner
{
public:
	void scan(Rva006CB1E0Value value, Real tail);
};

class Gen_00730e20
{
public:
	void forward(Rva006CB1E0Value value, Real tail);

private:
	unsigned char m_pad[0x10];
	Rva006CB1E0Owner *m_target;		// +0x10
};

void Gen_00730e20::forward(Rva006CB1E0Value value, Real tail)
{
	if (m_target)
		m_target->scan(value, tail);
}
