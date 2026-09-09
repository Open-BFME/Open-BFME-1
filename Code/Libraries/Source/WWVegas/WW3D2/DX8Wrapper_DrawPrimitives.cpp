// cl: /DNDEBUG /MD /EHsc
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
	D3DPT_TRIANGLELIST = 4
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
	DX8_DRAW_DUMMY(44) DX8_DRAW_DUMMY(45) DX8_DRAW_DUMMY(46) DX8_DRAW_DUMMY(47)
	DX8_DRAW_DUMMY(48) DX8_DRAW_DUMMY(49) DX8_DRAW_DUMMY(50) DX8_DRAW_DUMMY(51)
	DX8_DRAW_DUMMY(52) DX8_DRAW_DUMMY(53) DX8_DRAW_DUMMY(54) DX8_DRAW_DUMMY(55)
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
};
#undef DX8_DRAW_DUMMY

class Vector3
{
	public:
	float X, Y, Z;
};

class ShaderClass
{
public:
	UnsignedInt bits;
};

class VertexMaterialClass
{
public:
	void Get_Emissive(Vector3 *set) const;
};

// The getter is inline in the W3D vertex-buffer header. Its only field used by
// this body is the measured WORD at +0x0c, so this TU-local view preserves the
// real access without importing the whole DX8 header graph.
class VertexBufferClass
{
	char unused[0x0c];
	UnsignedShort vertex_count;

public:
	UnsignedShort Get_Vertex_Count() const { return vertex_count; }
};

struct RenderStateStruct
{
	ShaderClass shader;
	VertexMaterialClass *material;
	char unused[0x24c - 8];
	UnsignedInt vertex_buffer_types[2];
	UnsignedInt index_buffer_type;
	UnsignedShort vba_offset;
	UnsignedShort vba_count;
	UnsignedShort iba_offset;
	VertexBufferClass *vertex_buffers[2];
	void *index_buffer;
	UnsignedShort index_base_offset;
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
	static RenderStateStruct render_state;
	static unsigned draw_calls;

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
