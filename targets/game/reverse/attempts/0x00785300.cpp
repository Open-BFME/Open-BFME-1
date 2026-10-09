// ?draw@Rva00785FD0Item@@QAEXXZ
// partial score=0.8109 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWMath
// stlport

#include <vector>

struct LinePoint0078B040
{
	LinePoint0078B040() {}
	LinePoint0078B040(const LinePoint0078B040 &other) : x(other.x), y(other.y) {}
	float x, y;
};
struct LineVertex0078B040 { float x, y, z; unsigned color; float field10[4]; };

void __fastcall emitLine0078B040(void *, LineVertex0078B040 **cursor,
	const LinePoint0078B040 &a, const LinePoint0078B040 &b, float width, unsigned color);

struct Rva00785FD0Renderer;
extern Rva00785FD0Renderer *g_rva00785FD0Renderer;
void *__fastcall rva0078C300RendererAppend(Rva00785FD0Renderer *renderer, int count);
void __fastcall rva0078C430DoubleDispatch(void *renderer, int count);

int bfmeHelpWI(int color);
extern int g_Rva012BB860TransformMode;

#define _OPERATOR_NEW_DEFINED_
#include "texture.h"

// Four-byte texture reference returned by value; its destructor releases.
class Rva00785300TextureRef
{
public:
	Rva00785300TextureRef() : m_texture(0) {}
	Rva00785300TextureRef(const Rva00785300TextureRef &other) : m_texture(other.m_texture) { if (m_texture) m_texture->Add_Ref(); }
	~Rva00785300TextureRef() { if (m_texture) m_texture->Release_Ref(); }
	TextureClass *m_texture;
};

// The close helpers ignore EDX; their call sites still forward the vertex cursor.
// The casts retain that forwarding while naming the canonical declarations.
class BfmeTexVGS;
class BfmeThingVGV
{
public:
	void __fastcall bfmeSetVGV(BfmeTexVGS **src);
};
class Rva0078AE40
{
public:
	void closeA();
	void closeB();
};

class Gen_00920a60
{
public:
	void m(int a);
};
struct Rva00785300Filter
{
	int field04() const { return m_field04; }
	void setField04(int value) { m_field04 = value; }
	void setField00(int value) { m_field00 = value; }
	int m_field00;
	int m_field04;
};
class ShroudFilter;
class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};
class BfmeThingIH;

struct Rva00785300Matrix
{
	void transform(const LinePoint0078B040 &p, float &x, float &y) const
	{
		x = a * p.x + c * p.y + tx;
		y = b * p.x + d * p.y + ty;
	}
	LinePoint0078B040 operator*(const LinePoint0078B040 &p) const
	{
		LinePoint0078B040 r;
		r.x = a * p.x + c * p.y + tx;
		r.y = b * p.x + d * p.y + ty;
		return r;
	}
	float a, b, c, d, tx, ty;
};

struct Rva00785300Triangle
{
	LinePoint0078B040 p[3];
};

struct Rva00785300Line
{
	LinePoint0078B040 p[2];
	const LinePoint0078B040 &a() const { return p[0]; }
	const LinePoint0078B040 &b() const { return p[1]; }
};

class Rva00785300SolidShape
{
public:
	virtual ~Rva00785300SolidShape();
	unsigned m_color;
	std::vector<Rva00785300Triangle> m_triangles;
};

class Rva00785300TexturedShape : public Rva00785300SolidShape
{
public:
	unsigned char m_pad14;
	unsigned char m_scaled;
	unsigned char m_pad16[2];
	void *m_source;
	Rva00785300Matrix m_uv;
};

class Rva00785300LineShape
{
public:
	virtual ~Rva00785300LineShape();
	float m_width;
	unsigned m_color;
	std::vector<Rva00785300Line> m_lines;
};

class BfmeThingRD
{
public:
	Rva00785300TextureRef bfmeGoRD();
};
class Gen_00784480
{
public:
	void update(BfmeThingIH &thing);
};

class Rva00785300Shape
{
public:
	virtual ~Rva00785300Shape();
	virtual int kind();
	virtual Rva00785300TexturedShape *textured();
	virtual Rva00785300SolidShape *solid();
	virtual Rva00785300LineShape *lines();
};

class Rva00785FD0Item
{
public:
	void draw();
	void *m_vtbl;
	std::vector<Rva00785300Shape *> m_shapes;
	Rva00785300Matrix m_matrix;
};

#define XF_X(m, p) (m.a * p.x + m.c * p.y + m.tx)
#define XF_Y(m, p) (m.b * p.x + m.d * p.y + m.ty)

static inline Rva00785300Filter *filterOf(Rva00785300TextureRef &tex)
{
	return (Rva00785300Filter *)((ShroudTexture *)&tex)->getFilter();
}

// The filter value is loaded before each getFilter() call, so each store is an
// inline call that receives the value and fetches the filter itself.
static inline void setFilterField04(Rva00785300TextureRef &tex, int value)
{
	filterOf(tex)->setField04(value);
}

static inline void setFilterField00(Rva00785300TextureRef &tex, int value)
{
	filterOf(tex)->setField00(value);
}

static inline void setFilterField08(Rva00785300TextureRef &tex, int value)
{
	((Gen_00920a60 *)filterOf(tex))->m(value);
}

static inline void setVertex(LineVertex0078B040 *v, const Rva00785300Matrix &m,
	const LinePoint0078B040 &p, unsigned color)
{
	v->x = XF_X(m, p);
	v->y = XF_Y(m, p);
	v->z = 0.0f;
	v->color = color;
}

static inline void setUV(LineVertex0078B040 *v, const Rva00785300Matrix &m,
	const LinePoint0078B040 &p)
{
	v->field10[0] = XF_X(m, p);
	v->field10[1] = XF_Y(m, p);
}

static inline void setTexture(const Rva00785300TextureRef &tex)
{
	((BfmeThingVGV *)g_rva00785FD0Renderer)->bfmeSetVGV((BfmeTexVGS **)&tex);
}

static inline void transformPoint(const Rva00785300Matrix &m, const LinePoint0078B040 &p,
	float &x, float &y)
{
	x = XF_X(m, p);
	y = XF_Y(m, p);
}

void Rva00785FD0Item::draw()
{
	for (std::vector<Rva00785300Shape *>::iterator it = m_shapes.begin(); it != m_shapes.end(); ++it)
	{
		Rva00785300Shape *shape = *it;
		switch (shape->kind())
		{
		case 0:
		{
			Rva00785300TexturedShape *tri = shape->textured();
			if (!tri)
				break;
			Rva00785300TextureRef tex = ((BfmeThingRD *)tri)->bfmeGoRD();
			if (tex.m_texture)
			{
				if (!tri->m_scaled)
					((Gen_00784480 *)tri)->update(*(BfmeThingIH *)&tex);
				if (g_Rva012BB860TransformMode == 1 && filterOf(tex)->field04() != 1)
				{
					setFilterField04(tex, g_Rva012BB860TransformMode);
					setFilterField00(tex, g_Rva012BB860TransformMode);
					setFilterField08(tex, g_Rva012BB860TransformMode);
				}
			}
			unsigned color = bfmeHelpWI(tri->m_color);
			setTexture(tex);
			LineVertex0078B040 *v = (LineVertex0078B040 *)rva0078C300RendererAppend(
				g_rva00785FD0Renderer, tri->m_triangles.size());
			if (v)
			{
				for (std::vector<Rva00785300Triangle>::iterator t = tri->m_triangles.begin();
					t != tri->m_triangles.end(); ++t)
				{
					setVertex(v, m_matrix, t->p[1], color);
					setUV(v, tri->m_uv, t->p[1]);
					++v;
					setVertex(v, m_matrix, t->p[0], color);
					setUV(v, tri->m_uv, t->p[0]);
					++v;
					setVertex(v, m_matrix, t->p[2], color);
					setUV(v, tri->m_uv, t->p[2]);
					++v;
				}
				(((Rva0078AE40 *)g_rva00785FD0Renderer)->*reinterpret_cast<void (__fastcall Rva0078AE40::*)(void *)>(&Rva0078AE40::closeA))(v);
			}
			break;
		}
		case 1:
		{
			Rva00785300SolidShape *tri = shape->solid();
			if (!tri)
				break;
			unsigned color = bfmeHelpWI(tri->m_color);
			setTexture(Rva00785300TextureRef());
			LineVertex0078B040 *v = (LineVertex0078B040 *)rva0078C300RendererAppend(
				g_rva00785FD0Renderer, tri->m_triangles.size());
			if (!v)
				break;
			for (std::vector<Rva00785300Triangle>::iterator t = tri->m_triangles.begin();
				t != tri->m_triangles.end(); ++t)
			{
				setVertex(v, m_matrix, t->p[0], color);
				++v;
				setVertex(v, m_matrix, t->p[2], color);
				++v;
				setVertex(v, m_matrix, t->p[1], color);
				++v;
			}
			(((Rva0078AE40 *)g_rva00785FD0Renderer)->*reinterpret_cast<void (__fastcall Rva0078AE40::*)(void *)>(&Rva0078AE40::closeA))(v);
			break;
		}
		case 2:
		{
			Rva00785300LineShape *line = shape->lines();
			if (!line)
				break;
			unsigned color = bfmeHelpWI(line->m_color);
			setTexture(Rva00785300TextureRef());
			LineVertex0078B040 *cursor = reinterpret_cast<LineVertex0078B040 *(__fastcall *)(void *, int)>(rva0078C430DoubleDispatch)(g_rva00785FD0Renderer, line->m_lines.size());
			if (!cursor)
				break;
			LinePoint0078B040 a, b;
			for (std::vector<Rva00785300Line>::iterator l = line->m_lines.begin(); l != line->m_lines.end(); ++l)
			{
				m_matrix.transform(l->a(), a.x, a.y);
				m_matrix.transform(l->b(), b.x, b.y);
				emitLine0078B040(g_rva00785FD0Renderer, &cursor, a, b, line->m_width, color);
			}
			(((Rva0078AE40 *)g_rva00785FD0Renderer)->*reinterpret_cast<void (__fastcall Rva0078AE40::*)(void *)>(&Rva0078AE40::closeB))(cursor);
			break;
		}
		}
	}
}
