// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: 0x006F8720 is a byte twin of W3DBridge::getModelIndices
// (W3DBridgeBuffer.cpp, 0x006D89D0) with maxBridgeIndex 30000 instead of
// 16000 -- the same mesh index copier owned by a second, larger buffer class
// whose name the bytes never reach (thiscall with `this` unused).
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include <stdio.h>
#include <string.h>
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include <texture.h>
#include "common/GlobalData.h"
#include "common/RandomValue.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BodyModule.h"
#include "W3DDevice/GameLogic/W3DTerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Camera.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/DX8Renderer.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "WW3D2/Scene.h"

class Rva006F8720MeshBuffer
{
public:
	Int getModelIndices(UnsignedShort *destination_ib, Int curIndex, Int vertexOffset, MeshClass *pMesh);
};

Int Rva006F8720MeshBuffer::getModelIndices(UnsignedShort *destination_ib, Int curIndex, Int vertexOffset, MeshClass *pMesh)
{
	if (pMesh == NULL) 
		return(0);
	Int numPoly = pMesh->Peek_Model()->Get_Polygon_Count();
	const TriIndex *pPoly =pMesh->Peek_Model()->Get_Polygon_Array();
	const Int maxBridgeIndex = 30000;
	if (curIndex+3*numPoly+6 >= maxBridgeIndex) {
		return(0);
	}
	UnsignedShort *curIb = destination_ib+curIndex;
	Int i;
	for (i=0; i<numPoly; i++) {
		*curIb++ = vertexOffset + pPoly[i].I;
		*curIb++ = vertexOffset + pPoly[i].J;
		*curIb++ = vertexOffset + pPoly[i].K;
	}
	return(numPoly*3);
}
