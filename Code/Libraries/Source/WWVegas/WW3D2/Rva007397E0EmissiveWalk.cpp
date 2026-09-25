// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug
// Retail 0x007397E0 (225 B, cdecl, returns AL): walks a RenderObjClass tree
// and sets the emissive color of every vertex material it reaches. The
// material-info slot (+0x150), the sub-object slots (+0x6C count, +0x74 get),
// VertexMaterialClass::Set_Emissive (0x009210D0) and the self-recursion through
// ILT 0x0002C9DA identify the body. No caller, string or Zero Hour twin names
// it, so the address is kept in the name; the matched caller
// Rva00618A90Update.cpp already calls it by this signature. The child result
// is folded as an assignment: the `if (result || child) result = true` form
// makes MSVC 7.1 hoist a color into EBX and spill the result byte.
#include "WW3D2/rendobj.h"
#include "WW3D2/matinfo.h"
#include "WW3D2/vertmaterial.h"

// ?Rva007397E0@@YA_NPAXMMM@Z
bool Rva007397E0(void *object, float red, float green, float blue)
{
	RenderObjClass *robj = (RenderObjClass *)object;
	if (robj == NULL)
		return false;

	bool result = false;
	MaterialInfoClass *material_info = robj->Get_Material_Info();
	if (material_info != NULL)
	{
		for (int index = 0; index < material_info->Vertex_Material_Count(); ++index)
		{
			VertexMaterialClass *material = material_info->Get_Vertex_Material(index);
			if (material != NULL)
			{
				material->Set_Emissive(red, green, blue);
				material->Release_Ref();
				result = true;
			}
		}
		material_info->Release_Ref();
		return result;
	}

	int count = robj->Get_Num_Sub_Objects();
	for (int index = 0; index < count; ++index)
	{
		RenderObjClass *sub_object = robj->Get_Sub_Object(index);
		bool child = Rva007397E0(sub_object, red, green, blue);
		result = result || child;
		if (sub_object != NULL)
			sub_object->Release_Ref();
	}
	return result;
}
