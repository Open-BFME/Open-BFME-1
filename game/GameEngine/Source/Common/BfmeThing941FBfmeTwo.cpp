// Retail 0x00023D49 is a five-byte ILT thunk for BfmeThing941F::bfmeTwo941F.
// The pinned callers and the direct target prove this forwarding identity.
// cl: /O2 /MD

class Matrix3DTN;

class BfmeThingTN
{
public:
	void bfmeSetTransformTN(const Matrix3DTN *);
};

class BfmeThing941F
{
public:
	void bfmeTwo941F(void *value);
};

void BfmeThing941F::bfmeTwo941F(void *value)
{
	reinterpret_cast<BfmeThingTN *>(this)->bfmeSetTransformTN(
		reinterpret_cast<const Matrix3DTN *>(value));
}
