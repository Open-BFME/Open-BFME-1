// cl: /O2
//
// Retail 0x002C63E0 returns integer zero with no memory access or call.  The
// carved row has no caller or vtable evidence for a semantic owner, so this
// source keeps the zero-returning method address-derived.

class Rva002C63E0
{
public:
	int zero() const;
};

int Rva002C63E0::zero() const
{
	return 0;
}
