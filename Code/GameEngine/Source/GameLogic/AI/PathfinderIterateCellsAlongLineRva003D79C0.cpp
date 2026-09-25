// cl: /DNDEBUG /MD
//
// Retail 0x003D79C0, 566 bytes: the cell-space Pathfinder::iterateCellsAlongLine
// instance reached through ILT 0x00016103 from its world-space forwarder and from
// Pathfinder::bfmeAdjustLOSPoints. The shared Bresenham walk of
// PathfinderIterateCellsAlongLineCallbacks.cpp with its callback inlined: the
// first cell whose layer field falls outside 0x11..0x40 stops the walk and
// records that cell's centre and terrain height in the user data.
// IDENTITY OF THE USER-DATA STRUCT IS NOT RECOVERED; its name is address-derived.

extern "C" int __cdecl abs(int n);
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell
{
public:
	char m_unreconstructed[0x0c];
	unsigned int m_packed;

	__forceinline Int getLayer() const
	{
		return (m_packed >> 6) & 0x3f;
	}
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int cellX, Int cellY);

private:
	char m_unreconstructed[0x44];
};

struct Rva003FD060TerrainLogic
{
public:
	virtual void bfmeSlot0ABE(void);
	virtual void bfmeSlot1ABE(void);
	virtual void bfmeSlot2ABE(void);
	virtual void bfmeSlot3ABE(void);
	virtual void bfmeSlot4ABE(void);
	virtual void bfmeSlot5ABE(void);
	virtual void bfmeSlot6ABE(void);
	virtual Real bfmeHeightABE(Real x, Real y, PathfindLayerEnum layer,
		void *normal, Bool clip);
};

struct Rva003D79C0Struct
{
	void *owner;
	Real x;
	Real y;
	Real z;
};

class Pathfinder
{
public:
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003D79C0Struct *resultInfo);

private:
	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY)
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
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
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeK1253;
extern const Real g_bfmeDirectionWeight1285;

Int Pathfinder::iterateCellsAlongLine(const ICoord2D &startCell,
	const ICoord2D &destinationCell, PathfindLayerEnum layer,
	Rva003D79C0Struct *resultInfo)
{
	Int delta_x = abs( destinationCell.x - startCell.x );
	Int delta_y = abs( destinationCell.y - startCell.y );

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

	if (startCell.x > destinationCell.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell.y > destinationCell.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = startCell.x;
	Int y = startCell.y;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		Int cellLayer = to->getLayer();
		if (cellLayer < 0x11 || cellLayer > 0x40)
		{
			PathfindLayerEnum hitLayer = (PathfindLayerEnum)to->getLayer();
			Real wx = ((Real)x + g_bfmeK1253) * g_bfmeDirectionWeight1285;
			resultInfo->x = wx;
			Real wy = ((Real)y + g_bfmeK1253) * g_bfmeDirectionWeight1285;
			resultInfo->y = wy;
			resultInfo->z = TheTerrainLogic->bfmeHeightABE( wx, wy, hitLayer, 0, true );
			return 1;
		}

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}

	return 0;
}
