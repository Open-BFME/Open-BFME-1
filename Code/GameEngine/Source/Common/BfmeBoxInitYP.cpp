// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the bounds initialiser at retail 0x00C6C350, 68 bytes.  There is
// no one-time guard here, so this is a namespace-scope dynamic initialiser
// rather than a function-local static: the two corner temporaries are built on
// the stack right to left and passed by reference.

struct BfmePairYP
{
	BfmePairYP(float x, float y) : X(x), Y(y) {}

	float X;						// +0x00
	float Y;						// +0x04
};

class BfmeBoxYP
{
public:
	BfmeBoxYP(const BfmePairYP &low, const BfmePairYP &high);

	~BfmeBoxYP(void);

private:
	char m_bfmeRaw[0x10];
};

// ??__Eg_bfmeBoxYP@@YAXXZ
BfmeBoxYP g_bfmeBoxYP(BfmePairYP(-3.402823466e+38F, -3.402823466e+38F),
	BfmePairYP(3.402823466e+38F, 3.402823466e+38F));
