// ?render@W3DSmudgeManager@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.998 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc

// W3DSmudgeManager::render, retail 0x00722BD0, 2829 bytes.
// Port of GeneralsMD W3DSmudge.cpp render() to BFME's D3D9 device slots,
// BoxDynamicVBAccessClass and the probe colour member at +0x40.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef long HRESULT;

#define SMUDGE_DRAW_SIZE 500

class Vector2
{
public:
	float X;
	float Y;
	void Set(float x, float y) { X = x; Y = y; }
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }

	friend __forceinline Vector3 operator*(const Vector3 &a, float k)
	{
		return Vector3(a.X * k, a.Y * k, a.Z * k);
	}
	friend __forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
	}
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	Vector4(void) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	Vector4(const Vector4 &v) : X(v.X), Y(v.Y), Z(v.Z), W(v.W) {}
	Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	Vector4 &operator*=(float k) { X *= k; Y *= k; Z *= k; W *= k; return *this; }
};

class Matrix3D
{
public:
	Vector4 Row[3];
	Vector4 &operator[](int i) { return Row[i]; }
	const Vector4 &operator[](int i) const { return Row[i]; }

	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = (Vector3 *)&in;
		}
		float sX = A[0][1] * v->Y;
		sX = sX + A[0][2] * v->Z;
		sX = sX + A[0][0] * v->X;
		out->X = sX + A[0][3];
		float sY = A[1][1] * v->Y;
		sY = sY + A[1][2] * v->Z;
		sY = sY + A[1][0] * v->X;
		out->Y = sY + A[1][3];
		float sZ = A[2][1] * v->Y;
		sZ = sZ + A[2][2] * v->Z;
		sZ = sZ + A[2][0] * v->X;
		out->Z = sZ + A[2][3];
	}
};

class Matrix4
{
public:
	Vector4 Row[4];

	Matrix4(void) {}
	__forceinline explicit Matrix4(bool identity)
	{
		if (identity) {
			Row[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
			Row[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			Row[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
			Row[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	Vector4 &operator[](int i) { return Row[i]; }
	const Vector4 &operator[](int i) const { return Row[i]; }

	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		Row[3] = m.Row[3];
		return *this;
	}

	__forceinline Matrix4 Transpose(void) const
	{
		Matrix4 m;
		m.Row[0] = Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]);
		m.Row[1] = Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]);
		m.Row[2] = Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]);
		m.Row[3] = Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]);
		return m;
	}

	friend __forceinline Vector4 operator*(const Matrix4 &a, const Vector3 &v)
	{
		float w = a[3][0] * v[0];
		w = w + a[3][2] * v[2];
		w = w + a[3][1] * v[1];
		w = w + a[3][3] * 1.0f;
		float z = a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * 1.0f;
		float y = a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * 1.0f;
		float x = a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * 1.0f;
		return Vector4(x, y, z, w);
	}
};

class CameraClass
{
public:
	void Get_View_Matrix(Matrix3D *set_tm);
	void Get_Projection_Matrix(Matrix4 *set_tm);
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

struct D3DSURFACE_DESC
{
	UINT Format;
	UINT Type;
	DWORD Usage;
	UINT Pool;
	UINT MultiSampleType;
	DWORD MultiSampleQuality;
	UINT Width;
	UINT Height;
};

#define BFME_SLOT(n) virtual HRESULT __stdcall unused##n(void) = 0;

struct IDirect3DBaseTexture8
{
	virtual HRESULT __stdcall QueryInterface(void) = 0;
	virtual ULONG __stdcall AddRef(void) = 0;
	virtual ULONG __stdcall Release(void) = 0;
};

struct IDirect3DTexture8 : public IDirect3DBaseTexture8
{
	BFME_SLOT(03) BFME_SLOT(04) BFME_SLOT(05) BFME_SLOT(06) BFME_SLOT(07)
	BFME_SLOT(08) BFME_SLOT(09) BFME_SLOT(10) BFME_SLOT(11) BFME_SLOT(12)
	BFME_SLOT(13) BFME_SLOT(14) BFME_SLOT(15) BFME_SLOT(16)
	virtual HRESULT __stdcall GetLevelDesc(UINT level, D3DSURFACE_DESC *desc) = 0;
};

struct IDirect3DDevice8
{
	BFME_SLOT(00) BFME_SLOT(01) BFME_SLOT(02) BFME_SLOT(03) BFME_SLOT(04)
	BFME_SLOT(05) BFME_SLOT(06) BFME_SLOT(07) BFME_SLOT(08) BFME_SLOT(09)
	BFME_SLOT(10) BFME_SLOT(11) BFME_SLOT(12) BFME_SLOT(13) BFME_SLOT(14)
	BFME_SLOT(15) BFME_SLOT(16) BFME_SLOT(17) BFME_SLOT(18) BFME_SLOT(19)
	BFME_SLOT(20) BFME_SLOT(21) BFME_SLOT(22) BFME_SLOT(23) BFME_SLOT(24)
	BFME_SLOT(25) BFME_SLOT(26) BFME_SLOT(27) BFME_SLOT(28) BFME_SLOT(29)
	BFME_SLOT(30) BFME_SLOT(31) BFME_SLOT(32) BFME_SLOT(33) BFME_SLOT(34)
	BFME_SLOT(35) BFME_SLOT(36) BFME_SLOT(37) BFME_SLOT(38) BFME_SLOT(39)
	BFME_SLOT(40) BFME_SLOT(41) BFME_SLOT(42) BFME_SLOT(43)
	virtual HRESULT __stdcall SetTransform(int state, const Matrix4 *matrix) = 0;
	BFME_SLOT(45) BFME_SLOT(46) BFME_SLOT(47) BFME_SLOT(48) BFME_SLOT(49)
	BFME_SLOT(50) BFME_SLOT(51) BFME_SLOT(52) BFME_SLOT(53) BFME_SLOT(54)
	BFME_SLOT(55) BFME_SLOT(56) BFME_SLOT(57) BFME_SLOT(58) BFME_SLOT(59)
	BFME_SLOT(60) BFME_SLOT(61) BFME_SLOT(62) BFME_SLOT(63) BFME_SLOT(64)
	virtual HRESULT __stdcall SetTexture(DWORD stage, IDirect3DBaseTexture8 *texture) = 0;
	BFME_SLOT(66)
	virtual HRESULT __stdcall SetTextureStageState(DWORD stage, DWORD type, DWORD value) = 0;
	BFME_SLOT(68)
	virtual HRESULT __stdcall SetSamplerState(DWORD sampler, DWORD type, DWORD value) = 0;
};

class W3DShaderManager
{
public:
	static IDirect3DTexture8 *getRenderTexture(void);
	static bool m_renderingToTexture;
	static bool isRenderingToTexture(void) { return m_renderingToTexture; }
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	virtual ~RefCountClass(void);
	__forceinline void Add_Ref(void)
	{
		++m_numRefs;
	}
	__forceinline void Release_Ref(void)
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs;
};

class W3DMPO
{
};

class VertexMaterialClass : public W3DMPO, public RefCountClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType type);
};

class StringClass
{
	void Get_String(int length, bool is_temp);
	void Free_String(void);

public:
	StringClass(int initial_len = 0, bool hint_temporary = false)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = m_NullChar;
	}
	~StringClass(void)
	{
		Free_String();
	}
	char *m_Buffer;
	static char m_NullChar;
	static char *m_EmptyString;
};

class ShaderClass
{
public:
	unsigned int ShaderBits;
	static bool ShaderDirty;
	static ShaderClass _PresetAlphaShader;
};

class IndexBufferClass;

class VertexFormatXYZNDUV2
{
public:
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	unsigned int diffuse;
	float u1;
	float v1;
	float u2;
	float v2;
};

class FVFInfoClass;
class VertexBufferClass;

class BoxDynamicVBAccessClass
{
	const FVFInfoClass &FVFInfo;
	UnsignedInt Type;
	UnsignedInt FVF;
	UnsignedInt Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;

public:
	BoxDynamicVBAccessClass(UnsignedInt type, UnsignedInt fvf,
		unsigned short vertex_count, UnsignedInt buffer);
	~BoxDynamicVBAccessClass(void);

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass(void);
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array(void)
		{
			return Vertices;
		}
	};
};

class DynamicVBAccessClass;

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static IDirect3DBaseTexture8 *Textures[8];
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_changes;
	static unsigned texture_stage_state_changes;
	static unsigned TextureStageStates[8][32];
	static Matrix4 render_state_world;
	static Matrix4 render_state_view;

public:
	enum {
		WORLD_CHANGED = 1 << 0,
		VIEW_CHANGED = 1 << 1,
		WORLD_IDENTITY = 1 << 18,
		VIEW_IDENTITY = 1 << 19
	};

	static void Apply_Render_State_Changes(void);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const DynamicVBAccessClass &vba);
	static void Draw_Triangles(unsigned short start_index, unsigned short polygon_count,
		unsigned short min_vertex_index, unsigned short vertex_count);
	static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &name, int state, unsigned value);

	static IDirect3DDevice8 *_Get_D3D_Device8(void)
	{
		return D3DDevice;
	}

	static __forceinline void Set_Transform(int transform, const Matrix4 &m)
	{
		switch (transform) {
		case 256:
			render_state_world = m;
			render_state_changed |= (unsigned)WORLD_CHANGED;
			render_state_changed &= ~(unsigned)WORLD_IDENTITY;
			break;
		case 2:
			render_state_view = m;
			render_state_changed |= (unsigned)VIEW_CHANGED;
			render_state_changed &= ~(unsigned)VIEW_IDENTITY;
			break;
		default:
			break;
		}
	}

	static __forceinline void Set_Material(const VertexMaterialClass *material)
	{
		if (material)
			const_cast<VertexMaterialClass *>(material)->Add_Ref();
		if (render_state.material)
			render_state.material->Release_Ref();
		render_state.material = const_cast<VertexMaterialClass *>(material);
		render_state_changed |= 0x4000;
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty &&
			shader.ShaderBits == render_state.shader.ShaderBits)
			return;

		render_state_changed |= 0x8000;
		render_state.shader = shader;
		StringClass str;
	}

	static __forceinline void Set_DX8_Texture(unsigned int stage,
		IDirect3DBaseTexture8 *texture)
	{
		if (Textures[stage] == texture)
			return;
		if (Textures[stage])
			Textures[stage]->Release();
		Textures[stage] = texture;
		if (texture)
			texture->AddRef();
		IDirect3DDevice8 *device = _Get_D3D_Device8();
		device->SetTexture(stage, texture);
		++number_of_DX8_calls;
		++texture_changes;
	}

	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned state, unsigned value)
	{
		_Get_D3D_Device8()->SetSamplerState(stage, state, value);
		++number_of_DX8_calls;
		++texture_stage_state_changes;
	}

	static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage, unsigned state, unsigned value)
	{
		if (TextureStageStates[stage][state] == value)
			return;
		if (Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Texture_Stage_State_Value_Name(value_name, state, value);
		}
		TextureStageStates[stage][state] = value;
		_Get_D3D_Device8()->SetTextureStageState(stage, state, value);
		++number_of_DX8_calls;
		++texture_stage_state_changes;
	}

	static bool SnapshotActivated;
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
};

class SortingRendererClass
{
public:
	static void Flush(void);
};

class View
{
public:
	virtual void unused00(void); virtual void unused01(void); virtual void unused02(void);
	virtual void unused03(void); virtual void unused04(void); virtual void unused05(void);
	virtual void unused06(void); virtual void unused07(void); virtual void unused08(void);
	virtual void unused09(void); virtual void unused10(void); virtual void unused11(void);
	virtual void unused12(void); virtual void unused13(void); virtual void unused14(void);
	virtual Int getWidth(void);
	virtual void unused16(void);
	virtual Int getHeight(void);
};

extern View *TheTacticalView;

struct smudgeVertex
{
	Vector3 pos;
	Vector2 uv;
};

class Smudge
{
public:
	Smudge *m_next;
	Smudge *m_prev;
	void *m_list;
	Vector3 m_pos;
	Vector2 m_offset;
	Real m_size;
	Real m_opacity;
	smudgeVertex m_verts[5];

	Smudge *Succ(void) { return m_next; }
};

class SmudgeSetNode
{
public:
	SmudgeSetNode *m_next;
	SmudgeSetNode *m_prev;
	void *m_list;
};

class SmudgeSetBase
{
public:
	virtual ~SmudgeSetBase(void);
};

class SmudgeSet : public SmudgeSetBase, public SmudgeSetNode
{
public:
	void *m_usedSmudgeTail;
	Smudge *m_usedSmudgeHead;

	SmudgeSet *Succ(void) { return static_cast<SmudgeSet *>(m_next); }
	Smudge *getUsedSmudgeListHead(void) { return m_usedSmudgeHead; }
};

class SmudgeManager
{
public:
	virtual ~SmudgeManager(void);

	Int m_hardwareSupportStatus;
	SmudgeSetNode *m_freeHead;
	SmudgeSetNode *m_usedHead;
	char m_pad10[0x14];

	SmudgeSet *usedSmudgeSetHead(void) { return static_cast<SmudgeSet *>(m_usedHead); }
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	bool testHardwareSupport(void);
	void render(RenderInfoClass &rinfo);

	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	IndexBufferClass *m_indexBuffer;
	int m_backBufferWidth;
	int m_backBufferHeight;
	unsigned int m_probeColor;
};

void W3DSmudgeManager::render(RenderInfoClass &rinfo)
{
	if (!testHardwareSupport())
		return;

	CameraClass &camera = rinfo.Camera;
	Vector3 vsVert;
	Vector4 ssVert;
	Real uvSpanX, uvSpanY;
	Vector3 vertex_offsets[4] = {
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f)
	};

	UnsignedInt vertexDiffuse[5] = {m_probeColor, m_probeColor, m_probeColor, m_probeColor, m_probeColor};

	Matrix4 proj;
	Matrix3D view;

	camera.Get_View_Matrix(&view);
	camera.Get_Projection_Matrix(&proj);

	D3DSURFACE_DESC D3DDesc;

	IDirect3DTexture8 *backTexture = W3DShaderManager::getRenderTexture();
	if (!backTexture || !W3DShaderManager::isRenderingToTexture())
		return;

	backTexture->GetLevelDesc(0, &D3DDesc);

	UnsignedInt surfaceWidth = D3DDesc.Width;
	UnsignedInt surfaceHeight = D3DDesc.Height;

	Real texClampX = (Real)TheTacticalView->getWidth() / (Real)surfaceWidth;
	Real texClampY = (Real)TheTacticalView->getHeight() / (Real)surfaceHeight;

	Real texScaleX = texClampX * 0.5f;
	Real texScaleY = texClampY * 0.5f;

	SmudgeSet *set = usedSmudgeSetHead();
	Int count = 0;

	if (set)
	{
		SortingRendererClass::Flush();
	}

	while (set)
	{
		Smudge *smudge = set->getUsedSmudgeListHead();

		while (smudge)
		{
			Matrix3D::Transform_Vector(view, smudge->m_pos, &vsVert);

			smudgeVertex *verts = smudge->m_verts;

			verts[4].pos = vsVert;

			for (Int i = 0; i < 4; i++)
			{
				verts[i].pos = vsVert + vertex_offsets[i] * smudge->m_size;
				ssVert = proj * verts[i].pos;
				Real oow = 1.0f / ssVert.W;
				ssVert *= oow;
				verts[i].uv.Set((ssVert.X + 1.0f) * texScaleX, (1.0f - ssVert.Y) * texScaleY);

				Vector2 &thisUV = verts[i].uv;

				if (thisUV.X > texClampX)
					smudge->m_offset.X = 0;
				else
				if (thisUV.X < 0)
					smudge->m_offset.X = 0;

				if (thisUV.Y > texClampY)
					smudge->m_offset.Y = 0;
				else
				if (thisUV.Y < 0)
					smudge->m_offset.Y = 0;
			}

			uvSpanX = verts[3].uv.X - verts[0].uv.X;
			uvSpanY = verts[1].uv.Y - verts[0].uv.Y;
			verts[4].uv.X = verts[0].uv.X + uvSpanX * (0.5f + smudge->m_offset.X);
			verts[4].uv.Y = verts[0].uv.Y + uvSpanY * (0.5f + smudge->m_offset.X);

			count++;
			smudge = smudge->Succ();
		}

		set = set->Succ();
	}

	if (!count)
	{
		return;
	}

	Matrix4 identity(true);
	DX8Wrapper::Set_Transform(256, identity);
	DX8Wrapper::Set_Transform(2, identity);

	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);

	DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);
	DX8Wrapper::Set_DX8_Texture(0, backTexture);
	DX8Wrapper::Set_DX8_Sampler_State(0, 1, 3);
	DX8Wrapper::Set_DX8_Sampler_State(0, 2, 3);
	DX8Wrapper::Set_DX8_Sampler_State(0, 3, 3);
	DX8Wrapper::Set_DX8_Sampler_State(0, 5, 2);
	DX8Wrapper::Set_DX8_Sampler_State(0, 6, 2);
	DX8Wrapper::Set_DX8_Sampler_State(0, 7, 0);

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	if (vmat)
		vmat->Release_Ref();
	DX8Wrapper::Apply_Render_State_Changes();

	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 3);

	Int smudgesRemaining = count;
	set = usedSmudgeSetHead();
	Smudge *remainingSmudgeStart = set->getUsedSmudgeListHead();

	while (smudgesRemaining)
	{
		count = smudgesRemaining;

		if (count > SMUDGE_DRAW_SIZE)
			count = SMUDGE_DRAW_SIZE;

		Int smudgesInRenderBatch = 0;

		BoxDynamicVBAccessClass vb_access(2, 5, count * 5, 0);
		{
			BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
			VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();

			while (set)
			{
				Smudge *smudge = remainingSmudgeStart;

				while (smudge)
				{
					smudgeVertex *smVerts = smudge->m_verts;

					if (smudgesInRenderBatch >= count)
					{
						remainingSmudgeStart = smudge;
						goto flushSmudges;
					}

					vertexDiffuse[4] = ((Int)(smudge->m_opacity * 255.0f) << 24) | m_probeColor;

					for (Int i = 0; i < 5; i++)
					{
						verts->x = smVerts->pos.X;
						verts->y = smVerts->pos.Y;
						verts->z = smVerts->pos.Z;
						verts->nx = 0;
						verts->ny = 0;
						verts->nz = 0;
						verts->diffuse = vertexDiffuse[i];
						verts->u1 = smVerts->uv.X;
						verts->v1 = smVerts->uv.Y;
						verts->u2 = 0;
						verts->v2 = 0;
						verts++;
						smVerts++;
					}

					smudgesInRenderBatch++;
					smudge = smudge->Succ();
				}

				set = set->Succ();

				if (set)
					remainingSmudgeStart = set->getUsedSmudgeListHead();
			}
flushSmudges:
			DX8Wrapper::Set_Vertex_Buffer(*(DynamicVBAccessClass *)&vb_access);
		}

		DX8Wrapper::Draw_Triangles(0, smudgesInRenderBatch * 4, 0, smudgesInRenderBatch * 5);

		smudgesRemaining -= smudgesInRenderBatch;
	}

	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 4);
}
