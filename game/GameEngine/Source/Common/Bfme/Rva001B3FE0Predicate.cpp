// Structural BFME recovery, retail 0x001B3FE0 (41 bytes).
//
// The 0x00006DCF ILT thunk is called by Object::canCrushOrSquish with the
// Object receiver in ecx.  Retail first checks Object+0x04, then follows the
// independently observed Object+0x10 pointer, selecting its nested +0x08
// object when present and testing the resulting +0x20 value.  The method
// remains address-derived because its original semantic name is unrecovered.

struct Rva001B3FE0Nested
{
	unsigned char m_pad0[8];
	Rva001B3FE0Nested *m_child;
	unsigned char m_pad1[0x14];
	int m_value;
};

class Rva001B3FE0
{
public:
	bool test() const;

private:
	unsigned char m_vtable[4];
	void *m_guard;
	unsigned char m_pad0[8];
	Rva001B3FE0Nested *m_nested;
};

bool Rva001B3FE0::test() const
{
	if ( !m_guard )
		return false;

	Rva001B3FE0Nested *nested = m_nested;
	if ( !nested )
		return false;

	Rva001B3FE0Nested *child = nested->m_child;
	if ( !child )
		child = nested;

	return child->m_value != 0x7FFFFFFF;
}
