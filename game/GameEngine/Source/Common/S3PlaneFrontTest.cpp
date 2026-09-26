// One more body the ledger had split across its return arms.
//
// 0x0042E3B0 is a plane test: three products accumulated with the argument's
// fields as the loaded operand and ours as the multiplier, the plane distance
// at +0x0C subtracted, and the result compared against the argument's own
// +0x0C. test ah,1 after the compare reads C0 alone, so the branch is taken on
// strictly-less and the true case is greater-or-equal.
//
// The return is int, not bool: mov eax,1 and xor eax,eax rather than the
// two-byte al forms. Declared bool the body comes out three bytes shorter.

typedef float Real;

class BfmePlaneArg
{
public:
	Real m_bfmeX;							// +0x00
	Real m_bfmeY;							// +0x04
	Real m_bfmeZ;							// +0x08
	Real m_bfmeRadius;						// +0x0C
};

class Gen_0042e3b0
{
public:
	int bfmeInFront(const BfmePlaneArg *sphere) const;

private:
	Real m_bfmeX;							// +0x00
	Real m_bfmeY;							// +0x04
	Real m_bfmeZ;							// +0x08
	Real m_bfmeDistance;						// +0x0C
};

// ?bfmeInFront@Gen_0042e3b0@@QBEHPBVBfmePlaneArg@@@Z
int Gen_0042e3b0::bfmeInFront(const BfmePlaneArg *sphere) const
{
	if (sphere->m_bfmeX * m_bfmeX + sphere->m_bfmeY * m_bfmeY + sphere->m_bfmeZ * m_bfmeZ
		- m_bfmeDistance >= sphere->m_bfmeRadius)
		return 1;

	return 0;
}

