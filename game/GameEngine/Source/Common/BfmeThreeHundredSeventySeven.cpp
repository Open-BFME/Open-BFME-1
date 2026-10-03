void j_00025e1e();

struct BfmeVecZA
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class BfmeThingZA
{
public:
	BfmeThingZA *bfmeInitZA(const BfmeVecZA *one, const BfmeVecZA *two);
	unsigned char m_bfmeHead[4];
	BfmeVecZA m_bfmeA;
	BfmeVecZA m_bfmeB;
};

BfmeThingZA *BfmeThingZA::bfmeInitZA(const BfmeVecZA *one, const BfmeVecZA *two)
{
	// Retail calls the five-byte ILT thunk at 0x00025E1E, which tail-jumps to
	// the real body; one-argument fastcall puts `this` in ECX like a no-argument
	// thiscall, and the reference names the thunk that defines it.
	typedef void (__fastcall *BfmeBaseCall)(BfmeThingZA *);
	reinterpret_cast<BfmeBaseCall>(&j_00025e1e)(this);
	m_bfmeA = *one;
	m_bfmeB = *two;
	return this;
}
