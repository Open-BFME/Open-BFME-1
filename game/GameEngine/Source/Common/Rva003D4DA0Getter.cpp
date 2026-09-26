// cl: /O2 /Ob0
//
// The 4-byte carved body at 0x003D4DA0 reads the witnessed +0x40 field.
// No caller or table proves a semantic owner, so the address-derived class
// keeps the identity honest.

typedef int Int;

class Rva003D4DA0Opaque
{
	unsigned char m_unmodelled_000[0x40];
	Int m_unmodelled_040;

public:
	Int get() const;
};

Int Rva003D4DA0Opaque::get() const
{
	return m_unmodelled_040;
}
