// cl: /DNDEBUG /MD /EHsc
// readable body of ?flush@TerrainTracksRenderObjClassSystem@@QAEXXZ:
//   game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// BFME retail 0x0072FEB0..0x0073030B (892 bytes), the tank-track flush.
//
// Ported from the Zero Hour body in W3DTerrainTracks.cpp.  Three BFME
// differences are visible in the retail body and are reproduced here:
//
//  1. Zero Hour guards the vertex fill and the draw on m_edgesToFlush, which
//     BFME's constructor never allocates.  Retail instead remembers whether any
//     module contributed an edge (the byte at this frame slot) and gates the
//     whole draw on that.
//  2. Zero Hour walks the transform of every module and calls Set_Transform;
//     retail stores the identity world matrix once, before the draw loop.
//  3. Zero Hour calls ShaderClass::Invalidate() and Is_Really_Visible() per
//     module; BFME keeps Invalidate (it is the inline store to ShaderDirty at
//     0x012D6DFC) and drops Is_Really_Visible() from both loops.
//
// The shifts that pack the day-time light into the vertex colour run
// left to right -- ((red << 8) | green) << 8 | blue -- which is what retail
// emits; the algebraically identical red << 16 form is a different instruction
// sequence.
//
// SHAPE NOTE -- why the module pointer is declared inside each loop.  Retail
// fills the gap between the second vertex's v1 load and its v1 store with the
// two independent live-out reloads of the inner loop body, in this order:
//
//   +0183  mov ecx,[esp+0x14]      mod   (live into the outer latch, +01A5)
//   +0187  mov edi,[esp+0x18]      this  (live into the wrap check,  +00F1)
//
// MSVC 7.1 C1 emits the live-in reloads of a block in LCID order, and an LCID
// is minted where the parser first creates the value, not where it is used.
// So the order is decided by WHICH STATEMENT FIRST MAKES the loop-carried
// module pointer a value.  Declaring `mod` at function scope -- the Zero Hour
// spelling, and the obvious reading of "walk the module list twice" -- mints
// its LCID before the first `this`-relative read (m_maxTankTrackEdges at
// +008F), and the reloads come out swapped: this, then mod.  Retail's order
// needs the module pointer minted AFTER that read, i.e. the early null test
// reads m_usedModules directly and each loop declares its own block-scoped
// `mod`.  Both loops walk the same list, so this is also the natural upstream
// shape.  See targets/game/reverse/re_attempts.log for the three earlier
// sessions that swept declaration order, loop shape and the block graph
// without reaching it.  Everything else stays as upstream has it, including
// the function-scope `distanceFade`; only the module pointer moved.
//
// The x87 light pack, the WriteLockClass fill loop, the inlined
// Set_Material/Set_Shader/Set_World_Identity blocks and the
// BoxSetTexture/Draw_Triangles draw loop are all byte-exact as written
// (probe: 892/892, 57 relocations, shape 1.000, frame 0x20).

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

#define REAL_TO_INT(x) ((Int)(x))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
// Only the (int,bool) constructor and the destructor are reachable from here:
// the shader description the DX8Wrapper snapshot needs.
class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;		// 0x012D9124
	static char m_NullChar;			// 0x0134ECC8
	void Get_String(int, bool);
	void Free_String(void);

public:
	__forceinline StringClass(int n = 0, bool temporary = false)
		: m_Buffer(m_EmptyString)
	{
		Get_String(n, temporary);
		m_Buffer[0] = m_NullChar;
	}
	__forceinline ~StringClass(void)
	{
		Free_String();
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class VertexMaterialClass
{
public:
	virtual void Delete_This(void);
	Int refs;						// this+0x04

	void Release_Ref(void)
	{
		if (!--refs)
			Delete_This();
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h
class VertexBufferClass
{
public:
	class WriteLockClass
	{
		VertexBufferClass *m_Buffer;	// this+0x00
		void *m_Vertices;			// this+0x04
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags = 0);
		~WriteLockClass(void);
		void *Get_Vertex_Array(void) { return m_Vertices; }
	};
};

class DX8VertexBufferClass : public VertexBufferClass
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8fvf.h
struct VertexFormatXYZDUV1
{
	Real x, y, z;
	unsigned int diffuse;
	Real u1, v1;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h
struct Vector3
{
	Real X, Y, Z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector2.h
struct Vector2
{
	Real X, Y;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
struct edgeInfo
{
	Vector3 endPointPos[2];
	Vector2 endPointUV[2];
	Int timeAdded;
	Real alpha;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red, green, blue;
};

// Retail's GlobalData at 0x012ED5C8; keep only the members this file reads.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva006C9270GlobalData
{
	char head[0x9BC];
	RGBColor m_terrainAmbient[3];		// this+0x9BC
	RGBColor m_terrainDiffuse[3];		// this+0x9E0
};

static inline const Rva006C9270GlobalData *tracksGlobalData()
{
	return (const Rva006C9270GlobalData *)TheWritableGlobalData;
}

class IndexBufferClass;
class TextureBaseClass;
void BoxSetTexture(unsigned int stage, TextureBaseClass *&texture);

extern VertexMaterialClass *ScreenMaterial;		// 0x01340EC4
extern unsigned int ScreenCurrentShader;		// 0x01340EC0
extern unsigned int TheBoxTextureDirtyMask;		// 0x0133F49C
extern Real g_worldMatrix[16];					// 0x0134108C
extern unsigned short Rva0134112CIndexBaseOffset;// 0x0134112C, the cached index offset
extern bool g_rva007A2330Flag;					// 0x012D6DFC

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	unsigned int bits;							// this+0x00

	// ShaderClass::ShaderDirty is the byte at 0x012D6DFC; the harvest named it
	// after the body that writes it.  Set_Shader below reads the same byte.
	static __forceinline void Invalidate(void) { g_rva007A2330Flag = true; }
	static bool Is_Backface_Culling_Inverted(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	// The deferred-state members live in the wrapper's render_state block; the
	// three the flush touches are named after the addresses retail uses.
	static __forceinline void Set_Material(VertexMaterialClass *material)
	{
		if (material)
			++material->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = material;
		TheBoxTextureDirtyMask |= 0x4000;		// MATERIAL_CHANGED
	}

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!g_rva007A2330Flag && shader.bits == ScreenCurrentShader)
			return;
		ScreenCurrentShader = shader.bits;
		TheBoxTextureDirtyMask |= 0x8000;		// SHADER_CHANGED
		StringClass description(0, false);
	}

	static __forceinline void Set_World_Identity(void)
	{
		g_worldMatrix[0] = 1.0f;
		g_worldMatrix[1] = 0.0f;
		g_worldMatrix[2] = 0.0f;
		g_worldMatrix[3] = 0.0f;
		g_worldMatrix[4] = 0.0f;
		g_worldMatrix[5] = 1.0f;
		g_worldMatrix[6] = 0.0f;
		g_worldMatrix[7] = 0.0f;
		g_worldMatrix[8] = 0.0f;
		g_worldMatrix[9] = 0.0f;
		g_worldMatrix[10] = 1.0f;
		g_worldMatrix[11] = 0.0f;
		g_worldMatrix[12] = 0.0f;
		g_worldMatrix[13] = 0.0f;
		g_worldMatrix[14] = 0.0f;
		g_worldMatrix[15] = 1.0f;
		TheBoxTextureDirtyMask = (TheBoxTextureDirtyMask & 0xfffbffff) | 1;
	}

	static __forceinline void Set_Index_Buffer_Index_Offset(unsigned int offset)
	{
		if (Rva0134112CIndexBaseOffset == offset)
			return;
		Rva0134112CIndexBaseOffset = offset;
		TheBoxTextureDirtyMask |= 0x20000;		// INDEX_BUFFER_CHANGED
	}

	static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
	static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned int);
	static void Draw_Triangles(unsigned short, unsigned short, unsigned short,
		unsigned short);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClass
{
public:
	unsigned char m_bfme_head[8];				// this+0x00 .. +0x07
	TextureBaseClass *m_stageZeroTexture;		// this+0x08
	Int m_activeEdgeCount;						// this+0x0C
	Int m_totalEdgesAdded;						// this+0x10
	void *m_ownerDrawable;						// this+0x14
	edgeInfo m_edges[100];						// this+0x18, 0x30 per edge
	Vector3 m_lastAnchor;						// this+0x12D8
	Int m_bottomIndex;							// this+0x12E4
	Int m_topIndex;								// this+0x12E8
	Bool m_haveAnchor;							// this+0x12EC
	Bool m_bound;								// this+0x12ED
	unsigned char m_bfme_pad0[2];
	Real m_width;								// this+0x12F0
	Real m_length;								// this+0x12F4
	Bool m_airborne;								// this+0x12F8
	Bool m_haveCap;								// this+0x12F9
	unsigned char m_bfme_pad1[2];
	TerrainTracksRenderObjClass *m_nextSystem;	// this+0x12FC
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClassSystem
{
public:
	void flush(void);

private:
	DX8VertexBufferClass *m_vertexBuffer;			// this+0x00
	const IndexBufferClass *m_indexBuffer;			// this+0x04
	VertexMaterialClass *m_vertexMaterialClass;		// this+0x08
	ShaderClass m_shaderClass;						// this+0x0C
	TerrainTracksRenderObjClass *m_usedModules;		// this+0x10
	TerrainTracksRenderObjClass *m_freeModules;		// this+0x14
	void *m_TerrainTracksScene;					// this+0x18
	Int m_maxTankTrackEdges;						// this+0x1C
	Int m_maxTankTrackOpaqueEdges;					// this+0x20
	Int m_maxTankTrackFadeDelay;					// this+0x24
};

// ?flush@TerrainTracksRenderObjClassSystem@@QAEXXZ
void TerrainTracksRenderObjClassSystem::flush(void)
{
	Int diffuseLight;
	Int trackStartIndex;
	Real distanceFade;
	if (!m_usedModules)
		return;	//nothing to render

	if (ShaderClass::Is_Backface_Culling_Inverted())
		return;	//don't render track marks in reflections.

	// adjust shading for time of day.
	const Rva006C9270GlobalData *gd = tracksGlobalData();
	diffuseLight = REAL_TO_INT((gd->m_terrainAmbient[0].red +
		gd->m_terrainDiffuse[0].red * 0.5f) * 255.0f);
	diffuseLight = (diffuseLight << 8) | REAL_TO_INT(
		(gd->m_terrainAmbient[0].green +
		gd->m_terrainDiffuse[0].green * 0.5f) * 255.0f);
	diffuseLight = (diffuseLight << 8) | REAL_TO_INT(
		(gd->m_terrainAmbient[0].blue +
		gd->m_terrainDiffuse[0].blue * 0.5f) * 255.0f);

	Real numFadedEdges = m_maxTankTrackEdges - m_maxTankTrackOpaqueEdges;

	//check if there is anything to draw and fill vertex buffer
	Bool drewSomething = false;
	{
		DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexBuffer);
		VertexFormatXYZDUV1 *verts =
			(VertexFormatXYZDUV1 *)lockVtxBuffer.Get_Vertex_Array();

		//Fill our vertex buffer with all the tracks
		TerrainTracksRenderObjClass *mod = m_usedModules;
		while (mod)
		{
			Vector3 *endPoint;
			Vector2 *endPointUV;
			Int i, index;

			if (mod->m_activeEdgeCount >= 2)
			{
				drewSomething = true;
				for (i = 0, index = mod->m_bottomIndex;
					i < mod->m_activeEdgeCount; i++, index++)
				{
					if (index >= m_maxTankTrackEdges)
						index = 0;

					endPoint = &mod->m_edges[index].endPointPos[0];	//left endpoint
					endPointUV = &mod->m_edges[index].endPointUV[0];

					distanceFade = 1.0f;

					if ((mod->m_activeEdgeCount - 1 - i) >= m_maxTankTrackOpaqueEdges)
					{	//we're getting close to the limit on the number of track pieces allowed
						//so force it to fade out.
						distanceFade = 1.0f - (Real)((mod->m_activeEdgeCount - i) -
							m_maxTankTrackOpaqueEdges) / numFadedEdges;
					}

					distanceFade *= mod->m_edges[index].alpha;	//adjust fade with distance from start of track

					verts->x = endPoint->X;
					verts->y = endPoint->Y;
					verts->z = endPoint->Z;

					verts->u1 = endPointUV->X;
					verts->v1 = endPointUV->Y;

					//fade the alpha channel with distance
					verts->diffuse = diffuseLight |
						(REAL_TO_INT(distanceFade * 255.0f) << 24);
					verts++;

					endPoint = &mod->m_edges[index].endPointPos[1];	//right endpoint
					endPointUV = &mod->m_edges[index].endPointUV[1];

					verts->x = endPoint->X;
					verts->y = endPoint->Y;
					verts->z = endPoint->Z;

					verts->u1 = endPointUV->X;
					verts->v1 = endPointUV->Y;			///@todo: Add diffuse lighting.

					verts->diffuse = diffuseLight |
						(REAL_TO_INT(distanceFade * 255.0f) << 24);
					verts++;
				}//for
			}// mod has edges to render
			mod = mod->m_nextSystem;
		}	//while (mod)
	}//edges to flush

	//draw the filled vertex buffers
	if (drewSomething)
	{
		ShaderClass::Invalidate();
		DX8Wrapper::Set_Material(m_vertexMaterialClass);
		DX8Wrapper::Set_Shader(m_shaderClass);
		DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffer, 0);

		trackStartIndex = 0;
		DX8Wrapper::Set_World_Identity();
		TerrainTracksRenderObjClass *mod = m_usedModules;
		while (mod)
		{
			if (mod->m_activeEdgeCount >= 2)
			{
				BoxSetTexture(0, mod->m_stageZeroTexture);
				DX8Wrapper::Set_Index_Buffer_Index_Offset(trackStartIndex);
				DX8Wrapper::Draw_Triangles(	0, (mod->m_activeEdgeCount - 1) * 2, 0,
											mod->m_activeEdgeCount * 2);

				trackStartIndex += mod->m_activeEdgeCount * 2;
			}
			mod = mod->m_nextSystem;
		}	//there are some edges to render in pool.
	}
}
