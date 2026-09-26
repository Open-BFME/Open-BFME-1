// ?d_007dbd40@@YAXXZ
// partial score=0.4 date=2026-09-22
// cl: /DNDEBUG /MD

typedef float Real;

struct IDirect3DBaseTexture8;
struct IDirect3DSurface8;

struct Coord2D
{
	Real x;
	Real y;
};

struct Device;
struct DeviceVtable
{
	char pad0[0xe4];
	long (__stdcall *SetRenderState)(Device *, unsigned long, unsigned);
	char pad1[0x104 - 0xe8];
	long (__stdcall *SetTexture)(Device *, unsigned, void *);
	char pad2[4];
	long (__stdcall *SetTextureStageState)(Device *, unsigned, unsigned,
		unsigned);
	char pad3[0x14c - 0x118];
	long (__stdcall *DrawPrimitiveUP)(Device *, unsigned, unsigned,
		const void *, unsigned);
	char pad4[0x164 - 0x150];
	long (__stdcall *SetVertexShader)(Device *, unsigned);
	char pad5[0x170 - 0x168];
	long (__stdcall *SetPixelShader)(Device *, unsigned);
};

struct Device
{
	DeviceVtable *v;
};

class BfmeTacticalView
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
	virtual int getWidth() = 0;
	virtual void slot16() = 0;
	virtual int getHeight() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(int *, int *) = 0;
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class ShroudTexture
{
public:
	TextureBaseClass *p;
};

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *, bool);
	static void Set_DX8_Render_State(unsigned long, unsigned);
	static void Apply_Render_State_Changes();
};

void BoxSetTexture(unsigned, TextureBaseClass *&);
unsigned bfmeCurrentCU();
void bfmeHighlightApply(unsigned, void *, unsigned, TextureBaseClass *,
	IDirect3DSurface8 *, TextureBaseClass *, IDirect3DSurface8 *);
extern "C" __declspec(dllimport) double BfmeFloorER(double);
extern "C" long __ftol2(double);

#define BfmeDeviceGlobal (*(Device **)0x01340534)
#define BfmeTacticalViewGlobal (*(BfmeTacticalView **)0x012f1600)
#define g_bfmeHighlightRendering (*(bool *)0x0133f42c)

struct GlobalData
{
	char pad[0xdbd];
	bool active;
};
extern GlobalData *TheWritableGlobalData;

extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1266A;
extern const Real g_bfmeK1253;
extern const Real Rva00064680NegativeScale;

class Rva007DCA80
{
public:
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &, int &);
	virtual bool postRender(int, unsigned, bool &, Coord2D *);
	virtual bool setup(int);
	virtual int set(int);
	virtual void reset();

	unsigned long pixelShader;
	unsigned long vertexShader;
	unsigned pad0[8];
	unsigned size;
	unsigned pad1[4];
	TextureBaseClass *texture[3];
	IDirect3DSurface8 *surface[3];
	ShroudTexture vapor[2];
};

struct Vertex
{
	Real x;
	Real y;
	Real z;
	Real w;
	unsigned color;
	Real u0;
	Real v0;
	Real u1;
	Real v1;
	Real u2;
	Real v2;
};

struct FrameTable
{
	char padding[20];
	int counts[13];
};


bool Rva007DCA80::postRender(int mode, unsigned unused, bool &extra,
	Coord2D *displaySize)
{
	bool saved = *(bool *)((char *)this + 0x1c);
	GlobalData *globalData = TheWritableGlobalData;
	globalData->active = saved;
	g_bfmeHighlightRendering = false;
	if (*(bool *)((char *)this + 0x30))
	{
		DX8Wrapper::Set_Render_Target(0, true);
		reset();
		extra = true;
		*(bool *)((char *)this + 0x30) = false;
		return true;
	}
	if (!set(mode))
		return false;
	FrameTable frameTable;
	int *frameCounts = frameTable.counts;
	Real frameScale = *(const Real *)0x01128aac /
		*(const Real *)0x012bb214;
	frameCounts[0] = 15;
	frameCounts[1] = 16;
	frameCounts[2] = 15;
	frameCounts[3] = 17;
	frameCounts[4] = 18;
	frameCounts[5] = 17;
	frameCounts[6] = 20;
	frameCounts[7] = 21;
	frameCounts[8] = 19;
	frameCounts[9] = 20;
	frameCounts[10] = 17;
	frameCounts[11] = 18;
	frameCounts[12] = 16;
	Real frame = *(Real *)0x013073b8 + *(Real *)0x01096cf4;
	*(Real *)0x013073b8 = frame;
	if (frame >= *(const Real *)0x0112825c)
		*(Real *)0x013073b8 = 0.0f;
	Real framePosition = (Real)BfmeFloorER(
		(double)*(Real *)0x013073b8);
	int frameIndex = (int)framePosition;
	*(int *)((char *)this + 0x18) = (int)__ftol2(
		(float)frameCounts[frameIndex] * frameScale);
	if (*(int *)((char *)this + 0x18) < 3)
		*(int *)((char *)this + 0x18) = 3;

	unsigned current = bfmeCurrentCU();
	bfmeHighlightApply(*(unsigned *)(current + 8), (char *)this + 0x34,
		size, texture[0], surface[1], texture[1], surface[0]);

	Device *device = BfmeDeviceGlobal;
	BoxSetTexture(1, vapor[1].p);
	device->v->SetTextureStageState(device, 1, 1, 1);
	device->v->SetTextureStageState(device, 1, 2, 1);
	device->v->SetTextureStageState(device, 2, 1, 1);
	device->v->SetTextureStageState(device, 2, 2, 2);
	BoxSetTexture(2, vapor[0].p);
	device->v->SetTexture(device, 2,
		((TextureBaseClass *)&vapor[0])->Peek_D3D_Base_Texture());

	Real invW = *(const Real *)0x01075338 / (Real)displaySize->x;
	Real x0, y0;
	BfmeTacticalViewGlobal->getOrigin((int *)&x0, (int *)&y0);
	int width = BfmeTacticalViewGlobal->getWidth();
	int height = BfmeTacticalViewGlobal->getHeight();
	int right = (int)x0 + width;
	int bottom = (int)y0 + height;
	Real invH = *(const Real *)0x01075338 / (Real)displaySize->y;
	Vertex v[4];
	const Real half = g_bfmeK1253;
	v[0].x = (Real)bottom - half;
	v[0].y = (Real)right - half;
	v[0].z = 0.0f;
	v[0].w = 1.0f;
	v[0].color = 0xffffffff;
	v[0].u0 = (Real)right * invW;
	v[0].v0 = (Real)bottom * invH;
	v[0].u1 = v[0].u0 + *(Real *)((char *)this + 0x20);
	v[0].v1 = v[0].v0 + *(Real *)((char *)this + 0x24);
	v[0].u2 = v[0].u0 + *(Real *)((char *)this + 0x28);
	v[0].v2 = v[0].v0;
	v[1].x = (Real)bottom - half;
	v[1].y = (Real)x0 - half;
	v[1].z = 0.0f;
	v[1].w = 1.0f;
	v[1].color = 0xffffffff;
	v[1].u0 = (Real)right * invW;
	v[1].v0 = (Real)y0 * invH;
	v[1].u1 = v[1].u0 + *(Real *)((char *)this + 0x20);
	v[1].v1 = v[1].v0 + *(Real *)((char *)this + 0x24);
	v[1].u2 = v[1].u0 + *(Real *)((char *)this + 0x28);
	v[1].v2 = v[1].v0;
	v[2].x = (Real)y0 - half;
	v[2].y = (Real)right - half;
	v[2].z = 0.0f;
	v[2].w = 1.0f;
	v[2].color = 0xffffffff;
	v[2].u0 = (Real)x0 * invW;
	v[2].v0 = (Real)bottom * invH;
	v[2].u1 = v[2].u0 + *(Real *)((char *)this + 0x20);
	v[2].v1 = v[2].v0 + *(Real *)((char *)this + 0x24);
	v[2].u2 = v[2].u0 + *(Real *)((char *)this + 0x28);
	v[2].v2 = v[2].v0;
	v[3].x = (Real)y0 - half;
	v[3].y = (Real)x0 - half;
	v[3].z = 0.0f;
	v[3].w = 1.0f;
	v[3].color = 0xffffffff;
	v[3].u0 = (Real)x0 * invW;
	v[3].v0 = (Real)y0 * invH;
	v[3].u1 = v[3].u0 + *(Real *)((char *)this + 0x20);
	v[3].v1 = v[3].v0 + *(Real *)((char *)this + 0x24);
	v[3].u2 = v[3].u0 + *(Real *)((char *)this + 0x28);
	v[3].v2 = v[3].v0;

	if (*(unsigned char *)0x012bc2c3)
		DX8Wrapper::Set_DX8_Render_State(0x13, 2);
	else
		DX8Wrapper::Set_DX8_Render_State(0x13, 5);
	DX8Wrapper::Set_DX8_Render_State(0x14, 6);
	DX8Wrapper::Set_DX8_Render_State(0x1b, 1);
	DX8Wrapper::Apply_Render_State_Changes();
	device->v->SetRenderState(device, 0x1b, 1);
	device->v->SetPixelShader(device, 0);
	device->v->SetVertexShader(device, 0x344);
	device->v->SetTextureStageState(device, 0, 1, 3);
	device->v->SetTextureStageState(device, 0, 0xb, 0);
	device->v->SetTextureStageState(device, 0, 2, 1);
	device->v->SetTextureStageState(device, 0, 3, 2);
	device->v->SetTextureStageState(device, 0, 5, 0);
	device->v->SetTextureStageState(device, 0, 6, 0);
	device->v->SetTextureStageState(device, 0, 4, 0);
	device->v->SetTextureStageState(device, 1, 1, 1);
	device->v->SetTextureStageState(device, 1, 0xb, 1);
	device->v->SetTextureStageState(device, 1, 2, 1);
	device->v->SetTextureStageState(device, 1, 3, 1);
	device->v->SetTextureStageState(device, 1, 4, 1);
	device->v->SetTextureStageState(device, 1, 5, 1);
	device->v->SetTextureStageState(device, 1, 6, 1);
	device->v->SetTextureStageState(device, 2, 1, 5);
	device->v->SetTextureStageState(device, 2, 0x18, 0);
	device->v->SetTextureStageState(device, 2, 0xb, 2);
	device->v->SetTextureStageState(device, 2, 2, 2);
	device->v->SetTextureStageState(device, 2, 3, 2);
	device->v->SetTextureStageState(device, 2, 4, 2);
	device->v->SetTextureStageState(device, 2, 5, 2);
	device->v->SetTextureStageState(device, 2, 6, 2);
	device->v->DrawPrimitiveUP(device, 5, 2, v, sizeof(Vertex));
	reset();
	return true;
}
