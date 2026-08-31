// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class TextureClass;

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

class WW3D
{
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
	static unsigned int SyncTime;
};

class VertexFormatXYZUV1;

class StreakRendererClass
{
public:
	StreakRendererClass();

private:
	enum { DEFAULT_BITS = 1 };
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

StreakRendererClass::StreakRendererClass() :
	Texture(0),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	Width(0.0f),
	Color(1.0f, 1.0f, 1.0f),
	Opacity(1.0f),
	SubdivisionLevel(0),
	NoiseAmplitude(0.0f),
	MergeAbortFactor(1.5f),
	TextureTileFactor(1.0f),
	LastUsedSyncTime(WW3D::Get_Sync_Time()),
	CurrentUVOffset(0.0f, 0.0f),
	UVOffsetDeltaPerMS(0.0f, 0.0f),
	Bits(DEFAULT_BITS),
	m_vertexBufferSize(0),
	m_vertexBuffer(0)
{
}
