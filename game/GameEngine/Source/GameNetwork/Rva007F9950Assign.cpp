// cl: /O2 /DNDEBUG /MD /EHsc
//
// 0x007F9950 (81 bytes) sat in an unclaimed gap: 16-byte-aligned start after
// an int3 pad run, ret 4 followed by int3 padding, and no call, ILT stub,
// table slot, code immediate, pin or dir32 name at the address.  It copies the
// dwords at +4 .. +0x2C and the byte at +0x30 from its argument into `this`,
// leaves +0 alone and returns `this`: the memberwise copy assignment of a
// polymorphic class (the vptr at +0 is never assigned).  An earlier banked
// attempt spelled it as a void copy and stopped at 0.85; returning *this is
// what puts `mov eax,ecx` first.
//
// IDENTITY IS NOT RECOVERED.  The class keeps the banked attempt's
// address-derived name.

class Rva007F9950Struct
{
public:
	virtual void slot();

	Rva007F9950Struct &operator=( const Rva007F9950Struct &other );

	int m_04;
	int m_08;
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	unsigned char m_30;
};

Rva007F9950Struct &Rva007F9950Struct::operator=( const Rva007F9950Struct &other )
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_c = other.m_c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	m_30 = other.m_30;
	return *this;
}
