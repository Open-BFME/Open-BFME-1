// ??0BfmeThingVGX@@QAE@ABV0@@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

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

class BfmeThingVGX
{
public:
	BfmeThingVGX(const BfmeThingVGX &that);
	BfmeThingVGX &bfmeAssignVGX(const BfmeThingVGX &o);

private:
	TextureRef m_tex;
	ShaderClass m_shader;
	float m_width;
	float m_cx;
	float m_cy;
	float m_cz;
	float m_opacity;
	float m_1c;
	char m_20;
};

BfmeThingVGX::BfmeThingVGX(const BfmeThingVGX &that) :
	m_tex(0)
{
	m_shader = *(const ShaderClass *)0x012D6E2C;
	m_width = 0.0f;
	m_cx = 1.0f;
	m_cy = 1.0f;
	m_cz = 1.0f;
	m_20 = 0;
	m_opacity = 1.0f;
	m_1c = 1.0f;
	bfmeAssignVGX(that);
}
