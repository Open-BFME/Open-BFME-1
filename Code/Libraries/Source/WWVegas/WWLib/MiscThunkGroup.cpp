// readable body of ?loadTracks@WaterTracksRenderSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
protected:
	void addWaypointLink(int, int);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWaterTracks.h
class WaterTracksRenderSystem
{
public:
	void loadTracks();
};

class WaterTracksRenderSystemLoadTracksShim
{
public:
	void loadTracks();
};

void WaterTracksRenderSystem::loadTracks()
{
	((WaterTracksRenderSystemLoadTracksShim *)this)->loadTracks();
}
class TerrainLogicAddWaypointLinkShim
{
public:
    void add(int a, int b);
};

void TerrainLogic::addWaypointLink(int a, int b)
{
    ((TerrainLogicAddWaypointLinkShim *)this)->add(a, b);
}
