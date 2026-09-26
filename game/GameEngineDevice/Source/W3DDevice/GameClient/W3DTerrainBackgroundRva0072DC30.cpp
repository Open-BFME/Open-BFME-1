// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Complete retail 0x0072DC30..0x0072E044 (1044 bytes), RET12.
// Address-derived method identity: BFME has a third argument and a second
// terrain draw path absent from the older drawVisiblePolys source.
// Native DX8/StringClass inline lifetimes reproduce all five unwind states.
// The positive count-and-texture condition destroys its temporary before
// entering the second draw. The same helper returns a one-pointer owning
// texture handle through hidden result storage (0x0074C690, full407B, RET16).
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "shader.h"
#include "dx8wrapper.h"
typedef bool Bool;
typedef unsigned short UnsignedShort;
void BoxSetTexture(unsigned, TextureBaseClass *&);
class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
	BFMETextureRelease *m_texture;

public:
	~BfmeHandleCX(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_texture;
	}
};

class WorldHeightMap;
class W3DTerrainBackground;

struct Rva0072E150Region
{
	int lo_x;
	int lo_y;
	int hi_x;
	int hi_y;
};

class WorldHeightMap
{
public:
	BfmeHandleCX rva0074C690(int, int, int);
};

class W3DTerrainBackground
{
	char m_00[0x1C];
	VertexBufferClass *m_vertex_1C;
	char m_20[4];
	IndexBufferClass *m_index_24;
	TextureBaseClass *m_texture_28;
	TextureBaseClass *m_texture_2C;
	TextureBaseClass *m_texture_30;
	int m_texture_stride_34;
	int m_curNumTerrainVertices;
	int m_curNumTerrainIndices;
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_initialized;
	Bool m_option_51;
	unsigned char m_dirty_52;
	char m_53[5];
	VertexBufferClass *m_vertex_58;
	char m_5C[4];
	IndexBufferClass *m_index_60;
	char m_64[4];
	int m_vertices_68;
	int m_indices_6C;

protected:
	void setFlipRecursive(int, int, int);

public:
	void rva0072D210(const Rva0072E150Region &, WorldHeightMap *, Bool, Bool);
	void rva0072DC30(RenderInfoClass &, Bool, Bool);
};

void W3DTerrainBackground::rva0072DC30(RenderInfoClass &, Bool disable_textures, Bool draw_secondary)
{
	if (*(int *)this == 2)
		return;

	if (m_curNumTerrainIndices == 0 && m_dirty_52 == 0)
		return;

	if (m_dirty_52)
	{
		const int width = m_width;
		m_dirty_52 = 0;
		Rva0072E150Region region = {
			0,
			0,
			m_xOrigin + width,
			m_yOrigin + width
		};
		setFlipRecursive(0, 0, width);
		rva0072D210(region, 0, false, m_option_51);
	}

	if (m_curNumTerrainIndices == 0)
		return;

	DX8Wrapper::Set_Index_Buffer(m_index_24, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertex_1C, 0);

	if (!disable_textures)
	{
		if (m_texture_30)
			BoxSetTexture(1, m_texture_30);
		else
			BoxSetTexture(1, m_texture_2C);
	}

	DX8Wrapper::Draw_Triangles(0, (unsigned short)(m_curNumTerrainIndices / 3), 0, m_curNumTerrainVertices);

	if (disable_textures && !draw_secondary)
		return;

	if (m_vertices_68 && (TextureBaseClass *&)m_map->rva0074C690(
		m_xOrigin, m_yOrigin, m_width)) {

	DX8Wrapper::Set_Index_Buffer(m_index_60, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertex_58, 0);

	if (!disable_textures)
	{
		DX8Wrapper::Set_DX8_Render_State(0x13, 5);
		DX8Wrapper::Set_DX8_Render_State(0x14, 6);
		DX8Wrapper::Set_DX8_Render_State(0x1B, 1);
		BoxSetTexture(1, (TextureBaseClass *&)m_map->rva0074C690(
			m_xOrigin, m_yOrigin, m_width));
	}

	DX8Wrapper::Draw_Triangles(0, (unsigned short)(m_indices_6C / 3), 0,
		(unsigned short)m_vertices_68);

	if (!disable_textures)
		DX8Wrapper::Set_DX8_Render_State(0x1B, 0);
	}
}
