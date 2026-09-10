// ??0WorldHeightMap@@IAE@XZ
// partial score=0.25 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfmeheightmap /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "GameLogic/SidesList.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"

// ??0WorldHeightMap@@IAE@XZ
WorldHeightMap::WorldHeightMap():
	m_width(0), m_height(0), m_borderSize(0), m_dataSize(0), m_data(NULL),
	m_seismicUpdateFlag(NULL), m_seismicUpdateWidth(0), m_seismicZVelocities(NULL),
	m_cellFlipState(NULL), m_flipStateWidth(0), m_cellCliffState(NULL),
	m_tileNdxes(NULL), m_blendTileNdxes(NULL), m_cliffInfoNdxes(NULL),
	m_extraBlendTileNdxes(NULL), m_numBitmapTiles(0), m_numEdgeTiles(0),
	m_numBlendedTiles(1), m_numCliffInfo(0), m_numTextureClasses(0),
	m_numEdgeTextureClasses(0), m_terrainTex(NULL), m_terrainTexHeight(1),
	m_alphaTerrainTex(NULL), m_alphaTexHeight(1), m_alphaEdgeTex(NULL),
	m_alphaEdgeHeight(0), m_drawOriginX(0), m_drawOriginY(0),
	m_drawWidthX(NORMAL_DRAW_WIDTH), m_drawHeightY(NORMAL_DRAW_HEIGHT)
{
	TheSidesList->validateSides();
	setupAlphaTiles();
}
