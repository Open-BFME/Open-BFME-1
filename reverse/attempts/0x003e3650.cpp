// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAURva003E3650Struct@@@Z
// partial score=0.95 date=2026-09-10
// cl: /DNDEBUG /MD
//
// Retail 0x003E3650: the cell-space Pathfinder::iterateCellsAlongLine
// overload reached by the world-space forwarder at 0x003E7F20 (ILT
// 0x0004940E).  This BFME body specializes the Bresenham walk for finding a
// controlled object occupying a goal cell.  The user-data record is named for
// the retail address because the forwarder does not expose its fields; the
// body independently proves its two fields at +0 and +4.
//
// The local views below are deliberately TU-scoped.  The object returned by
// GameLogic::findObjectByID is accessed at the offsets used by this retail
// body (+4 team, +0x74 id, +0xd0 control flag); those offsets must not be
// generalized to the wider Object declarations in other source files.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;
typedef unsigned int ObjectID;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

class BfmeSubBIA
{
public:
	Int ask();
};

class Team
{
public:
	Int m_unknown00;
	BfmeSubBIA *m_sub;
};

class Object
{
public:
	Int m_unknown00;
	Team *m_team;
	char m_unknown08[0x74 - 0x08];
	ObjectID m_id;
};

class Player
{
public:
	char m_unknown00[0xd0];
	unsigned char m_controlFlags;
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

extern GameLogic *TheGameLogic;

class PathfindCellInfo
{
public:
	char m_unknown00[0x20];
	Int m_goalUnit;
};

class PathfindCell
{
public:
	Int getRawType( void ) const { return m_packed & 0x7; }
	Int getGoalUnit( void ) const;

	PathfindCellInfo *m_info;
	Int m_unknown04;
	Int m_unknown08;
	unsigned int m_packed;
};

inline Int PathfindCell::getGoalUnit( void ) const
{
	PathfindCellInfo *info = m_info;
	if (info != 0)
		return info->m_goalUnit;
	return 0;
}

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	char m_unknown00[0x44];
};

struct Rva003E3650Struct
{
	Object *m_found;
	ObjectID m_ignoreID;
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E3650Struct *info );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

private:
	unsigned char m_unknown00[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_unknown24[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int x, Int y )
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell( x, y );
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}

static Player *getControllingPlayer( Object *object )
{
	Team *team = object->m_team;

	if (team == 0)
		return 0;

	if (team->m_sub == 0)
		return (Player *)team;

	return (Player *)team->m_sub->ask();
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	Rva003E3650Struct *info )
{
	Int delta_x = abs( end.x - start.x );
	Int delta_y = abs( end.y - start.y );

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;

	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (start.x > end.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = start.x;
	Int y = start.y;

	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *cell = getCell( layer, x, y );
		if (cell == 0)
			return 0;

		if (cell->getRawType() == 4)
		{
			Object *object = TheGameLogic->findObjectByID( cell->getGoalUnit() );
			if (object)
			{
				Player *player = getControllingPlayer( object );
				if (player->m_controlFlags & 2)
				{
					if (object->m_id != info->m_ignoreID)
					{
						info->m_found = object;
						return 1;
					}
				}
			}
		}

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			y += yinc1;
			num += den;
			x += xinc1;
		}
	}

	return 0;
}
