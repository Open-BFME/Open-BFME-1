// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// readable body of ?loadRoadsAndBridges@BaseHeightMapRenderObjClass@@QAEXPAVW3DTerrainLogic@@_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// BFME's focused road/bridge loader.  The canonical Zero Hour body is in
// BaseHeightMap.cpp; this TU supplies the retail member offsets and device lock.
#include "dx8wrapper.h"

typedef bool Bool;

class W3DTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
public:
	void loadRoads();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBridgeBuffer.h
class W3DBridgeBuffer
{
public:
	void loadBridges(W3DTerrainLogic *terrainLogic, Bool saveGame);
};

void W3DRadarResetLock();
void W3DRadarResetUnlock();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	void loadRoadsAndBridges(W3DTerrainLogic *terrainLogic, Bool saveGame);

private:
	char m_bfmeBody[0x30ac];
	W3DRoadBuffer *m_roadBuffer;
	W3DBridgeBuffer *m_bridgeBuffer;
};

void BaseHeightMapRenderObjClass::loadRoadsAndBridges(
	W3DTerrainLogic *terrainLogic,
	Bool saveGame)
{
	W3DRadarResetLock();

	if (DX8Wrapper::_Get_D3D_Device8()
		&& DX8Wrapper::_Get_D3D_Device8()->TestCooperativeLevel() != D3D_OK)
	{
		return;
	}

	W3DRadarResetUnlock();

	if (m_roadBuffer)
	{
		m_roadBuffer->loadRoads();
	}

	if (m_bridgeBuffer)
	{
		m_bridgeBuffer->loadBridges(terrainLogic, saveGame);
	}
}
