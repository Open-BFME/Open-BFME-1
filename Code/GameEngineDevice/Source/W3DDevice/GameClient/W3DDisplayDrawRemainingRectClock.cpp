// ?drawRemainingRectClock@W3DDisplay@@UAEXMMMMMK@Z
// Retail RVA 0x006ECA80; W3DDisplay vtable slot +0xCC (slot 51).
// Exact BFME body: 544 bytes, 14 relocations, verified by the limited fleet probe.
// The adjacent matched drawRectClock slot is +0xC8; this method owns the next slot.
// BfmeV1207 assignment and the four-byte x87 conversion helper preserve the
// native BFME codegen shape. The generated dump remains untouched.
// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

struct BfmeV1207
{
	BfmeV1207() {}
	BfmeV1207(float x, float y) : X(x), Y(y) {}
	BfmeV1207 &operator=(const BfmeV1207 &v) { X = v.X; Y = v.Y; return *this; }
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
