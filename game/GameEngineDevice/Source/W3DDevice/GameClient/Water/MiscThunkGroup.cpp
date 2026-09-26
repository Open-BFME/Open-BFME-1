// readable body of ?loadTracks@WaterTracksRenderSystem@@QAEXXZ: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
protected:
	void addWaypointLink(int id1, int id2);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWaterTracks.h
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
    void add(int id1, int id2);
};

void TerrainLogic::addWaypointLink(int id1, int id2)
{
    ((TerrainLogicAddWaypointLinkShim *)this)->add(id1, id2);
}
