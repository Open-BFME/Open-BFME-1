struct BfmeCoord6DF1F0
{
	float x;
	float y;
	float z;
};

struct Coord3D;

class PolygonTrigger
{
public:
	bool bfmeContainsPointAt0018FA20(Coord3D &point) const;
};

struct BfmePlayer6DF1F0
{
	char m_padding00[0x24];
	int m_index24;
};

struct BfmePlayerList6DF1F0
{
	char m_padding00[0x0c];
	BfmePlayer6DF1F0 *m_localPlayer0c;
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *point) const;
};

// ?ThePlayerList@@3PAVPlayerList@@A -- retail 0x012ED748, defined once in
// Common/RTS/PlayerList.cpp. The view above is this TU's own layout of it.
class PlayerList;
extern PlayerList *ThePlayerList;
class ShroudManager;
extern ShroudManager *TheShroudManager;


class Rva006DF1F0
{
public:
	bool allowsLocation(const BfmeCoord6DF1F0 *point) const;

private:
	char m_padding00[0x1c];
	PolygonTrigger *m_polygon1c;
};

bool Rva006DF1F0::allowsLocation(const BfmeCoord6DF1F0 *point) const
{
	if (m_polygon1c == 0)
		return true;

	int playerIndex = ((BfmePlayerList6DF1F0 *)ThePlayerList)->m_localPlayer0c->m_index24;
	if ((*reinterpret_cast<PartitionManager **>(&TheShroudManager))->getShroudStatusForPlayer(playerIndex, reinterpret_cast<const Coord3D *>(point)) == CELLSHROUD_SHROUDED)
		return false;

	if (m_polygon1c->bfmeContainsPointAt0018FA20(*reinterpret_cast<Coord3D *>(const_cast<BfmeCoord6DF1F0 *>(point))))
		return true;
	return false;
}
