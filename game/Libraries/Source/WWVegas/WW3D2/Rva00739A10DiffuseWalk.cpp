// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// Retail 0x00739A10 (222 B, cdecl, returns AL): the diffuse sibling of
// Rva007397E0 (Rva007397E0EmissiveWalk.cpp). The two bodies are byte-identical
// except that this one calls VertexMaterialClass::Set_Diffuse (0x00921010)
// where the sibling calls Set_Emissive, and recurses through its own ILT
// 0x00020207. The sibling's matched caller proves the shared
// (object, red, green, blue) contract; no caller or string names this body,
// so the address stays in the name.
#include "WW3D2/rendobj.h"
#include "WW3D2/matinfo.h"
#include "WW3D2/vertmaterial.h"

// ?Rva00739A10@@YA_NPAXMMM@Z
bool Rva00739A10(void *object, float red, float green, float blue)
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
				material->Set_Diffuse(red, green, blue);
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
		bool child = Rva00739A10(sub_object, red, green, blue);
		result = result || child;
		if (sub_object != NULL)
			sub_object->Release_Ref();
	}
	return result;
}
