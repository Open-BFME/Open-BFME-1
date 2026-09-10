// ?drawRemainingRectClock@W3DDisplay@@UAEXMMMMMK@Z
// partial score=0.90 date=2026-09-11
// Retail RVA 0x006ECA80; W3DDisplay vtable slot +0xCC (after the matched
// drawRectClock slot +0xC8).  The 544-byte body is the BFME radial remaining
// clock variant: it clamps the percentage, builds an ellipse fan, and sends
// each triangle through the already matched BfmeA1207 helper.
//
// The two-pi data reference is a separate retail literal at VA 0x0111E36C;
// it is pinned under g_bfmeDisplayTwoPi rather than being recreated locally.
//
// Fixed vs the 0.84 bank: the count-multiply/pop shape (fusing the K1266B
// multiply into the bfmeMathVE cast expression keeps the ternary maxHalf
// value resident across the fraction multiply, matching retail's deferred
// "fstp st(0)" discard) and the zero1/zero2/zero3 store order (declare them
// zero3,zero2,zero1 so the compiler's argument-order materialization comes
// out ascending like retail's). ours=550B vs retail=544B, 117 non-reloc
// diff bytes, first divergence now at +0x107: retail speculatively loads
// dword ptr [esp+0x30] (previous.X) between the centerX/centerY register
// loads that precede the do-while loop and keeps that one FPU register
// resident across the whole loop for one of the two vertex-sum adds inside
// the loop body (loop body itself is otherwise byte-exact); nothing tried
// here (temp-variable reordering of the X/Y sum expressions, zero-struct
// declaration order) reproduces that speculative preload. Ruled out:
// reordering the countValue statements alone (three-statement form always
// pops fraction immediately, regardless of maxHalf/fraction operand order);
// a single fused maxHalf*fraction*K1266B expression (wrong operand order,
// loads K1266B via fld first, 550B with an extra fld+fmul).
// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

struct BfmeV1207
{
	BfmeV1207() {}
	BfmeV1207(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

typedef BfmeV1207 BfmeVector2;

class BfmeRender2D
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void disableTexturing() { m_texturingEnabled = 0; }
};

class BfmeA1207 : public BfmeRender2D
{
public:
	void bfmeDo1207(const BfmeV1207 &a1, const BfmeV1207 &a2,
		const BfmeV1207 &a3, const BfmeV1207 &a4,
		const BfmeV1207 &a5, const BfmeV1207 &a6, int color);
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	BfmeA1207 *m_render2D;

public:
	virtual void drawRemainingRectClock(float startX, float startY, float width,
		float height, float percent, UnsignedInt color);
};

extern const float BfmeZeroRange;
extern float g_bfmeScaleBC;
extern const float g_bfmeK1253;
extern float g_bfmeDefaultBU;
extern const float g_bfmeK1266B;
extern const float g_01076C24;
extern const float g_bfmeDisplayTwoPi;

extern "C" __declspec(dllimport) double __cdecl bfmeMathVE(double value);
extern "C" double __cdecl sin(double value);
extern "C" double __cdecl cos(double value);
#pragma intrinsic(sin, cos)

inline long floatToLong(float value)
{
	long result;
	__asm { fld [value] }
	__asm { fistp [result] }
	return result;
}

void W3DDisplay::drawRemainingRectClock(float startX, float startY, float width,
	float height, float percent, UnsignedInt color)
{
	if (percent < BfmeZeroRange)
		percent = BfmeZeroRange;
	else if (percent > g_bfmeScaleBC)
		percent = g_bfmeScaleBC;

	float halfWidth = width * 0.5f;
	m_render2D->disableTexturing();
	float halfHeight = height * 0.5f;
	float centerX = halfWidth + startX;
	float centerY = halfHeight + startY;
	float negativeHalfHeight = -halfHeight;
	BfmeVector2 previous(0.0f, negativeHalfHeight);

	float fraction = g_bfmeDefaultBU - (g_01076C24 * percent);
	float angleRange = g_bfmeDisplayTwoPi;
	angleRange *= fraction;
	float maxHalf = (halfWidth > halfHeight) ? halfWidth : halfHeight;
	float countValue = maxHalf;
	countValue *= fraction;
	float countAsFloat = (float)bfmeMathVE((double)(countValue * g_bfmeK1266B));
	int count = floatToLong(countAsFloat);
	float angleStep = angleRange / (float)count;
	float angle = 0.0f;

	if (count > 0)
	{
		BfmeVector2 zero3(0.0f, 0.0f);
		BfmeVector2 zero2(0.0f, 0.0f);
		BfmeVector2 zero1(0.0f, 0.0f);
		BfmeVector2 center(centerX, centerY);

		int i = count;
		do
		{
			angle += angleStep;
			BfmeVector2 next;
			if (angle > BfmeZeroRange && angle < g_bfmeDisplayTwoPi)
			{
				next.X = -(halfWidth * (float)sin((double)angle));
				next.Y = -(halfHeight * (float)cos((double)angle));
			}
			else
			{
				next.X = 0.0f;
				next.Y = negativeHalfHeight;
			}

			m_render2D->bfmeDo1207(
				center,
				BfmeVector2(centerX + previous.X, centerY + previous.Y),
				BfmeVector2(centerX + next.X, centerY + next.Y),
				zero1, zero2, zero3, color);
			previous = next;
		} while (--i);
	}
}
