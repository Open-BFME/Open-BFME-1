// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?Do_Mappers_Need_Normals@MeshMatDescClass@@QAE_NXZ: Code/Libraries/Source/WWVegas/WW3D2/meshmatdesc.cpp
#define Matrix4x4 Matrix4

#include "meshmatdesc.h"
#include "vertmaterial.h"
#include "dx8wrapper.h"
#include "dx8caps.h"

// ?Do_Mappers_Need_Normals@MeshMatDescClass@@QAE_NXZ
bool MeshMatDescClass::Do_Mappers_Need_Normals()
{
	if (*reinterpret_cast<bool *>(0x0134050c)
		&& *reinterpret_cast<bool *>(*reinterpret_cast<unsigned char **>(0x01340578) + 0x13b)
		&& *reinterpret_cast<unsigned int *>(0x012d6d8c) > 1) {
		return true;
	}

	for (int pass = 0; pass < PassCount; ++pass) {
		if (Material[pass] != 0) {
			VertexMaterialClass *retailMaterial = reinterpret_cast<VertexMaterialClass *>(
				reinterpret_cast<unsigned char *>(Material[pass]) - 4);
			if (retailMaterial->Do_Mappers_Need_Normals()) return true;
		} else {
			VertexMaterialClass *prev_mtl = 0;
			VertexMaterialClass *mtl;
			for (int vidx = 0; vidx < VertexCount; ++vidx) {
				if (MaterialArray[pass]) {
					VertexMaterialClass **items = *reinterpret_cast<VertexMaterialClass ***>((unsigned char *)MaterialArray[pass] + 8);
					mtl = items[vidx];
				} else {
					mtl = Material[pass];
				}
				if (mtl != prev_mtl && mtl != 0) {
					VertexMaterialClass *retailMaterial = reinterpret_cast<VertexMaterialClass *>(
						reinterpret_cast<unsigned char *>(mtl) - 4);
					if (retailMaterial->Do_Mappers_Need_Normals()) return true;
					prev_mtl = mtl;
				}
			}
		}
	}
	return false;
}
