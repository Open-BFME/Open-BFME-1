// cl: /DNDEBUG /MD /EHsc

// Initialise every member to its default, take one field from the source, then
// assign. That is the reference's copy constructor unchanged -- the whole body
// is `*this = that`, and everything before the call is the initialiser list.
//
// Each entry lands where the reference says it should: Texture at 0, the preset
// shader at 4, Width at 8, Color's three floats at 0xc, Opacity at 0x18,
// SubdivisionLevel at 0x1c, NoiseAmplitude at 0x20, MergeAbortFactor at 0x28,
// TextureTileFactor at 0x2c, LastUsedSyncTime at 0x30 copied from that, the two
// UV pairs at 0x34 and 0x3c, and Bits at 0x44. BFME adds three fields the
// reference does not have, at 0x24, 0x48 and 0x4c, all zeroed.
//
// The preset shader is read as an address. It is a static member of ShaderClass
// and the load is a plain dword, so the literal says what the bytes say without
// asserting a symbol name.
class TextureClass;

// The texture is not a raw pointer. The reference's operator= sets it with
// REF_PTR_SET and the destructor releases it with REF_PTR_RELEASE, and retail
// registers this in the frame slot before the store to offset 0 -- which is
// where the constructor's one unwind state is owned.
class TextureRef
{
public:
	TextureRef(TextureClass *p) : m_ptr(p) {}
	~TextureRef();

private:
	TextureClass *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}

	float X;
	float Y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.h
class SegLineRendererClass
{
public:
	SegLineRendererClass(const SegLineRendererClass &that);

	~SegLineRendererClass();

	SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
	TextureRef Texture;
	ShaderClass Shader;
	float Width;
	Vector3 Color;
	float Opacity;
	int SubdivisionLevel;
	float NoiseAmplitude;
	int m_24;
	float MergeAbortFactor;
	float TextureTileFactor;
	unsigned int LastUsedSyncTime;
	Vector2 CurrentUVOffset;
	Vector2 UVOffsetDeltaPerMS;
	int Bits;
	int m_48;
	int m_4c;
};

// ??0SegLineRendererClass@@QAE@ABV0@@Z
SegLineRendererClass::SegLineRendererClass(const SegLineRendererClass &that) :
	Texture(0),
	Shader(*(const ShaderClass *)0x012D6E2C),
	Width(0.0f),
	Color(Vector3(1, 1, 1)),
	Opacity(1.0f),
	SubdivisionLevel(0),
	NoiseAmplitude(0.0f),
	m_24(0),
	MergeAbortFactor(1.5f),
	TextureTileFactor(1.0f),
	LastUsedSyncTime(that.LastUsedSyncTime),
	CurrentUVOffset(0.0f, 0.0f),
	UVOffsetDeltaPerMS(0.0f, 0.0f),
	Bits(1),
	m_48(0),
	m_4c(0)
{
	*this = that;
}
