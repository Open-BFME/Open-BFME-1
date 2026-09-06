// ?d_0087e0d0@@YAXXZ
// partial score=0.96 date=2026-09-06
// ?bfmeCalcBWF@BfmeCalcBWF@@QAE_NPAUBfmeRetBWF@@M0@Z
// Retail 0x0087E0D0. Copies a three-float result and applies the owner's
// two-axis sine and cosine transform when its scale is nonzero.

extern "C" double __cdecl sin( double angle );
extern "C" double __cdecl cos( double angle );
extern const float BfmeZeroRange;

struct BfmeRetBWF
{
	float x;
	float y;
	float z;
};

class BfmeCalcBWF
{
public:
	bool bfmeCalcBWF( BfmeRetBWF *one, float angle, BfmeRetBWF *two );

private:
	char m_unmodelled[ 8 ];
	float m_x;
	float m_y;
};

// ?bfmeCalcBWF@BfmeCalcBWF@@QAE_NPAVBfmeRetBWF@@M0@Z
bool BfmeCalcBWF::bfmeCalcBWF(
	BfmeRetBWF *one, float angle, BfmeRetBWF *two )
{
	*two = *one;
	if ( m_x == BfmeZeroRange
		&& m_y == BfmeZeroRange )
		return false;

	float sine = (float)sin( angle );
	float cosine = (float)cos( angle );
	two->x += cosine * m_x + sine * m_y;
	two->y += sine * m_x + cosine * m_y;
	return true;
}
