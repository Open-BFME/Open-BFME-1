// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/water /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// readable body of ?renderSkyBody@WaterRenderObjClass@@IAEXPAVMatrix3D@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp

#include "WW3D2/dx8wrapper.h"
#include "WW3D2/dx8fvf.h"
#include "WW3D2/dx8indexbuffer.h"
#include "WW3D2/vertmaterial.h"
#include "WWMath/vector3.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

void __cdecl BoxSetTexture(UnsignedInt stage, TextureBaseClass *&texture);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
	char m_beforeCC[0xcc];

protected:
	IndexBufferClass *m_indexBuffer;
	char m_beforeE4[0x14];
	TextureBaseClass *m_alphaClippingTexture;

	void renderSkyBody(Matrix3D *mat);
};

void WaterRenderObjClass::renderSkyBody(Matrix3D *mat)
{
	Vector3 cPos;
	Vector3 pView;
	Vector3 pRight;
	Vector3 pUp;
	Vector3 pPos(150.0f, 550.0f, 30.0f);

	mat->Get_Translation(&cPos);

	pView = cPos - pPos;
	pView.Normalize();

	Vector3 WorldUp(0, 0, -1);
	Vector3 rotAxis;
	Vector3::Normalized_Cross_Product(WorldUp, pView, &rotAxis);

	Real angle = Vector3::Dot_Product(WorldUp, pView);
	angle = acos(angle);

	Matrix3D tm(1);
	tm.Set(rotAxis, angle);
	tm.Adjust_Translation(Vector3(150.0f, 550.0f, 30.0f));
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);

	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(
		VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);

	ShaderClass shader = ShaderClass::_PresetAlphaShader;
	*reinterpret_cast<UnsignedInt *>(&shader) &= ~0x00100000u;
	shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
	shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
	DX8Wrapper::Set_Shader(shader);

	BoxSetTexture(0, m_alphaClippingTexture);

	BoxDynamicVBAccessClass vb_access(2, 5, 4, 0);
	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();
		if (verts)
		{
			verts[0].x = -45.0f;
			verts[0].y = 45.0f;
			verts[0].z = 0.0f;
			verts[0].u2 = 0.0f;
			verts[0].v2 = 1.0f;
			verts[0].diffuse = 0xffffffff;

			verts[1].x = 45.0f;
			verts[1].y = 45.0f;
			verts[1].z = 0.0f;
			verts[1].u2 = 1.0f;
			verts[1].v2 = 1.0f;
			verts[1].diffuse = 0xffffffff;

			verts[2].x = 45.0f;
			verts[2].y = -45.0f;
			verts[2].z = 0.0f;
			verts[2].u2 = 1.0f;
			verts[2].v2 = 0.0f;
			verts[2].diffuse = 0xffffffff;

			verts[3].x = -45.0f;
			verts[3].y = -45.0f;
			verts[3].z = 0.0f;
			verts[3].u2 = 0.0f;
			verts[3].v2 = 0.0f;
			verts[3].diffuse = 0xffffffff;
		}
	}

	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);
	DX8Wrapper::Set_Vertex_Buffer(
		*reinterpret_cast<DynamicVBAccessClass *>(&vb_access));
	DX8Wrapper::Draw_Triangles(0, 2, 0, 4);
}
