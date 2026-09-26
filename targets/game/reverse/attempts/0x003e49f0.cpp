// ?bfmeCheckAttackViewHelper@Pathfinder@@QAEHPAVObject@@PAUCoord3D@@PAX@Z
// partial score=0.167 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// BFME perimeter-cell attack-view helper at retail 0x003E49F0.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern const Real g_bfmeScaleBK;
extern const Real g_bfmeK1253;

struct Coord3D { Real x, y, z; };

class Object
{
public:
	Int getLayer() const;

private:
	unsigned char m_pad00[0x74];
public:
	ObjectID m_id;
};

class Rva003E49F0CellInfo
{
public:
	unsigned char m_pad00[0x18];
	ObjectID m_id18;
	unsigned char m_pad1c[4];
	ObjectID m_id20;
};

class Rva003E49F0Cell
{
public:
	Rva003E49F0CellInfo *m_info;
	unsigned char m_pad04[0x0c];
};

class Rva003E49F0Layer
{
public:
	Rva003E49F0Cell *getCell(Int x, Int y);
	unsigned char m_storage[0x44];
};

class Rva003E49F0TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40();
	virtual Bool queryObjectLayer(Object *object, Int layer);
};

extern Rva003E49F0TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Int bfmeCheckAttackViewHelper(Object *object, Coord3D *position, void *cellIds);

protected:
	void getRadiusAndCenter(const Object *object, Int &radius, Bool &center);

private:
	unsigned char m_pad00[0x10];
	Rva003E49F0Cell **m_map;
	Int m_loX;
	Int m_loY;
	Int m_hiX;
	Int m_hiY;
	unsigned char m_pad24[0x85c - 0x24];
	Rva003E49F0Layer m_layers[16];
};

static __forceinline Int rva003E49F0Round(Real value)
{
	Int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

static __forceinline Int rva003E49F0Floor(Real value)
{
	return rva003E49F0Round((Real)floor((double)value));
}

static __forceinline ObjectID rva003E49F0CellId(Rva003E49F0Cell *cell)
{
	Rva003E49F0CellInfo *info = cell->m_info;
	ObjectID id = info ? info->m_id18 : 0;
	if (id == 0 && info && info->m_id20)
		id = info->m_id20;
	return id;
}

static __forceinline void rva003E49F0AddUnique(ObjectID id, ObjectID ignore,
	ObjectID *ids, Int &count)
{
	if (id == 0 || id == ignore)
		return;
	Int i = 0;
	while (i < count && ids[i] != id)
		++i;
	if (i == count)
		ids[count++] = id;
}

Int Pathfinder::bfmeCheckAttackViewHelper(Object *object, Coord3D *position,
	void *cellIds)
{
	Int radius;
	Bool centered;
	getRadiusAndCenter(object, radius, centered);

	Int x;
	Int y;
	Real scaledX = position->x;
	scaledX *= g_bfmeScaleBK;
	if (centered)
	{
		x = rva003E49F0Floor(scaledX);
		Real scaledY = position->y;
		scaledY *= g_bfmeScaleBK;
		y = rva003E49F0Floor(scaledY);
		++radius;
	}
	else
	{
		x = rva003E49F0Floor(scaledX + g_bfmeK1253);
		Real scaledY = position->y;
		scaledY *= g_bfmeScaleBK;
		y = rva003E49F0Floor(scaledY + g_bfmeK1253);
	}

	Bool terrainConfirmed = false;
	Bool useLayer = false;
	Int layer = object->getLayer();
	if (layer != 1 && layer < 16)
	{
		useLayer = true;
		terrainConfirmed = TheTerrainLogic->queryObjectLayer(object, layer);
	}

	ObjectID *ids = (ObjectID *)cellIds;
	Int count = 0;
	const Int xMin = x - radius - 1;
	const Int xMax = x + radius + 1;
	const Int yMin = y - radius - 1;
	const Int yMax = y + radius + 1;

	for (Int cellX = xMin; cellX < xMax; ++cellX)
	{
		for (Int cellY = yMin; cellY < yMax; ++cellY)
		{
			if (cellX != xMin && cellY != yMin &&
				cellX != xMax - 1 && cellY != yMax - 1)
				continue;

			if (useLayer && cellX >= m_loX && cellX <= m_hiX &&
				cellY >= m_loY && cellY <= m_hiY)
			{
				Rva003E49F0Cell *cell = 0;
				if (layer > 1 && layer <= 15)
					cell = m_layers[layer].getCell(cellX, cellY);
				if (cell == 0)
					cell = &m_map[cellX][cellY];
				rva003E49F0AddUnique(rva003E49F0CellId(cell), object->m_id,
					ids, count);
				if (count == 16)
					return 16;
			}

			if (terrainConfirmed && cellX >= m_loX && cellX <= m_hiX &&
				cellY >= m_loY && cellY <= m_hiY)
			{
				Rva003E49F0Cell *cell = &m_map[cellX][cellY];
				rva003E49F0AddUnique(rva003E49F0CellId(cell), object->m_id,
					ids, count);
				if (count == 16)
					return 16;
			}
		}
	}
	return count;
}
