// readable body of ?loadTracks@WaterTracksRenderSystem@@QAEXXZ: game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
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
