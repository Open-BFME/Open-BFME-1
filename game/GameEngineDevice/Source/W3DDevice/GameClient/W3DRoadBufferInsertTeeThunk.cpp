// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?insertTee@W3DRoadBuffer@@IAEXVVector2@@HM@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp

class Vector2
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
protected:
    void insertTee(Vector2, int, float);
};

class W3DRoadBufferInsertTeeShim
{
public:
    void insert(Vector2 loc, int roadType, float width);
};

void W3DRoadBuffer::insertTee(Vector2 loc, int roadType, float width)
{
    ((W3DRoadBufferInsertTeeShim *)this)->insert(loc, roadType, width);
}
