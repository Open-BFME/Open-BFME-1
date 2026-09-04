// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "W3DDevice/GameClient/WorldHeightMap.h"

// BFME's edge-class records are forty bytes and live at +0xd0d0.  The
// reference header describes the older record layout, so keep this overlay
struct BfmeEdgeTextureClass007475D0
{
	Int width;
	char pad04[8];
	ICoord2D positionInTexture;
	char pad14[0x14];
};

struct BfmeWorldHeightMap007475D0
{
	char pad0[0xd0d0];
	BfmeEdgeTextureClass007475D0 edgeTextureClasses[256];
	char padAfterEdges[0x2808];
	Int alphaEdgeHeight;
};

// ?getUVForBlend@WorldHeightMap@@QAEXHPAURegion2D@@@Z
void WorldHeightMap::getUVForBlend(Int edgeClass, Region2D *range)
{
	BfmeWorldHeightMap007475D0 *self =
		reinterpret_cast<BfmeWorldHeightMap007475D0 *>(this);
	ICoord2D pos = self->edgeTextureClasses[edgeClass].positionInTexture;
	Int width = self->edgeTextureClasses[edgeClass].width;

	range->lo.x = (Real)pos.x / TEXTURE_WIDTH;
	range->lo.y = (Real)pos.y / self->alphaEdgeHeight;
	range->hi.x = ((Real)pos.x + width * TILE_PIXEL_EXTENT) / TEXTURE_WIDTH;
	range->hi.y = ((Real)pos.y + width * TILE_PIXEL_EXTENT) / self->alphaEdgeHeight;
}
