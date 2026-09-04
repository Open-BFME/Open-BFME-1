// cl: /DNDEBUG /MD /EHsc
//
// BfmeThingVGX copy ctor, retail 0x00975090, 103 bytes.
// Sibling of matched bfmeAssignVGX @ 0x00974FB0. TextureRef at +0 owns the
// one EH state; defaults then assign, same shape as SegLineRendererClass.

class BfmeTexVGX;

class TextureRef
{
public:
	TextureRef(BfmeTexVGX *p) : m_ptr(p) {}
	~TextureRef();

private:
	BfmeTexVGX *m_ptr;
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class BfmeThingVGX
{
public:
	BfmeThingVGX(const BfmeThingVGX &that);
	BfmeThingVGX &bfmeAssignVGX(const BfmeThingVGX &o);

private:
	TextureRef m_tex;
	ShaderClass m_shader;
	float m_width;
	Vector3 m_color;
	float m_opacity;
	float m_1c;
	char m_20;
};

// ??0BfmeThingVGX@@QAE@ABV0@@Z
BfmeThingVGX::BfmeThingVGX(const BfmeThingVGX &that) :
	m_tex(0),
	m_shader(*(const ShaderClass *)0x012D6E2C),
	m_width(0.0f),
	m_color(Vector3(1, 1, 1)),
	m_opacity(1.0f),
	m_1c(1.0f),
	m_20(0)
{
	bfmeAssignVGX(that);
}
