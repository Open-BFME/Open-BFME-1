// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class TextureClass;

class TextureRef
{
public:
	TextureRef() : m_ptr(0) {}
	~TextureRef();
private:
	TextureClass *m_ptr;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	unsigned int m_bits;
	static ShaderClass _PresetAdditiveSpriteShader;
};

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

class VertexFormatXYZUV1;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streakRender.h
class StreakRendererClass
{
public:
	StreakRendererClass(const StreakRendererClass &that);
	StreakRendererClass &operator=(const StreakRendererClass &that);

private:
	enum { DEFAULT_BITS = 1 };
	TextureRef Texture;
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

StreakRendererClass::StreakRendererClass(const StreakRendererClass &that) :
	Texture(),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	Width(0.0f),
	Color(1.0f, 1.0f, 1.0f),
	Opacity(1.0f),
	SubdivisionLevel(0),
	NoiseAmplitude(0.0f),
	MergeAbortFactor(1.5f),
	TextureTileFactor(1.0f),
	LastUsedSyncTime(that.LastUsedSyncTime),
	CurrentUVOffset(0.0f, 0.0f),
	UVOffsetDeltaPerMS(0.0f, 0.0f),
	Bits(DEFAULT_BITS),
	m_vertexBufferSize(0),
	m_vertexBuffer(0)
{
	*this = that;
}
