// ?renderShoreLines@BaseHeightMapRenderObjClass@@IAEXPAVCameraClass@@@Z
// partial score=0.42 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmeheightmap /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_USE_STATIC_LIB

#include <windows.h>
#include <d3dx8core.h>
#include "Common/GlobalData.h"
#include "GameClient/Water.h"
#include "W3DDevice/GameClient/BaseHeightMap.h"

#define DEFAULT_MAX_BATCH_SHORELINE_TILES 512

class BoxDynamicVBAccessClass
{
	const FVFInfoClass &m_fvfInfo;
	unsigned m_type;
	unsigned m_fvf;
	unsigned m_start;
	unsigned short m_vertexCount;
	unsigned short m_vertexBufferOffset;
	class BoxVertexBufferClass *m_vertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type, unsigned fvf, unsigned short vertexCount, unsigned start);
	~BoxDynamicVBAccessClass();

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *m_dynamicVBAccess;
		VertexFormatXYZNDUV2 *m_vertices;

	public:
		__declspec(noinline) WriteLockClass(BoxDynamicVBAccessClass *vbAccess);
		__declspec(noinline) ~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return m_vertices; }
	};
};

void __cdecl BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

void BaseHeightMapRenderObjClass::renderShoreLines(CameraClass *pCamera)
{
	char *heightMap = reinterpret_cast<char *>(this);
	if (!*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(TheGlobalData) + 0x8c) ||
		*reinterpret_cast<Real *>(heightMap + 0x3018) == 0.0f ||
		*reinterpret_cast<Int *>(heightMap + 0x30c4) == 0) {
		return;
	}

	if (DX8Wrapper::getBackBufferFormat() != WW3D_FORMAT_A8R8G8B8) {
		return;
	}

	Int vertexCount = 0;
	Int indexCount = 0;
	WorldHeightMap *map = *reinterpret_cast<WorldHeightMap **>(heightMap + 0x2ff4);
	Int drawEdgeY = map->getDrawOrgY() + map->getDrawHeight() - 1;
	Int drawEdgeX = map->getDrawOrgX() + map->getDrawWidth() - 1;
	if (drawEdgeX > map->getXExtent() - 1) {
		drawEdgeX = map->getXExtent() - 1;
	}
	if (drawEdgeY > map->getYExtent() - 1) {
		drawEdgeY = map->getYExtent() - 1;
	}
	Int drawStartX = map->getDrawOrgX();
	Int drawStartY = map->getDrawOrgY();
	Int j = 0;

	ShaderClass unlitShader = ShaderClass::_PresetOpaque2DShader;
	unlitShader.Set_Depth_Compare(ShaderClass::PASS_LEQUAL);
	DX8Wrapper::Set_Shader(unlitShader);
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);
	TextureBaseClass *&destAlphaTexture =
		*reinterpret_cast<TextureBaseClass **>(heightMap + 0x3090);
	BoxSetTexture(0, destAlphaTexture);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, Matrix3D(1));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_TEXCOORDINDEX, 0);

	while (j != *reinterpret_cast<Int *>(heightMap + 0x30c4)) {
		BoxDynamicVBAccessClass vb_access(BUFFER_TYPE_DYNAMIC_DX8, dynamic_fvf_type,
			DEFAULT_MAX_BATCH_SHORELINE_TILES * 4, 0);
		DynamicIBAccessClass ib_access(BUFFER_TYPE_DYNAMIC_DX8,
			DEFAULT_MAX_BATCH_SHORELINE_TILES * 6);

		{
			BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
			VertexFormatXYZNDUV2 *vb = lock.Get_Formatted_Vertex_Array();
			DynamicIBAccessClass::WriteLockClass lockib(&ib_access);
			UnsignedShort *ib = lockib.Get_Index_Array();
			if (!ib || !vb) {
				DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,
					D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED);
				return;
			}

			try {
				for (; j < *reinterpret_cast<Int *>(heightMap + 0x30c4); ++j) {
					if (vertexCount >= DEFAULT_MAX_BATCH_SHORELINE_TILES * 4) {
						break;
					}

					shoreLineTileInfo *shoreInfo =
						&(*reinterpret_cast<shoreLineTileInfo **>(heightMap + 0x30c0))[j];
					Int x = shoreInfo->m_xy & 0xffff;
					Int y = shoreInfo->m_xy >> 16;

					if (x >= drawStartX && x < drawEdgeX && y >= drawStartY && y < drawEdgeY) {
						vb->x = shoreInfo->verts[0];
						vb->y = shoreInfo->verts[1];
						vb->z = shoreInfo->verts[2];
						vb->nx = 0;
						vb->ny = 0;
						vb->nz = 0;
						vb->diffuse = 0;
						vb->u1 = shoreInfo->t0;
						vb->v1 = 0;
						vb->u2 = 0;
						vb->v2 = 0;
						++vb;

						vb->x = shoreInfo->verts[3];
						vb->y = shoreInfo->verts[4];
						vb->z = shoreInfo->verts[5];
						vb->nx = 0;
						vb->ny = 0;
						vb->nz = 0;
						vb->diffuse = 0;
						vb->u1 = shoreInfo->t1;
						vb->v1 = 0;
						vb->u2 = 0;
						vb->v2 = 0;
						++vb;

						vb->x = shoreInfo->verts[6];
						vb->y = shoreInfo->verts[7];
						vb->z = shoreInfo->verts[8];
						vb->nx = 0;
						vb->ny = 0;
						vb->nz = 0;
						vb->diffuse = 0;
						vb->u1 = shoreInfo->t2;
						vb->v1 = 0;
						vb->u2 = 0;
						vb->v2 = 0;
						++vb;

						vb->x = shoreInfo->verts[9];
						vb->y = shoreInfo->verts[10];
						vb->z = shoreInfo->verts[11];
						vb->nx = 0;
						vb->ny = 0;
						vb->nz = 0;
						vb->diffuse = 0;
						vb->u1 = shoreInfo->t3;
						vb->v1 = 0;
						vb->u2 = 0;
						vb->v2 = 0;
						++vb;

						if (map->getQuickFlipState(x, y)) {
							ib[0] = 1 + vertexCount;
							ib[1] = 3 + vertexCount;
							ib[2] = vertexCount;
							ib[3] = 1 + vertexCount;
							ib[4] = 2 + vertexCount;
							ib[5] = 3 + vertexCount;
						} else {
							ib[0] = vertexCount;
							ib[1] = 2 + vertexCount;
							ib[2] = 3 + vertexCount;
							ib[3] = vertexCount;
							ib[4] = 1 + vertexCount;
							ib[5] = 2 + vertexCount;
						}
						ib += 6;
						vertexCount += 4;
						indexCount += 6;
					}
				}
				IndexBufferExceptionFunc();
			} catch (...) {
				IndexBufferExceptionFunc();
			}
		}

		if (indexCount > 0 && vertexCount > 0) {
			DX8Wrapper::Set_Index_Buffer(ib_access, 0);
			DX8Wrapper::Set_Vertex_Buffer(
				*reinterpret_cast<const DynamicVBAccessClass *>(&vb_access));
			DX8Wrapper::Draw_Triangles(0, indexCount / 3, 0, vertexCount);
		}

		vertexCount = 0;
		indexCount = 0;
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED);
	ShaderClass::Invalidate();
}
