// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib

struct TBlendTileInfo;

class BFMERetailWorldHeightMap
{
public:
    void blendTileData(TBlendTileInfo *blend, int width);
};

class BFMERetailWorldHeightMapBlendTileDataShim
{
public:
    void blendTileData(TBlendTileInfo *, int);
};

void BFMERetailWorldHeightMap::blendTileData(TBlendTileInfo *blend, int width)
{
    ((BFMERetailWorldHeightMapBlendTileDataShim *)this)->blendTileData(blend, width);
}
