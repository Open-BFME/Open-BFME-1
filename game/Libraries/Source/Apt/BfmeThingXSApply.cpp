// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// AssetManagerImpl::bfmeApplyXS: transforms the four corners of a rectangle by a 2x3 matrix
// and grows a min/max bounds rectangle to cover them.
#include "vector2.h"

class AssetManagerImpl
{
public:
	void bfmeApplyXS(void *what, void *sub);

private:
	unsigned char m_pad000[0x20];
	Vector2 m_offset20;
	Vector2 m_offset28;
	Vector2 m_offset30;
};

// 0x008D2E20: what is the bounds rectangle (minX, minY, maxX, maxY), sub the source rectangle.
void AssetManagerImpl::bfmeApplyXS(void *what, void *sub)
{
	float *bounds = (float *)what;
	const float *input = (const float *)sub;
	float inputX[4];
	float inputY[4];
	float pointX[4];
	float pointY[4];

	inputX[0] = input[0];
	inputY[0] = input[1];
	inputX[1] = input[2];
	inputY[1] = input[1];
	inputX[2] = input[2];
	inputY[2] = input[3];
	inputX[3] = input[0];
	inputY[3] = input[3];

	for (int i = 0; i < 4; ++i)
	{
		pointX[i] = inputX[i] * m_offset20.X + inputY[i] * m_offset28.X + m_offset30.X;
		pointY[i] = inputX[i] * m_offset20.Y + inputY[i] * m_offset28.Y + m_offset30.Y;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (pointX[i] < bounds[0])
			bounds[0] = pointX[i];
		if (pointX[i] > bounds[2])
			bounds[2] = pointX[i];
		if (pointY[i] < bounds[1])
			bounds[1] = pointY[i];
		if (pointY[i] > bounds[3])
			bounds[3] = pointY[i];
	}
}
