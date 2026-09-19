// ?d_003d79c0@@YAXXZ
// partial score=0.23 date=2026-09-20
// cl: /DNDEBUG /MD

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
	PathfindCell *getCell(Int x, Int y);

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

class Rva003D79C0Pathfinder
{
public:
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003D79C0Struct *userData);

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

	__forceinline PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeK1253;
extern const Real g_bfmeDirectionWeight1285;

Int Rva003D79C0Pathfinder::iterateCellsAlongLine(const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	Rva003D79C0Struct *userData)
{
	const ICoord2D *start_ptr = &start;
	const ICoord2D *end_ptr = &end;
	Int end_x = end_ptr->x;
	Int x = start_ptr->x;
	Int delta_x = abs(end_x - x);
	Int y = start_ptr->y;
	Int end_y = end_ptr->y;
	Int delta_y = abs(end_y - y);

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

	if (start.x > end_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		register PathfindCell *cell = getCell(layer, x, y);
		if (cell == 0)
			return 0;

		unsigned int layerWord = cell->m_packed;
		Int cellLayer = (layerWord >> 6) & 0x3f;
		if (cellLayer >= 0x11 && cellLayer <= 0x40)
		{
			userData->x = ((Real)x + g_bfmeK1253) * g_bfmeDirectionWeight1285;
			userData->y = ((Real)y + g_bfmeK1253) * g_bfmeDirectionWeight1285;
			layerWord = cell->m_packed;
			userData->z = TheTerrainLogic->bfmeHeightABE(
				userData->x, userData->y,
				(PathfindLayerEnum)((layerWord >> 6) & 0x3f), 0, true);
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
