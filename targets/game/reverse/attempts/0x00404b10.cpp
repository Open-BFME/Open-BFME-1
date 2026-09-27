// ?d_00404b10@@YAXXZ
// partial score=0.07603614833 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Full BFME body [0x00404B10,0x00405799), 3209 bytes. Native reconstruction, NOT matched.
// Measurement: 3269B vs 3209B; 2965 positional masked differences; 22 shifted
// relocations; frame 38 vs 34. Masked same-position fraction=244/3209=.076036148.
// Normalized instruction shape=.907 is NOT a byte-match score.
// Fresh Ghidra and retail recover the tree branch absent in the original bank.
// Cell zone is +0xA, flags +0xC; cells are 16B and layers are 0x44B.
// PathfindZoneManagerConstructor independently witnesses the three 12x6 tables
// at +2329C/+233BC/+234DC and the 52B-node tree at +235FC. The node payload
// is a packed pair at +10 followed by two 16B property records (+14/+24).
// The original bank swapped grid axes and dropped the sixth merge argument.
// Retail makes twenty cdecl calls through 0002B648 to native 00403C90/107:
// args source,target,equivalency,heads,next,maxZone; ADD ESP,18. Callee ignores
// maxZone, as the assert-only sizeOfZE argument does in the Zero Hour twin.
// The alias below uses the existing ILT symbol and makes no speculative pin.
// The other direct target is STLport _Rb_global<bool>::_M_increment at 0082B870.
// Existing bank names are retained; newly recovered node records keep the RVA.
#include <map>
typedef unsigned short zoneStorageType;

struct BfmeZoneRegion
{
	int loX;
	int loY;
	int hiX;
	int hiY;
};

struct BfmeZoneCell
{
	void *info;
	unsigned int unused4;
	unsigned short rva008;
	zoneStorageType zone;
	unsigned int flags;
    bool flag20Set() const { return (flags >> 20) & 1; }
    bool flag21Set() const { return (flags >> 21) & 1; }
};

struct BfmeZoneLayer
{
	unsigned char opaque[0x30];
	zoneStorageType zone;
	unsigned char tail[0x12];
};

void bfmeResolveZones(int sourceZone, int targetZone,
	zoneStorageType *zoneEquivalency, zoneStorageType *zoneListHeads,
	zoneStorageType *zoneListNext, unsigned int sizeOfZones);
#pragma comment(linker, "/alternatename:?bfmeResolveZones@@YAXHHPAG00I@Z=?j_0002b648@@YAXXZ")

// Retail tests this bool at VA 0x012B4D2C before choosing grid or tree traversal.
// Its semantic name is unproved; no symbol pin is added for this bank.
extern bool g_rva012B4D2CUseZonePairs;

struct Rva00404B10CellProperties
{
    unsigned short type;
    unsigned short padding;
    unsigned int layer;
    unsigned int connectLayer;
    bool flag20;
    bool flag21;
    unsigned short profileLayer;
};
struct Rva00404B10ZoneEdge : public _STL::_Rb_tree_node_base
{
    unsigned int zonePair;
    Rva00404B10CellProperties source;
    Rva00404B10CellProperties target;
};
class PathfindZoneManager
{
public:
	void bfmeBuildProfileZones(BfmeZoneCell **map, BfmeZoneLayer *layers,
		const BfmeZoneRegion &bounds, int startPercent, int endPercent);

private:
	unsigned char m_beforeMaxZone[0x23298];
	unsigned int m_maxZone;
	zoneStorageType *m_zoneEquivalency[12][6];
	zoneStorageType *m_zoneListHeads[12][6];
	zoneStorageType *m_zoneListNext[12][6];
	_STL::_Rb_tree_node_base *m_incrementalObjects;
	unsigned int m_pairCount;
	unsigned int m_compare;
	Rva00404B10ZoneEdge *m_currentIncrementalObject;
};


static bool sameProfileCell(const BfmeZoneCell &a, const BfmeZoneCell &b,
    int layer, bool flag20, bool flag21)
{
    bool same = true;
    if (layer > 0 && ((int)((a.flags >> 22) & 3) > layer) !=
        ((int)((b.flags >> 22) & 3) > layer)) same = false;
    if (flag20 && (a.flag20Set() != b.flag20Set())) same = false;
    if (flag21 && (a.flag21Set() != b.flag21Set())) same = false;
    return same;
}

static unsigned int substituteZero(unsigned int value, unsigned int replacement)
{
	unsigned int type = value & 7;
    unsigned int result = replacement;
    if(type != 0) result = type;
    return result;
}

void PathfindZoneManager::bfmeBuildProfileZones(BfmeZoneCell **map,
	BfmeZoneLayer *layers, const BfmeZoneRegion &bounds,
	int startPercent, int endPercent)
{
	if (startPercent == 0)
	{
		for (int table = 0; table < 6; ++table)
		{
			for (int profile = 0; profile < 12; ++profile)
			{
				for (unsigned int zone = 0; zone < m_maxZone; ++zone)
				{
					m_zoneEquivalency[profile][table][zone] =
						(zoneStorageType)zone;
					m_zoneListHeads[profile][table][zone] =
						(zoneStorageType)zone;
					m_zoneListNext[profile][table][zone] = 0xffff;
				}
			}
		}
		m_currentIncrementalObject =
			(Rva00404B10ZoneEdge *)m_incrementalObjects->_M_left;
	}

	int firstObject = m_pairCount * (unsigned int)startPercent / 100;
	int lastObject = m_pairCount * (unsigned int)endPercent / 100;
	int width = bounds.hiY - bounds.loY + 1;
	int firstY = bounds.loY + width * startPercent / 100;
	int lastY = bounds.loY + width * endPercent / 100;

	for (int profile = 0; profile < 12; ++profile)
	{
		int layer = profile % 3;
		unsigned int profileFlags = profile / 3;
		bool flag20 = (profileFlags & 1) != 0;
		bool flag21 = ((profileFlags >> 1) & 1) != 0;

        if (g_rva012B4D2CUseZonePairs)
        {

            for (int y = firstY; y < lastY; ++y)
                for (int x = bounds.loX; x <= bounds.hiX; ++x)
                {
                    BfmeZoneCell &cell = map[x][y];
                    int connectLayer = (cell.flags >> 12) & 0x3f;
                    if (connectLayer >= 2 && connectLayer <= 15 && (cell.flags & 7) == 0)
                        bfmeResolveZones(cell.zone, layers[connectLayer].zone,
                            m_zoneEquivalency[profile][0], m_zoneListHeads[profile][0],
                            m_zoneListNext[profile][0], m_maxZone);
                }
            Rva00404B10ZoneEdge *edge = m_currentIncrementalObject;
            for (int index = firstObject; index < lastObject; ++index)
            {
                unsigned int zonePair = edge->zonePair;
                unsigned short sourceZone = (unsigned short)(zonePair >> 16);
                unsigned short targetZone = (unsigned short)zonePair;
                if ((layer <= 0 || ((int)edge->source.profileLayer > layer) ==
                                   ((int)edge->target.profileLayer > layer)) &&
                    (!flag20 || edge->source.flag20 == edge->target.flag20) &&
                    (!flag21 || edge->source.flag21 == edge->target.flag21))
                {
                    {
                    int sourceType = 1;
                    if (edge->source.type != 0) sourceType = edge->source.type;
                    int targetType;
                    if (edge->target.type == 0) targetType = 1;
                    else targetType = edge->target.type;
                    if (sourceType == targetType &&
                        edge->source.layer == edge->target.layer)
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][2],
                            m_zoneListHeads[profile][2],m_zoneListNext[profile][2],m_maxZone);
                    }
                    {
                    int sourceType = 3;
                    if (edge->source.type != 0) sourceType = edge->source.type;
                    int targetType;
                    if (edge->target.type == 0) targetType = 3;
                    else targetType = edge->target.type;
                    if (sourceType == targetType &&
                        edge->source.layer == edge->target.layer)
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][3],
                            m_zoneListHeads[profile][3],m_zoneListNext[profile][3],m_maxZone);
                    }
                    {
                    int sourceType = 2;
                    if (edge->source.type != 0) sourceType = edge->source.type;
                    int targetType;
                    if (edge->target.type == 0) targetType = 2;
                    else targetType = edge->target.type;
                    if (sourceType == targetType &&
                        edge->source.layer == edge->target.layer)
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][1],
                            m_zoneListHeads[profile][1],m_zoneListNext[profile][1],m_maxZone);
                    }
                    {
                    int sourceType = 4;
                    if (edge->source.type != 0) sourceType = edge->source.type;
                    int targetType;
                    if (edge->target.type == 0) targetType = 4;
                    else targetType = edge->target.type;
                    if (sourceType == targetType &&
                        edge->source.layer == edge->target.layer)
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][4],
                            m_zoneListHeads[profile][4],m_zoneListNext[profile][4],m_maxZone);
                    }
                    if ((edge->source.type == 2) == (edge->target.type == 2))
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][5],
                            m_zoneListHeads[profile][5],m_zoneListNext[profile][5],m_maxZone);
                    if (edge->source.type == edge->target.type &&
                        (edge->source.layer == edge->target.layer ||
                         edge->source.layer == edge->target.connectLayer ||
                         edge->source.connectLayer == edge->target.layer ||
                         (edge->source.connectLayer == 16 && edge->target.connectLayer == 16)))
                        bfmeResolveZones(sourceZone,targetZone,m_zoneEquivalency[profile][0],
                            m_zoneListHeads[profile][0],m_zoneListNext[profile][0],m_maxZone);
                }
                edge = (Rva00404B10ZoneEdge *)_STL::_Rb_global<bool>::_M_increment(edge);
            }
            if (profile == 11) m_currentIncrementalObject = edge;
        }
        else
        {

			for (int y = firstY; y < lastY; ++y)
			{
				for (int x = bounds.loX; x <= bounds.hiX; ++x)
				{
					BfmeZoneCell &cell = map[x][y];
					int connectLayer = (cell.flags >> 12) & 0x3f;
					if (connectLayer >= 2 && connectLayer <= 15 &&
						(cell.flags & 7) == 0)
					{
						bfmeResolveZones(cell.zone, layers[connectLayer].zone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0], m_maxZone);
					}

					int cellZone = cell.zone;
					if (x <= bounds.loX)
						goto check_left_cell;
					{
					int otherZone = map[x - 1][y].zone;
					if (cellZone == otherZone ||
						!sameProfileCell(cell, map[x - 1][y], layer,
							flag20, flag21))
						goto check_left_cell;

					if (substituteZero(cell.flags, 1) == substituteZero(map[x - 1][y].flags, 1) &&
						((cell.flags ^ map[x - 1][y].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][2],
							m_zoneListHeads[profile][2],
							m_zoneListNext[profile][2], m_maxZone);

					if (substituteZero(cell.flags, 3) == substituteZero(map[x - 1][y].flags, 3) &&
						((cell.flags ^ map[x - 1][y].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][3],
							m_zoneListHeads[profile][3],
							m_zoneListNext[profile][3], m_maxZone);

					if (substituteZero(cell.flags, 2) == substituteZero(map[x - 1][y].flags, 2) &&
						((cell.flags ^ map[x - 1][y].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][1],
							m_zoneListHeads[profile][1],
							m_zoneListNext[profile][1], m_maxZone);

					if (substituteZero(cell.flags, 4) == substituteZero(map[x - 1][y].flags, 4) &&
						((cell.flags ^ map[x - 1][y].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][4],
							m_zoneListHeads[profile][4],
							m_zoneListNext[profile][4], m_maxZone);

					if (((cell.flags & 7) == 2) == ((map[x - 1][y].flags & 7) == 2))
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][5],
							m_zoneListHeads[profile][5],
							m_zoneListNext[profile][5], m_maxZone);

					if (((cell.flags ^ map[x - 1][y].flags) & 7) == 0 &&
                        (((cell.flags >> 6) & 0x3f) == ((map[x - 1][y].flags >> 6) & 0x3f) ||
                         ((cell.flags >> 6) & 0x3f) == ((map[x - 1][y].flags >> 12) & 0x3f) ||
                         ((cell.flags >> 12) & 0x3f) == ((map[x - 1][y].flags >> 6) & 0x3f) ||
                         (((cell.flags >> 12) & 0x3f) == 16 && ((map[x - 1][y].flags >> 12) & 0x3f) == 16)))
						bfmeResolveZones(cellZone, otherZone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0], m_maxZone);
					}

				check_left_cell:
					if (y <= bounds.loY)
						continue;
					int leftZone = map[x][y - 1].zone;
					if (cellZone == leftZone ||
						!sameProfileCell(cell, map[x][y - 1], layer,
							flag20, flag21))
						continue;

					if (substituteZero(cell.flags, 1) == substituteZero(map[x][y - 1].flags, 1) &&
						((cell.flags ^ map[x][y - 1].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][2],
							m_zoneListHeads[profile][2],
							m_zoneListNext[profile][2], m_maxZone);
					if (substituteZero(cell.flags, 3) == substituteZero(map[x][y - 1].flags, 3) &&
						((cell.flags ^ map[x][y - 1].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][3],
							m_zoneListHeads[profile][3],
							m_zoneListNext[profile][3], m_maxZone);
					if (substituteZero(cell.flags, 2) == substituteZero(map[x][y - 1].flags, 2) &&
						((cell.flags ^ map[x][y - 1].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][1],
							m_zoneListHeads[profile][1],
							m_zoneListNext[profile][1], m_maxZone);
					if (substituteZero(cell.flags, 4) == substituteZero(map[x][y - 1].flags, 4) &&
						((cell.flags ^ map[x][y - 1].flags) & 0xfc0) == 0)
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][4],
							m_zoneListHeads[profile][4],
							m_zoneListNext[profile][4], m_maxZone);
					if (((cell.flags & 7) == 2) == ((map[x][y - 1].flags & 7) == 2))
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][5],
							m_zoneListHeads[profile][5],
							m_zoneListNext[profile][5], m_maxZone);

					if (((cell.flags ^ map[x][y - 1].flags) & 7) == 0 &&
                        (((cell.flags >> 6) & 0x3f) == ((map[x][y - 1].flags >> 6) & 0x3f) ||
                         ((cell.flags >> 6) & 0x3f) == ((map[x][y - 1].flags >> 12) & 0x3f) ||
                         ((cell.flags >> 12) & 0x3f) == ((map[x][y - 1].flags >> 6) & 0x3f) ||
                         (((cell.flags >> 12) & 0x3f) == 16 && ((map[x][y - 1].flags >> 12) & 0x3f) == 16)))
						bfmeResolveZones(cellZone, leftZone,
							m_zoneEquivalency[profile][0],
							m_zoneListHeads[profile][0],
							m_zoneListNext[profile][0], m_maxZone);
				}
			}
		        }
	}
}
