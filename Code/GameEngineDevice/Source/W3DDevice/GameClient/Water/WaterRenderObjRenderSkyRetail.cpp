// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/water /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

#include "WW3D2/dx8wrapper.h"
#include "WW3D2/dx8fvf.h"
#include "WW3D2/dx8indexbuffer.h"
#include "WW3D2/vertmaterial.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

void __cdecl BoxSetTexture(UnsignedInt stage, TextureBaseClass *&texture);

// BoxDynamicVBAccessClass is a TU-local wrapper in the original WW3D source.
// Its BFME layout is the one consumed by DX8Wrapper::Set_Vertex_Buffer.
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

struct WaterSetting
{
	TextureBaseClass *skyTexture;
	TextureBaseClass *waterTexture;
	Int waterRepeatCount;
	Real skyTexelsPerUnit;
	UnsignedInt vertex00Diffuse;
	UnsignedInt vertex10Diffuse;
	UnsignedInt vertex11Diffuse;
	UnsignedInt vertex01Diffuse;
	UnsignedInt waterDiffuse;
	UnsignedInt transparentWaterDiffuse;
	Real uScrollPerMs;
	Real vScrollPerMs;
};

class WaterRenderObjClass
{
	char m_beforeCC[0xcc];

protected:
	IndexBufferClass *m_indexBuffer; // +0xcc
	char m_before104[0x34];
	Real m_uOffset;                  // +0x104
	Real m_vOffset;                  // +0x108
	char m_before114[8];
	Int m_LastUpdateTime;            // +0x114
	char m_beforeSettings[0x1c8];
	WaterSetting m_settings[6];      // +0x2e0
	Int m_tod;                       // +0x400

	void renderSky(void);
};

void WaterRenderObjClass::renderSky(void)
{
	Int timeNow, timeDiff;
	Real fu, fv;

	WaterSetting *setting = &m_settings[m_tod];

	timeNow = (Int)timeGetTime();

	timeDiff = timeNow - m_LastUpdateTime;
	m_LastUpdateTime = timeNow;

	m_uOffset += timeDiff * setting->uScrollPerMs * setting->skyTexelsPerUnit;
	m_vOffset += timeDiff * setting->vScrollPerMs * setting->skyTexelsPerUnit;

	// Clamp the UV coordinate into the 0,1 range.
	m_uOffset = m_uOffset - (Real)((Int)m_uOffset);
	m_vOffset = m_vOffset - (Real)((Int)m_vOffset);

	fu = m_uOffset + (384.0f * 2.0f) * setting->skyTexelsPerUnit;
	fv = m_vOffset + (384.0f * 2.0f) * setting->skyTexelsPerUnit;

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(
		VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);

	ShaderClass shader = ShaderClass::_PresetOpaqueShader;
	// BFME keeps cull mode in bit 20; this TU-local mask preserves the retail
	// shader ABI while the shared Zero Hour header still describes bit 19.
	*reinterpret_cast<UnsignedInt *>(&shader) &= ~0x00100000u;
	shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
	shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
	DX8Wrapper::Set_Shader(shader);

	BoxSetTexture(0, setting->skyTexture);

	BoxDynamicVBAccessClass vb_access(2, 5, 4, 0);
	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();
		if (verts)
		{
			verts[0].x = -3840.0f;
			verts[0].y = 3840.0f;
			verts[0].z = 30.0f;
			verts[0].u1 = m_uOffset;
			verts[0].v1 = fv;
			verts[0].diffuse = setting->vertex01Diffuse;

			verts[1].x = 3840.0f;
			verts[1].y = 3840.0f;
			verts[1].z = 30.0f;
			verts[1].u1 = fu;
			verts[1].v1 = fv;
			verts[1].diffuse = setting->vertex11Diffuse;

			verts[2].x = 3840.0f;
			verts[2].y = -3840.0f;
			verts[2].z = 30.0f;
			verts[2].u1 = fu;
			verts[2].v1 = m_vOffset;
			verts[2].diffuse = setting->vertex10Diffuse;

			verts[3].x = -3840.0f;
			verts[3].y = -3840.0f;
			verts[3].z = 30.0f;
			verts[3].u1 = m_uOffset;
			verts[3].v1 = m_vOffset;
			verts[3].diffuse = setting->vertex00Diffuse;
		}
	}

	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);
	DX8Wrapper::Set_Vertex_Buffer(
		*reinterpret_cast<DynamicVBAccessClass *>(&vb_access));

	Matrix3D tm(1);
	tm.Set_Translation(Vector3(0, 0, 0));
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);

	DX8Wrapper::Draw_Triangles(0, 2, 0, 4);
}
