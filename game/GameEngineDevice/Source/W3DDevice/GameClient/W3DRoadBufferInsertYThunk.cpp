// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?insertY@W3DRoadBuffer@@IAE_NVVector2@@HM@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer.cpp

class Vector2
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
protected:
    bool insertY(Vector2 loc, int index1, float scale);
};

class W3DRoadBufferInsertYShim
{
public:
    bool insertY(Vector2, int, float);
};

bool W3DRoadBuffer::insertY(Vector2 loc, int index1, float scale)
{
    return ((W3DRoadBufferInsertYShim *)this)->insertY(loc, index1, scale);
}
