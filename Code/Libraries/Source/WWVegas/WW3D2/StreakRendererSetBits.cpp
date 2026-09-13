// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// The BFME StreakRendererClass keeps the texture-animation fields that the
// GeneralsMD header comments out.  Its constructor at 0x0095C720 therefore
// places Bits at +0x40 (with the UV delta at +0x38), while the four flag
// setters and the UV-rate setter immediately following that constructor were
// left as unclaimed bodies.  Keep this TU self-contained so the recovered
// layout does not alter the shared upstream header used by the other renderer.

#include "../WWMath/vector2.h"

class TextureClass;

class ShaderClass
{
public:
	unsigned int m_bits;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class VertexFormatXYZUV1;

class StreakRendererClass
{
public:
	void Set_Merge_Intersections(int onoff);
	void Set_Freeze_Random(int onoff);
	void Set_Disable_Sorting(int onoff);
	void Set_End_Caps(int onoff);
	void Set_UV_Offset_Rate(const Vector2 &rate);

private:
	TextureClass *Texture;
	ShaderClass Shader;
	float Width;
	Vector3 Color;
	float Opacity;
	unsigned int SubdivisionLevel;
	float NoiseAmplitude;
	float MergeAbortFactor;
	float TextureTileFactor;
	unsigned int LastUsedSyncTime;
	Vector2 CurrentUVOffset;
	Vector2 UVOffsetDeltaPerMS;
	unsigned int Bits;
	unsigned int m_vertexBufferSize;
	VertexFormatXYZUV1 *m_vertexBuffer;
};

void StreakRendererClass::Set_Merge_Intersections(int onoff)
{
	if (onoff) {
		Bits |= 0x00000001;
	} else {
		Bits &= ~0x00000001;
	}
}

void StreakRendererClass::Set_Freeze_Random(int onoff)
{
	if (onoff) {
		Bits |= 0x00000002;
	} else {
		Bits &= ~0x00000002;
	}
}

void StreakRendererClass::Set_Disable_Sorting(int onoff)
{
	if (onoff) {
		Bits |= 0x00000004;
	} else {
		Bits &= ~0x00000004;
	}
}

void StreakRendererClass::Set_End_Caps(int onoff)
{
	if (onoff) {
		Bits |= 0x00000008;
	} else {
		Bits &= ~0x00000008;
	}
}

void StreakRendererClass::Set_UV_Offset_Rate(const Vector2 &rate)
{
	UVOffsetDeltaPerMS = rate * 0.001f;
}
