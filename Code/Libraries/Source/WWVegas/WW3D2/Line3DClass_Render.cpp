// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "line3d.h"
#include "vertmaterial.h"
#include "shader.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "rinfo.h"
#include "dx8wrapper.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8fvf.h"

const unsigned short Line3DRenderIndices[] =
{
	3,5,1,
	7,5,3,
	1,5,0,
	5,4,0,
	4,2,0,
	4,6,2,
	7,3,2,
	6,7,2,
	7,6,5,
	5,6,4,
	2,3,1,
	2,1,0
};

// BFME's box renderer uses a four-argument dynamic vertex-buffer wrapper.  The
// class is intentionally declared in this TU, as in boxrobj.cpp, because the
// retail ABI is not part of the shared ZH header.
class BoxDynamicVBAccessClass
{
	const FVFInfoClass & FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass * VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned buffer);
	~BoxDynamicVBAccessClass();

	const FVFInfoClass & FVF_Info() const { return FVFInfo; }

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;

	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage,TextureBaseClass *& texture);

class Line3DTextureRef
{
	TextureBaseClass *Texture;

public:
	Line3DTextureRef() : Texture(NULL) {}
	~Line3DTextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass *&() { return Texture; }
};

void Line3DClass::Render(RenderInfoClass & rinfo)
{
	if (Is_Not_Hidden_At_All() == false) {
		return;
	}

	unsigned int sort_level = (unsigned int)Get_Sort_Level();

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != SORT_LEVEL_NONE) {
		WW3D::Add_To_Static_Sort_List(this, sort_level);
		return;
	}

	DX8Wrapper::Set_Shader(Shader);
	{
		Line3DTextureRef texture;
		BoxSetTexture(0,texture);
	}

	VertexMaterialClass *vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vm);
	REF_PTR_RELEASE(vm);

	DX8Wrapper::Set_Transform(D3DTS_WORLD,Transform);

    BoxDynamicVBAccessClass vb(BUFFER_TYPE_DYNAMIC_DX8,5,8,0);
	{
		BoxDynamicVBAccessClass::WriteLockClass Lock(&vb);
		const FVFInfoClass &fi=vb.FVF_Info();
		unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();
		int i;
		unsigned int color=DX8Wrapper::Convert_Color(Color);

		for (i=0; i<8; i++) {
			*(Vector3*)(vb+fi.Get_Location_Offset())=vert[i];
			*(unsigned int*)(vb+fi.Get_Diffuse_Offset())=color;
			vb+=fi.Get_FVF_Size();
		}
	}

	DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8,36);
	{
        DynamicIBAccessClass::WriteLockClass Lock(&ib);
        unsigned short *mem=Lock.Get_Index_Array();
        const unsigned short *indices=Line3DRenderIndices;
        const unsigned short *end=Line3DRenderIndices+36;
        while ((int)indices<(int)end) {
            *mem++=*indices++;
        }
	}

	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb));
	DX8Wrapper::Set_Index_Buffer(ib,0);
	DX8Wrapper::Draw_Triangles(0,36/3,0,8);
}
