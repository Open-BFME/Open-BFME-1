// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep

class RefCountClass
{
public:
	RefCountClass();
	virtual void Delete_This();
	virtual ~RefCountClass();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	MultiListObjectClass();
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RenderObjClass();
	virtual int Class_ID() const;
	virtual ~RenderObjClass();

protected:
	char m_tail[0xB8];
};

void operator delete[](void *) throw();

#include "simplevec.h"

class Vector3
{
public:
	Vector3() {}
	float X, Y, Z;
};

class BfmeTexVGX;

class TextureRef
{
public:
	TextureRef() : m_ptr(0) {}
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
	BfmeThingVGX()
		: m_tex(),
		  m_shader(),
		  m_width(0.0f),
		  m_color(),
		  m_opacity(0.0f),
		  m_1c(0.0f),
		  m_20(0)
	{}
	BfmeThingVGX(const BfmeThingVGX &);

private:
	TextureRef m_tex;
	ShaderClass m_shader;
	float m_width;
	Vector3 m_color;
	float m_opacity;
	float m_1c;
	char m_20;
};

class Bitmap2DObjClass : public RenderObjClass
{
public:
	Bitmap2DObjClass();
	Bitmap2DObjClass(const Bitmap2DObjClass &);
	virtual RenderObjClass *Clone() const;

private:
	SimpleDynVecClass<Vector3> m_vertices;
	SimpleDynVecClass<float> m_widths;
	BfmeThingVGX m_vgx;
};

// ??0Bitmap2DObjClass@@QAE@XZ present-unmatched
Bitmap2DObjClass::Bitmap2DObjClass()
    : m_vertices(0),
      m_widths(0),
      m_vgx()
{}

// ??0Bitmap2DObjClass@@QAE@ABV0@@Z present-unmatched
Bitmap2DObjClass::Bitmap2DObjClass(const Bitmap2DObjClass &source)
	: m_vertices(source.m_vertices),
	  m_widths(source.m_widths),
	  m_vgx(source.m_vgx)
{}

void Force_Bitmap2DObj_Destructor(Bitmap2DObjClass *bitmap)
{
	delete bitmap;
}
