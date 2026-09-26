// cl: /O2 /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "seglinerenderer.h"
#include "vector2.h"
#include "wwmath.h"

// Retail BFME places the line renderer at +0x104 (ZH places it 0x34 earlier).
class StreakLineClass
{
	unsigned char m_beforeRenderer[0x104];
	SegLineRendererClass LineRenderer;

public:
	void Set_UV_Offset_Rate(const Vector2 &rate);
	Vector2 Get_UV_Offset_Rate();
	void Set_Noise_Amplitude(float amplitude);
};

void StreakLineClass::Set_UV_Offset_Rate(const Vector2 &rate)
{
	LineRenderer.Set_UV_Offset_Rate(rate);
}


Vector2 StreakLineClass::Get_UV_Offset_Rate()
{
	return LineRenderer.Get_UV_Offset_Rate();
}

void StreakLineClass::Set_Noise_Amplitude(float amplitude)
{
	LineRenderer.Set_Noise_Amplitude(WWMath::Fabs(amplitude));
	*reinterpret_cast<unsigned *>(reinterpret_cast<char *>(this) + 0x10) &= 0xfffdffffu;
}