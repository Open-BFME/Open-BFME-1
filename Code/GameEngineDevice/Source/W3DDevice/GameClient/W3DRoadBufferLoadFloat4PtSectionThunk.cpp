// readable body of ?loadFloat4PtSection@W3DRoadBuffer@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp
class RoadSegment;
class Vector2
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
protected:
	void loadFloat4PtSection(RoadSegment *, Vector2, Vector2, Vector2, Vector2 *, float, float, float, float);
};

class W3DRoadBufferLoadFloat4PtSectionShim
{
public:
	void loadFloat4PtSection(RoadSegment *, Vector2, Vector2, Vector2, Vector2 *, float, float, float, float);
};

void W3DRoadBuffer::loadFloat4PtSection(RoadSegment *road, Vector2 a, Vector2 b, Vector2 c, Vector2 *d, float w, float x, float y, float z)
{
	((W3DRoadBufferLoadFloat4PtSectionShim *)this)->loadFloat4PtSection(road, a, b, c, d, w, x, y, z);
}
