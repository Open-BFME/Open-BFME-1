// cl: /DNDEBUG /MD /EHsc

// PointGroupClass shader-prep, retail 0x00912E60. The 153-byte block that
// ZH inlines at the top of PointGroupClass::Render: disable the extra cull
// bit, then set primary gradient from the 0.9961 (254/255) white-opaque
// test and texturing from the Texture pointer. Layout matches the matched
// ctor at 0x00912580 (PointDiffuse +8, Texture +0x24, ShaderBits +0x28,
// DefaultPointColor +0x38).

class Vector3
{
public:
	float X, Y, Z;
};

class PointGroupClass
{
public:
	void prepare_shader(void);

private:
	virtual void abstract_dtor(void);
	void *PointLoc;
	void *PointDiffuse;
	void *APT;
	void *PointSize;
	void *PointOrientation;
	void *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	void *Texture;
	unsigned int ShaderBits;
	int PointMode;
	unsigned int Flags;
	float DefaultPointSize;
	Vector3 DefaultPointColor;
	float DefaultPointAlpha;
};

// ?prepare_shader@PointGroupClass@@QAEXXZ
void PointGroupClass::prepare_shader(void)
{
	__asm
	{
		mov eax, dword ptr [ecx+0x28]
		and eax, 0xFFEFFFFF
		mov dword ptr [ecx+0x28], eax
	}

	float value_255 = 0.9961f;
	bool default_white_opaque = (DefaultPointColor.X > value_255 &&
		DefaultPointColor.Y > value_255 &&
		DefaultPointColor.Z > value_255 &&
		DefaultPointAlpha > value_255);

	if (!PointDiffuse && default_white_opaque && Texture) {
		ShaderBits &= ~0x1C00u;
	} else {
		ShaderBits = (ShaderBits & ~0x400u) | 0x1800u;
	}

	if (Texture) {
		ShaderBits |= 0x10000u;
	} else {
		ShaderBits &= ~0x10000u;
	}
}
