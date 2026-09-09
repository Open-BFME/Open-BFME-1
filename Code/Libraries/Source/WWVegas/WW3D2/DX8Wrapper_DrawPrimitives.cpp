// cl: /DNDEBUG /MD /EHsc- /Oy
// readable body of ?Draw_Strip@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp

// DX8Wrapper::Draw (0x00906B40), Draw_Triangles (0x00906DF0), and Draw_Strip
// (0x00906E40). Draw is the BFME six-argument primitive helper; the two small
// wrappers forward their four arguments with a leading mode constant - 4 for
// triangles, 5 for strips - and a trailing 1. The helper's identity is proved
// by those named callers, while its boundary is the complete 526-byte body
// ending at 0x00906D4D immediately before the named 0x00906D70 sibling.

typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned long UnsignedLong;
typedef long HRESULT;

enum D3DPRIMITIVETYPE
{
	D3DPT_TRIANGLELIST = 4,
	D3DPT_TRIANGLESTRIP = 5,
	D3DPT_TRIANGLEFAN = 6
};

// The BFME executable keeps the D3D8 type names but calls the device through
// its D3D9-shaped draw ABI. This TU-local interface deliberately models only
// the vtable order needed by Draw: ValidateDevice is slot 70, ten reserved
// entries follow it, and the two draw calls are slots 81 and 82. The common
// d3d8 shim is the SDK layout (ValidateDevice slot 71 and five-argument
// DrawIndexedPrimitive), so using it here would make the source claim the
// wrong ABI and the wrong call offsets.
#define DX8_DRAW_DUMMY(n) virtual HRESULT __stdcall dummy##n() = 0;
struct IDirect3DDevice8
{
	DX8_DRAW_DUMMY(00) DX8_DRAW_DUMMY(01) DX8_DRAW_DUMMY(02) DX8_DRAW_DUMMY(03)
	DX8_DRAW_DUMMY(04) DX8_DRAW_DUMMY(05) DX8_DRAW_DUMMY(06) DX8_DRAW_DUMMY(07)
	DX8_DRAW_DUMMY(08) DX8_DRAW_DUMMY(09) DX8_DRAW_DUMMY(10) DX8_DRAW_DUMMY(11)
	DX8_DRAW_DUMMY(12) DX8_DRAW_DUMMY(13) DX8_DRAW_DUMMY(14) DX8_DRAW_DUMMY(15)
	DX8_DRAW_DUMMY(16) DX8_DRAW_DUMMY(17) DX8_DRAW_DUMMY(18) DX8_DRAW_DUMMY(19)
	DX8_DRAW_DUMMY(20) DX8_DRAW_DUMMY(21) DX8_DRAW_DUMMY(22) DX8_DRAW_DUMMY(23)
	DX8_DRAW_DUMMY(24) DX8_DRAW_DUMMY(25) DX8_DRAW_DUMMY(26) DX8_DRAW_DUMMY(27)
	DX8_DRAW_DUMMY(28) DX8_DRAW_DUMMY(29) DX8_DRAW_DUMMY(30) DX8_DRAW_DUMMY(31)
	DX8_DRAW_DUMMY(32) DX8_DRAW_DUMMY(33) DX8_DRAW_DUMMY(34) DX8_DRAW_DUMMY(35)
	DX8_DRAW_DUMMY(36) DX8_DRAW_DUMMY(37) DX8_DRAW_DUMMY(38) DX8_DRAW_DUMMY(39)
	DX8_DRAW_DUMMY(40) DX8_DRAW_DUMMY(41) DX8_DRAW_DUMMY(42) DX8_DRAW_DUMMY(43)
	virtual HRESULT __stdcall SetTransform(UnsignedInt, void *) = 0;
	DX8_DRAW_DUMMY(45) DX8_DRAW_DUMMY(46) DX8_DRAW_DUMMY(47)
	DX8_DRAW_DUMMY(48) DX8_DRAW_DUMMY(49) DX8_DRAW_DUMMY(50)
	virtual HRESULT __stdcall SetLight(UnsignedInt, void *) = 0;
	DX8_DRAW_DUMMY(52)
	virtual HRESULT __stdcall LightEnable(UnsignedInt, UnsignedInt) = 0;
	DX8_DRAW_DUMMY(54) DX8_DRAW_DUMMY(55)
	DX8_DRAW_DUMMY(56) DX8_DRAW_DUMMY(57) DX8_DRAW_DUMMY(58) DX8_DRAW_DUMMY(59)
	DX8_DRAW_DUMMY(60) DX8_DRAW_DUMMY(61) DX8_DRAW_DUMMY(62) DX8_DRAW_DUMMY(63)
	DX8_DRAW_DUMMY(64) DX8_DRAW_DUMMY(65) DX8_DRAW_DUMMY(66) DX8_DRAW_DUMMY(67)
	DX8_DRAW_DUMMY(68) DX8_DRAW_DUMMY(69)
	virtual HRESULT __stdcall ValidateDevice(UnsignedLong *) = 0;
	DX8_DRAW_DUMMY(71) DX8_DRAW_DUMMY(72) DX8_DRAW_DUMMY(73) DX8_DRAW_DUMMY(74)
	DX8_DRAW_DUMMY(75) DX8_DRAW_DUMMY(76) DX8_DRAW_DUMMY(77) DX8_DRAW_DUMMY(78)
	DX8_DRAW_DUMMY(79) DX8_DRAW_DUMMY(80)
	virtual HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE, UnsignedInt, UnsignedInt) = 0;
	virtual HRESULT __stdcall DrawIndexedPrimitive(
		D3DPRIMITIVETYPE, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt) = 0;
	DX8_DRAW_DUMMY(83) DX8_DRAW_DUMMY(84) DX8_DRAW_DUMMY(85) DX8_DRAW_DUMMY(86)
	DX8_DRAW_DUMMY(87) DX8_DRAW_DUMMY(88)
	virtual HRESULT __stdcall SetFVF(UnsignedInt) = 0;
	DX8_DRAW_DUMMY(90) DX8_DRAW_DUMMY(91) DX8_DRAW_DUMMY(92) DX8_DRAW_DUMMY(93)
	DX8_DRAW_DUMMY(94) DX8_DRAW_DUMMY(95) DX8_DRAW_DUMMY(96) DX8_DRAW_DUMMY(97)
	DX8_DRAW_DUMMY(98) DX8_DRAW_DUMMY(99)
	virtual HRESULT __stdcall SetStreamSource(
		UnsignedInt, void *, UnsignedInt, UnsignedInt) = 0;
	DX8_DRAW_DUMMY(101) DX8_DRAW_DUMMY(102) DX8_DRAW_DUMMY(103)
	virtual HRESULT __stdcall SetIndices(void *) = 0;
};
#undef DX8_DRAW_DUMMY

class Vector3
{
	public:
	float X, Y, Z;
};

class ShaderClass
{
	friend class DX8Wrapper;

	UnsignedInt bits;
	void Apply();
};

class VertexMaterialClass
{
	friend class DX8Wrapper;

	void Apply() const;
	static void Apply_Null();

public:
	void Get_Emissive(Vector3 *set) const;
};

class TextureClass;
struct BfmeDynamicVBSlot;

template<class T>
class RefCountPtr
{
public:
	void Apply(UnsignedInt stage);

private:
	T *Referent;
};

struct BfmeApplyCapsView
{
	char unused[0x278];
	int max_textures;
};

struct BfmeApplyLight
{
	char bytes[0x68];
};

struct BfmeApplyMatrix
{
	char bytes[0x40];
};

class BfmeApplyVertexBufferView;
class BfmeApplyIndexBufferView;

// The getter is inline in the W3D vertex-buffer header. Its only field used by
// this body is the measured WORD at +0x0c, so this TU-local view preserves the
// real access without importing the whole DX8 header graph.
class VertexBufferClass
{
	public:
	char unused[0x0c];
	UnsignedShort vertex_count;
	char unused_to_fvf[0x06];
	BfmeDynamicVBSlot *FVFInfo;
	unsigned char explicit_size;
	unsigned char padding[3];

	UnsignedShort Get_Vertex_Count() const { return vertex_count; }
	const BfmeDynamicVBSlot &FVF_Info() const { return *FVFInfo; }
};

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
	RefCountPtr<TextureClass> Textures[8];
	BfmeApplyLight Lights[4];
	unsigned char LightEnable[4];
	BfmeApplyMatrix world;
	BfmeApplyMatrix view;
	UnsignedInt vertex_buffer_types[2];
	UnsignedInt index_buffer_type;
	UnsignedShort vba_offset;
	UnsignedShort vba_count;
	UnsignedShort iba_offset;
	VertexBufferClass *vertex_buffers[2];
	void *index_buffer;
	UnsignedShort index_base_offset;
};

// The conversion uses the already matched BoxDynamicVBAccessClass and
// DynamicIBAccessClass bodies.  Their declarations are TU-local in their
// owning source files, so this source carries only the proven retail layouts
// needed by this caller.  In particular, the Box FVF table is the BFME
// 0x40-byte slot array used by its matched constructor; the stride is at +4.
struct BfmeDynamicVBSlot
{
	UnsignedInt fvf;
	UnsignedInt fvf_size;

	UnsignedInt Get_FVF() const { return fvf; }
	UnsignedInt Get_FVF_Size() const { return fvf_size; }
};

// BFME's DX8 vertex object fields used by the render-state helper are at
// +0x14 (FVF record), +0x18 (explicit-size marker), and +0x1c (D3D buffer).
class BfmeApplyVertexBufferView : public VertexBufferClass
{
public:
	void *VertexBuffer;
	const BfmeDynamicVBSlot &FVF_Info() const { return *FVFInfo; }
	void *Get_DX8_Vertex_Buffer() const { return VertexBuffer; }
};

// The dynamic index object exposes its D3D index buffer at +0x14 in the
// matched DX8 index-buffer access bodies.
class BfmeApplyIndexBufferView
{
	char unused[0x14];

public:
	void *IndexBuffer;
};

struct VertexFormatXYZNDUV2
{
	float x, y, z;
	float nx, ny, nz;
	UnsignedInt diffuse;
	float u1, v1, u2, v2;
};

class BoxVertexBufferClass
{
	char unused[0x1c];
	void *vertex_buffer;

public:
	void *Get_DX8_Vertex_Buffer() const { return vertex_buffer; }
};

class DX8Wrapper;

class BfmeSortingVertexBufferClass
{
	char unused[0x1c];

public:
	struct VertexFormatXYZNDUV2 *vertex_buffer;
};

class BoxDynamicVBAccessClass
{
	friend class DX8Wrapper;

	BfmeDynamicVBSlot *FVFInfo;
	UnsignedInt Type;
	UnsignedInt FVF;
	UnsignedInt Start;
	UnsignedShort VertexCount;
	UnsignedShort VertexBufferOffset;
	BoxVertexBufferClass *VertexBuffer;

public:
	BoxDynamicVBAccessClass(
		UnsignedInt type, UnsignedInt fvf, UnsignedShort vertex_count, UnsignedInt start);
	~BoxDynamicVBAccessClass();

	const BfmeDynamicVBSlot &FVF_Info() const { return *FVFInfo; }

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		struct VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		struct VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

class BfmeDynamicIndexBufferClass
{
	char unused[0x14];
	void *index_buffer;

public:
	void *Get_DX8_Index_Buffer() const { return index_buffer; }
};

class BfmeSortingIndexBufferClass
{
	char unused[0x14];

public:
	UnsignedShort *index_buffer;
};

class DynamicIBAccessClass
{
	friend class DX8Wrapper;

	UnsignedInt Type;
	UnsignedShort IndexCount;
	UnsignedShort IndexBufferOffset;
	BfmeDynamicIndexBufferClass *IndexBuffer;

public:
	DynamicIBAccessClass(UnsignedShort type, UnsignedShort index_count);
	~DynamicIBAccessClass();

	class WriteLockClass
	{
		DynamicIBAccessClass *DynamicIBAccess;
		UnsignedShort *Indices;

	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
		UnsignedShort *Get_Index_Array() { return Indices; }
	};
};

namespace Debug_Statistics
{
	void Record_DX8_Polys_And_Vertices(
		int polygon_count, int vertex_count, const ShaderClass &shader);
}

// BFME's image has a second draw-enable byte alongside DX8Wrapper's normal
// triangle-enable flag. It is the existing WW3D SnapshotActivated static; the
// address-derived material flag is the same global already named by
// SmallLeafBodies2.cpp, not a new identity claim.
class WW3D
{
	static bool SnapshotActivated;

public:
	static bool Is_Snapshot_Activated() { return SnapshotActivated; }
};

extern unsigned char g_Va0133F42C;
extern float g_bfmeScaleBK;
extern unsigned number_of_DX8_calls;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
	enum ChangedStates
	{
		WORLD_CHANGED = 1 << 0,
		VIEW_CHANGED = 1 << 1,
		LIGHT0_CHANGED = 1 << 2,
		LIGHT1_CHANGED = 1 << 3,
		LIGHT2_CHANGED = 1 << 4,
		LIGHT3_CHANGED = 1 << 5,
		TEXTURE0_CHANGED = 1 << 6,
		MATERIAL_CHANGED = 1 << 14,
		SHADER_CHANGED = 1 << 15,
		VERTEX_BUFFER_CHANGED = 1 << 16,
		INDEX_BUFFER_CHANGED = 1 << 17,
		WORLD_IDENTITY = 1 << 18,
		VIEW_IDENTITY = 1 << 19
	};

	enum BufferType
	{
		BUFFER_TYPE_DX8,
		BUFFER_TYPE_SORTING,
		BUFFER_TYPE_DYNAMIC_DX8,
		BUFFER_TYPE_DYNAMIC_SORTING,
		BUFFER_TYPE_INVALID
	};

	static bool _EnableTriangleDraw;
	static unsigned DrawPolygonLowBoundLimit;
	static IDirect3DDevice8 *D3DDevice;
	static BfmeApplyCapsView *CurrentCaps;
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static unsigned matrix_changes;
	static unsigned vertex_buffer_changes;
	static unsigned index_buffer_changes;
	static unsigned light_changes;
	static unsigned draw_calls;
	static unsigned char CurrentDX8LightEnables[4];

	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static bool _Is_Triangle_Draw_Enabled() { return _EnableTriangleDraw; }
	static void Apply_Render_State_Changes();
	static void Draw_Sorting_IB_VB(
		unsigned primitive_type,
		UnsignedShort start_index,
		UnsignedShort polygon_count,
		UnsignedShort min_vertex_index,
		UnsignedShort vertex_count);

public:
	static void Draw_Triangles( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d );
	static void Draw_Strip( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d );

private:
	static void Draw(
		int mode,
		UnsignedShort start_index,
		UnsignedShort polygon_count,
		UnsignedShort min_vertex_index,
		UnsignedShort vertex_count,
		int indexed_draw);
};

// ?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ
void DX8Wrapper::Apply_Render_State_Changes()
{
	if (!render_state_changed)
		return;

	if (render_state_changed & SHADER_CHANGED)
		render_state.shader.Apply();

	unsigned mask = TEXTURE0_CHANGED;
	for (int index = 0; index < CurrentCaps->max_textures; ++index, mask <<= 1) {
		if (render_state_changed & mask)
			render_state.Textures[index].Apply(index);
	}

	if (render_state_changed & MATERIAL_CHANGED) {
		VertexMaterialClass *material = render_state.material;
		if (material)
			material->Apply();
		else
			VertexMaterialClass::Apply_Null();
	}

	if (render_state_changed & (LIGHT0_CHANGED | LIGHT1_CHANGED |
		LIGHT2_CHANGED | LIGHT3_CHANGED)) {
		unsigned mask = LIGHT0_CHANGED;
		unsigned index = 0;
		unsigned count = 4;
		BfmeApplyLight *light = render_state.Lights;
		do {
			if (render_state_changed & mask) {
				if (render_state.LightEnable[index]) {
					if (light) {
						light_changes++;
						D3DDevice->SetLight(index, light);
						number_of_DX8_calls++;
						D3DDevice->LightEnable(index, 1);
						number_of_DX8_calls++;
						CurrentDX8LightEnables[index] = 1;
					}
					else if (CurrentDX8LightEnables[index]) {
						light_changes++;
						CurrentDX8LightEnables[index] = 0;
						D3DDevice->LightEnable(index, 0);
						number_of_DX8_calls++;
					}
				}
				else if (CurrentDX8LightEnables[index]) {
					light_changes++;
					CurrentDX8LightEnables[index] = 0;
					D3DDevice->LightEnable(index, 0);
					number_of_DX8_calls++;
				}
			}
			++index;
			light = reinterpret_cast<BfmeApplyLight *>(
				reinterpret_cast<char *>(light) + sizeof(BfmeApplyLight));
			mask <<= 1;
		} while (--count);
	}

	if (render_state_changed & WORLD_CHANGED) {
		matrix_changes++;
		D3DDevice->SetTransform(0x100, &render_state.world);
		number_of_DX8_calls++;
	}
	if (render_state_changed & VIEW_CHANGED) {
		matrix_changes++;
		D3DDevice->SetTransform(2, &render_state.view);
		number_of_DX8_calls++;
	}

	if (render_state_changed & VERTEX_BUFFER_CHANGED) {
		for (unsigned index = 0; index < 2; ++index) {
			if (render_state.vertex_buffers[index]) {
				switch (render_state.vertex_buffer_types[index]) {
				case BUFFER_TYPE_DX8:
				case BUFFER_TYPE_DYNAMIC_DX8: {
					IDirect3DDevice8 *device = D3DDevice;
					device->SetStreamSource(
						index,
						static_cast<BfmeApplyVertexBufferView *>(
							render_state.vertex_buffers[index])->Get_DX8_Vertex_Buffer(),
						0,
						render_state.vertex_buffers[index]->FVF_Info().Get_FVF_Size());
					number_of_DX8_calls++;
					vertex_buffer_changes++;
					if (!static_cast<BfmeApplyVertexBufferView *>(
							render_state.vertex_buffers[index])->explicit_size) {
						D3DDevice->SetFVF(
							render_state.vertex_buffers[index]->FVF_Info().Get_FVF());
						number_of_DX8_calls++;
					}
					break;
				}
				default:
					break;
				}
			}
			else {
				D3DDevice->SetStreamSource(index, 0, 0, 0);
				number_of_DX8_calls++;
				vertex_buffer_changes++;
			}
		}
	}

	if (render_state_changed & INDEX_BUFFER_CHANGED) {
		BfmeApplyIndexBufferView *index_buffer =
			reinterpret_cast<BfmeApplyIndexBufferView *>(render_state.index_buffer);
		if (index_buffer) {
			switch (render_state.index_buffer_type) {
			case BUFFER_TYPE_DX8:
			case BUFFER_TYPE_DYNAMIC_DX8:
				D3DDevice->SetIndices(index_buffer->IndexBuffer);
				break;
			default:
				goto finish;
			}
		}
		else {
			D3DDevice->SetIndices(0);
		}
		number_of_DX8_calls++;
		index_buffer_changes++;
	}

finish:
	render_state_changed &= WORLD_IDENTITY | VIEW_IDENTITY;
}

// ?Draw_Sorting_IB_VB@DX8Wrapper@@CAXIGGGG@Z
void DX8Wrapper::Draw_Sorting_IB_VB(
	unsigned primitive_type,
	UnsignedShort start_index,
	UnsignedShort polygon_count,
	UnsignedShort min_vertex_index,
	UnsignedShort vertex_count)
{
	// Sorting buffers are copied into the BFME dynamic DX8 buffers before the
	// device draw.  The two access classes and their lock lifetimes are the
	// matched retail bodies listed above; only their ABI views are local here.
	BoxDynamicVBAccessClass dyn_vb_access(
		BUFFER_TYPE_DYNAMIC_DX8, 5, vertex_count, 0);
	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&dyn_vb_access);
		VertexFormatXYZNDUV2 *src =
			reinterpret_cast<BfmeSortingVertexBufferClass *>(render_state.vertex_buffers[0])->vertex_buffer;
		VertexFormatXYZNDUV2 *dest = lock.Get_Formatted_Vertex_Array();
		src += render_state.vba_offset + render_state.index_base_offset + min_vertex_index;
		UnsignedInt size = dyn_vb_access.FVF_Info().Get_FVF_Size() * vertex_count / sizeof(UnsignedInt);
		UnsignedInt *dest_u = reinterpret_cast<UnsignedInt *>(dest);
		UnsignedInt *src_u = reinterpret_cast<UnsignedInt *>(src);

		for (UnsignedInt i = 0; i < size; ++i) {
			*dest_u++ = *src_u++;
		}
	}

	_Get_D3D_Device8()->SetStreamSource(
		0,
		dyn_vb_access.VertexBuffer->Get_DX8_Vertex_Buffer(),
		0,
		dyn_vb_access.FVF_Info().Get_FVF_Size());
	number_of_DX8_calls++;

	UnsignedInt fvf = dyn_vb_access.FVF_Info().Get_FVF();
	if (fvf != 0) {
		_Get_D3D_Device8()->SetFVF(fvf);
		number_of_DX8_calls++;
	}
	vertex_buffer_changes++;

	UnsignedInt index_count = 0;
	switch (primitive_type) {
	case D3DPT_TRIANGLELIST:
		index_count = polygon_count * 3;
		break;
	case D3DPT_TRIANGLESTRIP:
		index_count = polygon_count + 2;
		break;
	case D3DPT_TRIANGLEFAN:
		index_count = polygon_count + 2;
		break;
	default:
		break;
	}

	DynamicIBAccessClass dyn_ib_access(BUFFER_TYPE_DYNAMIC_DX8, index_count);
	{
		DynamicIBAccessClass::WriteLockClass lock(&dyn_ib_access);
		UnsignedShort *dest = lock.Get_Index_Array();
		UnsignedShort *src =
			reinterpret_cast<BfmeSortingIndexBufferClass *>(render_state.index_buffer)->index_buffer;
		src += render_state.iba_offset + start_index;

		for (UnsignedShort i = 0; i < index_count; ++i) {
			UnsignedShort index = *src++;
			index -= min_vertex_index;
			*dest++ = index;
		}
	}

	_Get_D3D_Device8()->SetIndices(dyn_ib_access.IndexBuffer->Get_DX8_Index_Buffer());
	number_of_DX8_calls++;
	index_buffer_changes++;
	draw_calls++;
	_Get_D3D_Device8()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		dyn_vb_access.VertexBufferOffset,
		0,
		vertex_count,
		dyn_ib_access.IndexBufferOffset,
		polygon_count);
	number_of_DX8_calls++;
	Debug_Statistics::Record_DX8_Polys_And_Vertices(polygon_count, vertex_count, render_state.shader);
}

// ?Draw@DX8Wrapper@@CAXHGGGGH@Z
void DX8Wrapper::Draw(
	int primitive_type,
	UnsignedShort start_index,
	UnsignedShort polygon_count,
	UnsignedShort min_vertex_index,
	UnsignedShort vertex_count,
	int indexed_draw)
{
	if (DrawPolygonLowBoundLimit && DrawPolygonLowBoundLimit >= polygon_count) return;

	// When this material filter is enabled, skip a missing material or one
	// whose three emissive components are all below the global threshold.
	// Preserve the short-circuit comparisons, including their NaN behavior.
	if (g_Va0133F42C) {
		VertexMaterialClass *material = render_state.material;
		if (!material) return;
		Vector3 emissive;
		material->Get_Emissive(&emissive);
		if (emissive.X < g_bfmeScaleBK
			&& emissive.Y < g_bfmeScaleBK
			&& emissive.Z < g_bfmeScaleBK) return;
	}

	Apply_Render_State_Changes();
	if (!_Is_Triangle_Draw_Enabled()) return;
	if (WW3D::Is_Snapshot_Activated()) {
		UnsignedLong passes = 0;
		D3DDevice->ValidateDevice(&passes);
	}

	if (vertex_count < 3) {
		min_vertex_index = 0;
		switch (render_state.vertex_buffer_types[0]) {
		case BUFFER_TYPE_DX8:
		case BUFFER_TYPE_SORTING:
			vertex_count = render_state.vertex_buffers[0]->Get_Vertex_Count()
				- render_state.index_base_offset
				- render_state.vba_offset
				- min_vertex_index;
			break;
		case BUFFER_TYPE_DYNAMIC_DX8:
		case BUFFER_TYPE_DYNAMIC_SORTING:
			vertex_count = render_state.vba_count;
			break;
		}
	}

	if (!*(unsigned char *)&indexed_draw) {
		Debug_Statistics::Record_DX8_Polys_And_Vertices(polygon_count, vertex_count, render_state.shader);
		draw_calls++;
		D3DDevice->DrawPrimitive(
			(D3DPRIMITIVETYPE)primitive_type, min_vertex_index, polygon_count);
		number_of_DX8_calls++;
		return;
	}

	switch (render_state.vertex_buffer_types[0]) {
	case BUFFER_TYPE_DX8:
	case BUFFER_TYPE_DYNAMIC_DX8:
		switch (render_state.index_buffer_type) {
		case BUFFER_TYPE_DX8:
		case BUFFER_TYPE_DYNAMIC_DX8:
			Debug_Statistics::Record_DX8_Polys_And_Vertices(polygon_count, vertex_count, render_state.shader);
			draw_calls++;
			D3DDevice->DrawIndexedPrimitive(
				(D3DPRIMITIVETYPE)primitive_type,
				render_state.vba_offset + render_state.index_base_offset,
				min_vertex_index,
				vertex_count,
				start_index + render_state.iba_offset,
				polygon_count);
			number_of_DX8_calls++;
			break;
		case BUFFER_TYPE_SORTING:
		case BUFFER_TYPE_DYNAMIC_SORTING:
		case BUFFER_TYPE_INVALID:
			break;
		}
		break;
	case BUFFER_TYPE_SORTING:
	case BUFFER_TYPE_DYNAMIC_SORTING:
		switch (render_state.index_buffer_type) {
		case BUFFER_TYPE_DX8:
		case BUFFER_TYPE_DYNAMIC_DX8:
		case BUFFER_TYPE_INVALID:
			break;
		case BUFFER_TYPE_SORTING:
		case BUFFER_TYPE_DYNAMIC_SORTING:
			Draw_Sorting_IB_VB(
				primitive_type, start_index, polygon_count, min_vertex_index, vertex_count);
			break;
		}
		break;
	case BUFFER_TYPE_INVALID:
		break;
	}
}

// ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z
void DX8Wrapper::Draw_Triangles( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d )
{
	Draw( 4, a, b, c, d, 1 );
}

// ?Draw_Strip@DX8Wrapper@@SAXGGGG@Z
void DX8Wrapper::Draw_Strip( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d )
{
	Draw( 5, a, b, c, d, 1 );
}
