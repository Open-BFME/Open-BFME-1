// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAURva003E3650Struct@@@Z
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x003E3650: Pathfinder::iterateCellsAlongLine, cell-space overload.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;
typedef unsigned int ObjectID;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { PATHFIND_LAYER_GROUND = 0 };

class BfmeX1011;

class BfmeSubBIA
{
public:
	int bfmeAskBIA();
};

class Team
{
public:
	int m_field00;
	BfmeSubBIA *m_sub;
};

class Object
{
public:
	int m_field00;
	Team *m_team;
	char m_pad08[0x74 - 0x08];
	ObjectID m_id;
};

class Player
{
public:
	char m_pad00[0xd0];
	unsigned char m_fieldD0;
};

class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011( int id );
};

extern BfmeLook1011 *g_bfmeLook1011;

class PathfindCellInfo
{
public:
	char m_pad00[0x20];
	Int m_field20;
};

class PathfindCell
{
public:
	Int getRawType( void ) const { return m_packed & 0x7; }
	Int getGoalUnit( void ) const;

	PathfindCellInfo *m_info;		// +0x00
	Int m_unused1;					// +0x04
	Int m_unused2;					// +0x08
	unsigned int m_packed;			// +0x0c
};

inline Int PathfindCell::getGoalUnit( void ) const
{
	PathfindCellInfo *info = m_info;
	if (info != 0)
		return info->m_field20;
	return 0;
}

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	unsigned char m_body[0x44];		// stride 0x44
};

struct Rva003E3650Struct
{
	Object *m_found;				// +0x00
	ObjectID m_ignoreID;			// +0x04
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E3650Struct *info );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

private:
	unsigned char m_prefix[0x10];		// +0x000 opaque
	PathfindCell **m_map;				// +0x010
	IRegion2D m_extent;					// +0x014
	unsigned char m_mid[0x85c - 0x24];	// +0x024 opaque
	PathfindLayer m_layers[16];			// +0x85c
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

static Player *controllingPlayer( Object *obj )
{
	Team *team = obj->m_team;

	if (team == 0)
		return 0;

	if (team->m_sub == 0)
		return (Player *)team;

	return (Player *)team->m_sub->bfmeAskBIA();
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
	PathfindLayerEnum layer, Rva003E3650Struct *info )
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
			Object *obj = (Object *)g_bfmeLook1011->bfmeFind1011( cell->getGoalUnit() );
			if (obj)
			{
				Player *player = controllingPlayer( obj );
				if (player->m_fieldD0 & 2)
				{
					if (obj->m_id != info->m_ignoreID)
					{
						info->m_found = obj;
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
