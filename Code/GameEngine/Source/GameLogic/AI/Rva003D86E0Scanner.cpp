// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /I.
// ?scan@Rva003D86E0Scanner@@QAEDHH@Z
// Retail 003D86E0, 478 bytes; the 003E5010 caller supplies this work record.
// Its owner is unproven, so retain the bank's address-derived identity.
// The complete body checks every cell in the window, including packed layer
// compatibility, movement eligibility, and terrain height side effects.
// Callees are the landed PathfindLayer::getCell, Pathfinder::bfmeStepD4F90,
// and Pathfinder::iterateCellsAlongLine. TerrainLogic's canonical header
// supplies the independently witnessed getLayerHeight slot at vtable+0x1c.
// Coordinate comparison through the aggregate operator preserves retail's
// reloads and register lifetime; spelling the two scalar comparisons does not.
// stlport
#include "PreRTS.h"
#include "Code/GameEngine/Include/GameLogic/TerrainLogic.h"
inline bool operator!=(const ICoord2D &a, const ICoord2D &b)
{
    return a.x != b.x || a.y != b.y;
}
// The landed line walker accepts this address but never reads the object.
struct Rva003D7010Struct
{
};
class PathfindCell
{
  public:
    char m_pad[12];
    unsigned int m_word;
};
class PathfindLayer
{
  public:
    PathfindCell *getCell(Int cellX, Int cellY);
    char m_pad[0x44];
};
class Pathfinder
{
  public:
    bool bfmeStepD4F90(void *state, PathfindCell *cell);
    Int iterateCellsAlongLine(const ICoord2D &, const ICoord2D &, PathfindLayerEnum,
                              Rva003D7010Struct *);
    __forceinline PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY)
    {
        if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x && cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
        {
            if (layer > 1 && layer <= 15)
            {
                PathfindCell *cell = m_layers[layer].getCell(cellX, cellY);
                if (cell)
                    return cell;
            }
            return &m_map[cellX][cellY];
        }
        return 0;
    }

  private:
    char m_beforeMap[0x10];
    PathfindCell **m_map;
    struct
    {
        ICoord2D lo, hi;
    } m_extent;
    char m_beforeLayers[0x85c - 0x24];
    PathfindLayer m_layers[16];
};
class Rva003D86E0Scanner
{
  public:
    char scan(Int cellX, Int cellY);

  private:
    Pathfinder *m_pathfinder;
    void *m_field04;
    Int m_resultCellX, m_resultCellY;
    PathfindLayerEnum m_layer;
    Int m_requestedLayer;
    Int m_cachedCellX, m_cachedCellY;
    Int m_lowerCellOffset, m_upperCellOffset;
};
char Rva003D86E0Scanner::scan(Int cellX, Int cellY)
{
    for (Int x = cellX - m_lowerCellOffset; x < cellX + m_upperCellOffset; ++x)
    {
        for (Int y = cellY - m_lowerCellOffset; y < cellY + m_upperCellOffset; ++y)
        {
            PathfindCell *cell = m_pathfinder->getCell(m_layer, x, y);
            if (!cell)
                return false;
            Int type = (cell->m_word >> 6) & 0x3f;
            Int requested = m_requestedLayer;
            if (requested != type)
            {
                if (requested == 1)
                {
                    if (type != 16)
                        return false;
                }
                else if (requested != 16)
                {
                    if ((requested >= 17 && requested <= 64) || (requested >= 2 && requested <= 15))
                        if (type != 16)
                            return false;
                }
            }
            if (!m_pathfinder->bfmeStepD4F90(m_field04, cell))
                return false;
            Coord3D position;
            position.x = x * 10 + 5.0f;
            position.y = y * 10 + 5.0f;
            TheTerrainLogic->getLayerHeight(position.x, position.y, (PathfindLayerEnum)type, 0,
                                            true);
        }
    }
    m_resultCellX = cellX;
    m_resultCellY = cellY;
    if (m_requestedLayer == 1 || m_requestedLayer >= 16)
    {
        if (*(ICoord2D *)&m_resultCellX != *(ICoord2D *)&m_cachedCellX)
        {
            Rva003D7010Struct data;
            if (m_pathfinder->iterateCellsAlongLine(*(ICoord2D *)&m_resultCellX,
                                                    *(ICoord2D *)&m_cachedCellX,
                                                    (PathfindLayerEnum)m_requestedLayer, &data))
                return false;
        }
    }
    return true;
}
