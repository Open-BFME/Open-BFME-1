// ?Render@W3DStatusCircle@@UAEXAAVRenderInfoClass@@@Z
// Retail 0x00726290: BFME moved the three render-resource members from the
// Zero Hour layout. Keep the object mirror local until the real body lands.
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef bool Bool;

class RenderInfoClass;
class IndexBufferClass;
class VertexBufferClass;
class TextureBaseClass;

class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;
	void Get_String(int, bool);
	void Free_String();

public:
	__forceinline StringClass(int n = 0, bool temporary = false)
		: m_Buffer(m_EmptyString)
	{
		Get_String(n, temporary);
		m_Buffer[0] = m_NullChar;
	}
	struct LateTag {};
	__forceinline StringClass(int n, bool temporary, LateTag)
		: m_Buffer(m_EmptyString)
	{
		Get_String(n, temporary);
		m_Buffer[0] = *(volatile char *)&m_NullChar;
	}
	struct EarlyTag {};
	__forceinline StringClass(int n, bool temporary, EarlyTag)
		: m_Buffer(m_EmptyString)
	{
		Get_String(n, temporary);
		char nullChar = m_NullChar;
		m_Buffer[0] = nullChar;
	}
	struct VolatileEarlyTag {};
	__forceinline StringClass(int n, bool temporary, VolatileEarlyTag)
		: m_Buffer(m_EmptyString)
	{
		Get_String(n, temporary);
		m_Buffer[0] = *(volatile char *)&m_NullChar;
	}
	__forceinline ~StringClass()
	{
		Free_String();
	}
};

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	void Release_Ref()
	{
		if (!--refs)
			Delete_This();
	}
};

class TextureClass
{
public:
	void Release_Ref();
};

class TextureHandle
{
public:
	TextureClass *p;
	TextureHandle() : p(0) {}
	~TextureHandle()
	{
		if (p)
			p->Release_Ref();
	}
};

void BoxSetTexture(unsigned int, TextureBaseClass *&);

struct Device;
struct DeviceVtable
{
	char pad[0xe4];
	int (__stdcall *SetRenderState)(Device *, unsigned long, unsigned);
};
struct Device
{
	DeviceVtable *v;
};

extern VertexMaterialClass *ScreenMaterial;
extern unsigned TheBoxTextureDirtyMask;
extern bool ScreenSnapshot;
extern unsigned ScreenRenderStates[];
extern unsigned ScreenCurrentShader;
extern Device *ScreenDevice;
extern unsigned ScreenStateChanges;
extern unsigned ScreenTotalChanges;

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
	static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned);
	static void Draw_Triangles(unsigned short, unsigned short, unsigned short, unsigned short);
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
};

extern char *TheGameLogic;
extern char *TheWritableGlobalData;
extern char *TheGameEngine;
extern char *TheScriptEngine;
extern bool g_w3dStatusCircleNeedUpdate;
extern float g_worldMatrix[16];
extern unsigned char g_rva007A2330Flag;
extern float g_bfmeDefaultBU;
extern const float g_bfmeScaleB3;
extern const Real BfmeZeroRange;

void j_00008d5f();
void j_0003d5a0();
void j_00046759();

#pragma comment(linker, "/alternatename:?initData@W3DStatusCircle@@IAEHXZ=?j_00008d5f@@YAXXZ")

struct Rva00726290Vector3
{
	Real x;
	Real y;
	Real z;
	Rva00726290Vector3(Real x_, Real y_, Real z_)
		: x(x_), y(y_), z(z_) {}
};

struct Rva00726290Matrix3D
{
	Real row[12];

	__forceinline Rva00726290Matrix3D(Bool init)
	{
		if (init)
			Make_Identity();
	}
	__forceinline void Make_Identity()
	{
		row[0] = 1.0f; row[1] = 0.0f; row[2] = 0.0f; row[3] = 0.0f;
		row[4] = 0.0f; row[5] = 1.0f; row[6] = 0.0f; row[7] = 0.0f;
		row[8] = 0.0f; row[9] = 0.0f; row[10] = 1.0f; row[11] = 0.0f;
	}
	__forceinline void Set_Translation(const Rva00726290Vector3 &t)
	{
		row[3] = t.x;
		row[7] = t.y;
		row[11] = t.z;
	}
};

__forceinline void Rva00726290SetWorld(const Rva00726290Matrix3D &m)
{
	g_worldMatrix[0] = m.row[0];
	g_worldMatrix[1] = m.row[4];
	g_worldMatrix[2] = m.row[8];
	g_worldMatrix[3] = 0.0f;
	g_worldMatrix[4] = m.row[1];
	g_worldMatrix[5] = m.row[5];
	g_worldMatrix[6] = m.row[9];
	g_worldMatrix[7] = 0.0f;
	g_worldMatrix[8] = m.row[2];
	g_worldMatrix[9] = m.row[6];
	g_worldMatrix[10] = m.row[10];
	g_worldMatrix[11] = 0.0f;
	g_worldMatrix[12] = m.row[3];
	g_worldMatrix[13] = m.row[7];
	g_worldMatrix[14] = m.row[11];
	g_worldMatrix[15] = 1.0f;
	TheBoxTextureDirtyMask = (TheBoxTextureDirtyMask & 0xfffbffff) | 1;
}

class Rva00726290W3DStatusCircle;
class W3DStatusCircle
{
	friend class Rva00726290W3DStatusCircle;

protected:
	int initData();
	int updateCircleVB();
	int updateScreenVB(int);
};

class Rva00726290W3DStatusCircle
{
public:
	virtual void Render(RenderInfoClass &);
};

#define BFME_SET_RS(state_, value_) do { \
	if (ScreenRenderStates[(state_)] != (unsigned)(value_)) { \
		if (ScreenSnapshot) { \
			StringClass valueName(0, true, StringClass::VolatileEarlyTag()); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(valueName, (state_), (value_)); \
		} \
		ScreenRenderStates[(state_)] = (value_); \
		ScreenDevice->v->SetRenderState(ScreenDevice, (state_), (value_)); \
		++ScreenTotalChanges; \
		++ScreenStateChanges; \
	} \
} while (0)

// ?Render@W3DStatusCircle@@UAEXAAVRenderInfoClass@@@Z
void Rva00726290W3DStatusCircle::Render(RenderInfoClass &)
{
	if (*(Int *)(TheGameLogic + 0x10c) == 8)
		return;

	IndexBufferClass *&indexBuffer = *(IndexBufferClass **)((char *)this + 0xd8);
	if (indexBuffer == 0) {
		((W3DStatusCircle *)this)->initData();
	}
	if (indexBuffer == 0)
		return;

	Bool setIndex = false;
	Rva00726290Matrix3D tm(true);
	if (*(Bool *)(TheWritableGlobalData + 0xa9c) &&
		*(Int *)(TheGameLogic + 0x10c) != 4) {
		if (g_w3dStatusCircleNeedUpdate)
			((W3DStatusCircle *)this)->updateCircleVB();

		VertexMaterialClass *vmat = *(VertexMaterialClass **)((char *)this + 0xe0);
		if (vmat)
			++vmat->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		TheBoxTextureDirtyMask |= 0x4000;
		if (g_rva007A2330Flag ||
			*(unsigned *)((char *)this + 0xdc) != ScreenCurrentShader) {
			unsigned shader = *(unsigned *)((char *)this + 0xdc);
			ScreenCurrentShader = shader;
			TheBoxTextureDirtyMask |= 0x8000;
			StringClass shaderDescription;
		}
		{
			TextureHandle texture;
			BoxSetTexture(0, (TextureBaseClass *&)texture.p);
		}
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(
			*(VertexBufferClass **)((char *)this + 0xe4), 0);

		Rva00726290Vector3 vec(0.95f, 0.67f, 0.0f);
		tm.Set_Translation(vec);
		Rva00726290SetWorld(tm);
		setIndex = true;
		DX8Wrapper::Draw_Triangles(
			0, 20, 0,
			(unsigned short)(*(unsigned short *)((char *)this + 0xc8) * 3));
	}

	Int &fade = *(Int *)((char *)this + 0xcc);
	Real &previousIntensity = *(Real *)((char *)this + 0xd0);
	Real &currentIntensity = *(Real *)((char *)this + 0xd4);
	if (*(Int *)(TheGameEngine + 0x30) == 1) {
		previousIntensity = currentIntensity;
		fade = *(Int *)(TheScriptEngine + 0x170b4);
		if (fade == 0) {
			currentIntensity = 0.0f;
			return;
		}
		currentIntensity = *(Real *)(TheScriptEngine + 0x170c4);
		if (*(Bool *)(TheScriptEngine + 0x170b8))
			previousIntensity = currentIntensity;
	}
	if (fade == 0)
		return;

	if (!setIndex) {
		VertexMaterialClass *vmat = *(VertexMaterialClass **)((char *)this + 0xe0);
		if (vmat)
			++vmat->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		TheBoxTextureDirtyMask |= 0x4000;
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		{
			TextureHandle texture;
			BoxSetTexture(0, (TextureBaseClass *&)texture.p);
		}
	}

	Real intensity = currentIntensity;
	Real frameFraction = *(Real *)(TheGameEngine + 0x38);
	if (previousIntensity < BfmeZeroRange) {
		previousIntensity = intensity;
	} else if (currentIntensity != previousIntensity) {
		intensity = (g_bfmeDefaultBU - frameFraction) * previousIntensity +
			frameFraction * currentIntensity;
	} else {
		intensity = previousIntensity;
	}
	intensity *= g_bfmeScaleB3;
	Int clr = (Int)intensity;
	Int diffuse = (0xff << 24) | (clr << 16) | (clr << 8) | clr;
	((W3DStatusCircle *)this)->updateScreenVB(diffuse);

	tm.Make_Identity();
	Rva00726290SetWorld(tm);
	unsigned shaderBits = 0x00114037;
	if (g_rva007A2330Flag || shaderBits != ScreenCurrentShader) {
		ScreenCurrentShader = shaderBits;
		TheBoxTextureDirtyMask |= 0x8000;
		StringClass shaderDescription(0, false, StringClass::LateTag());
	}
	DX8Wrapper::Set_Vertex_Buffer(
		*(VertexBufferClass **)((char *)this + 0xe8), 0);
	DX8Wrapper::Apply_Render_State_Changes();

	switch (fade) {
		default:
		case 2:
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case 1:
			BFME_SET_RS(0xab, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			BFME_SET_RS(0xab, 1);
			break;
		case 3:
			BFME_SET_RS(0x13, 9);
			BFME_SET_RS(0x14, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case 4:
			BFME_SET_RS(0x13, 1);
			BFME_SET_RS(0x14, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
	}
	g_rva007A2330Flag = 1;
}
