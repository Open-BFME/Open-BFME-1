// ?d_007d7910@@YAXXZ
// partial score=0.38 date=2026-09-22
// cl: /DNDEBUG /MD
// Retail 0x007D7910: the slot-3 postRender body of Rva007D85C0.
// Its owner is proven by the constructor-installed vtable 0x01128BAC.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

enum FilterModes
{
	FM_NULL_MODE = 0
};

extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

#define Rva007D85C0RenderFlag (*(unsigned char *)0x0133F42C)

struct Vec4Base
{
	Real x;
	Real y;
	Real z;
	Real w;
};

struct Vec4 : Vec4Base
{
	Vec4(Real a, Real b, Real c, Real d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

struct IDirect3DSurface8;
struct Rva007D85C0Device;

struct Rva007D85C0DeviceVtable
{
	char pad000[0x104];
	long (__stdcall *SetTexture)(Rva007D85C0Device *, unsigned int, void *);
	char pad108[4];
	long (__stdcall *SetTextureStageState)(Rva007D85C0Device *, unsigned int,
		unsigned int, unsigned int);
	char pad110[0x3c];
	long (__stdcall *DrawPrimitiveUP)(Rva007D85C0Device *, unsigned int,
		unsigned int, const void *, unsigned int);
	char pad150[0x14];
	long (__stdcall *SetVertexShader)(Rva007D85C0Device *, unsigned int);
	char pad168[8];
	long (__stdcall *SetPixelShader)(Rva007D85C0Device *, unsigned int);
};

struct Rva007D85C0Device
{
	Rva007D85C0DeviceVtable *v;
};

#define Rva007D85C0DeviceGlobal (*(Rva007D85C0Device **)0x01340534)
#define Rva007D85C0TacticalViewGlobal (*(class Rva007D85C0TacticalView **)0x012F1600)

class Rva007D85C0TacticalView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual Int getWidth() = 0;
	virtual void slot16() = 0;
	virtual Int getHeight() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(Int *, Int *) = 0;
};

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *, Bool);
	static void Set_DX8_Render_State(unsigned long, unsigned int);
	static void Apply_Render_State_Changes(void);
};

class Rva007D85C0
{
public:
	virtual Int init(void);
	virtual Int shutdown(void);
	virtual Bool preRender(Bool &, Int &);
	virtual Bool postRender(FilterModes, Coord2D &, Bool &, Coord2D *);
	virtual Bool setup(FilterModes);
	virtual Int set(FilterModes);
	virtual void reset(void);

	Int m_04;
	Int m_08;
	unsigned char m_0c;
	unsigned char m_pad0d[0x13];
	void *m_20;
};

// ?postRender@Rva007D85C0@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z
Bool Rva007D85C0::postRender(FilterModes mode, Coord2D &scrollDelta,
	Bool &doExtraRender, Coord2D *displaySize)
{
	Rva007D85C0RenderFlag = 0;
	if (m_0c)
	{
		DX8Wrapper::Set_Render_Target(0, true);
		reset();
		doExtraRender = true;
		m_0c = 0;
		return true;
	}
	if (!set(mode))
		return false;

	Rva007D85C0Device *pDev = Rva007D85C0DeviceGlobal;
	struct Vertex
	{
		Vec4Base p;
		Vertex(void) {}
		Real u;
		Real v;
		Real u1;
		Real v1;
	} vertex[4];

	Real inverse = g_bfmeDefaultBU / (Real)m_08;
	Real halfTexel = inverse * g_bfmeK1253;
	vertex[0].p = Vec4(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[0].u1 = g_bfmeDefaultBU + halfTexel;
	vertex[0].v1 = halfTexel;
	vertex[1].p = Vec4(1.0f, -1.0f, 0.0f, 1.0f);
	vertex[1].u1 = g_bfmeDefaultBU + halfTexel;
	vertex[1].v1 = g_bfmeDefaultBU + halfTexel;
	vertex[2].p = Vec4(-1.0f, 1.0f, 0.0f, 1.0f);
	vertex[2].u1 = halfTexel;
	vertex[2].v1 = halfTexel;
	vertex[3].p = Vec4(-1.0f, -1.0f, 0.0f, 1.0f);
	vertex[3].u1 = halfTexel;
	vertex[3].v1 = g_bfmeDefaultBU + halfTexel;

	DX8Wrapper::Set_Render_Target(0, true);
	DX8Wrapper::Set_DX8_Render_State(0x13, 5);
	DX8Wrapper::Set_DX8_Render_State(0x14, 2);
	DX8Wrapper::Set_DX8_Render_State(0x1b, 1);
	DX8Wrapper::Set_DX8_Render_State(0x3c, 0x2f000000);
	DX8Wrapper::Set_DX8_Render_State(0x8d, 1);
	DX8Wrapper::Set_DX8_Render_State(0x91, 1);
	DX8Wrapper::Apply_Render_State_Changes();

	Rva007D85C0DeviceGlobal->v->SetTexture(Rva007D85C0DeviceGlobal,
		0, m_20);
	Rva007D85C0DeviceGlobal->v->SetTexture(Rva007D85C0DeviceGlobal,
		1, m_20);
	pDev->v->SetPixelShader(pDev, 0);
	pDev->v->SetVertexShader(pDev, 0x204);
	pDev->v->SetTextureStageState(pDev, 0, 5, 3);
	pDev->v->SetTextureStageState(pDev, 0, 6, 3);
	pDev->v->SetTextureStageState(pDev, 0, 4, 2);
	pDev->v->SetTextureStageState(pDev, 1, 5, 1);
	pDev->v->SetTextureStageState(pDev, 1, 6, 2);
	pDev->v->SetTextureStageState(pDev, 1, 4, 2);
	pDev->v->SetTextureStageState(pDev, 0, 2, 0);
	pDev->v->SetTextureStageState(pDev, 0, 1, 2);
	pDev->v->SetTextureStageState(pDev, 0, 3, 0);
	pDev->v->SetTextureStageState(pDev, 1, 2, 1);
	pDev->v->SetTextureStageState(pDev, 1, 3, 3);
	pDev->v->SetTextureStageState(pDev, 1, 7, 1);
	pDev->v->SetTextureStageState(pDev, 2, 1, 1);
	pDev->v->SetTextureStageState(pDev, 0, 0x18, 0);
	pDev->v->SetTextureStageState(pDev, 1, 0x18, 1);

	Int xpos, ypos, width, height;
	Rva007D85C0TacticalViewGlobal->getOrigin(&xpos, &ypos);
	width = Rva007D85C0TacticalViewGlobal->getWidth();
	height = Rva007D85C0TacticalViewGlobal->getHeight();
	Real right = (Real)(xpos + width);
	Real bottom = (Real)(ypos + height);
	Real finalHalfTexel = (g_bfmeDefaultBU / (Real)m_08) *
		g_bfmeK1253;

	vertex[0].p = Vec4(right - g_bfmeK1253, bottom - g_bfmeK1253,
		0.0f, 1.0f);
	vertex[1].p = Vec4(right - g_bfmeK1253,
		(Real)ypos - g_bfmeK1253,
		0.0f, 1.0f);
	vertex[2].p = Vec4((Real)xpos - g_bfmeK1253,
		bottom - g_bfmeK1253,
		0.0f, 1.0f);
	vertex[3].p = Vec4((Real)xpos - g_bfmeK1253,
		(Real)ypos - g_bfmeK1253,
		0.0f, 1.0f);
	vertex[0].u = (g_bfmeDefaultBU / displaySize->x) * right -
		finalHalfTexel;
	vertex[0].v = (g_bfmeDefaultBU / displaySize->y) * bottom -
		finalHalfTexel;
	vertex[1].u = (g_bfmeDefaultBU / displaySize->x) * right -
		finalHalfTexel;
	vertex[1].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)ypos - finalHalfTexel;
	vertex[2].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)xpos - finalHalfTexel;
	vertex[2].v = (g_bfmeDefaultBU / displaySize->y) * bottom -
		finalHalfTexel;
	vertex[3].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)xpos - finalHalfTexel;
	vertex[3].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)ypos - finalHalfTexel;

	pDev->v->DrawPrimitiveUP(pDev, 5, 2, vertex, sizeof(Vertex));

	vertex[0].u = (g_bfmeDefaultBU / displaySize->x) * right -
		finalHalfTexel;
	vertex[0].v = (g_bfmeDefaultBU / displaySize->y) * bottom +
		finalHalfTexel;
	vertex[1].u = (g_bfmeDefaultBU / displaySize->x) * right -
		finalHalfTexel;
	vertex[1].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)ypos + finalHalfTexel;
	vertex[2].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)xpos - finalHalfTexel;
	vertex[2].v = (g_bfmeDefaultBU / displaySize->y) * bottom +
		finalHalfTexel;
	vertex[3].u = (g_bfmeDefaultBU / displaySize->x) *
		(Real)xpos - finalHalfTexel;
	vertex[3].v = (g_bfmeDefaultBU / displaySize->y) *
		(Real)ypos + finalHalfTexel;
	pDev->v->DrawPrimitiveUP(pDev, 5, 2, vertex, sizeof(Vertex));
	reset();
	return true;
}
