// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x006C39D0, 1772 bytes: W3DRadar::buildTerrainTexture.  The matched
// W3DRadar::refreshTerrain (0x006C4280) reaches it through ILT 0x0002248F.
// BFME first looks for "<map>_art.tga" beside the pristine map and, when it
// exists, installs it as the radar image; otherwise it samples the terrain the
// way the original Generals W3DRadar.cpp does (integer z, getGroundHeight per
// water sample, isUnderwater without a terrain-Z out parameter), not the Zero
// Hour variant.
//
// Shape notes: the extension scan reads peek()[dot] (that spelling is what
// holds '.' in cl); findObjectByID is STLport hash_map::find over a
// {start, finish} bucket vector, which reloads the bucket base after the div;
// the sampling half sits in its own block so the map-art temporary and the
// surface share one stack slot.

#include <string.h>
#pragma intrinsic(strlen)

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef Int Color;
typedef UnsignedInt ObjectID;

#define TRUE true
#define FALSE false
#define NULL 0

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}

private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	void concat(const T *text, int length);
	void removeLastChar();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	Int getLength() const { return m_data ? m_data->length : 0; }
	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const { return m_data ? m_data->data : ""; }
	char *peek() const { return m_data->data; }
	void removeLastChar() { ((StringBase<char> *)this)->removeLastChar(); }
	void concat(const char *text) { ((StringBase<char> *)this)->concat(text, strlen(text)); }
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;

	void setFromInt(Int c)
	{
		red = ((c >> 16) & 0xff) / 255.0f;
		green = ((c >> 8) & 0xff) / 255.0f;
		blue = (c & 0xff) / 255.0f;
	}
};

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

class GameState
{
public:
	AsciiString getPristineMapName();
};
extern GameState *TheGameState;

class FileSystem
{
public:
	Bool doesFileExist(const char *filename) const;
};
extern FileSystem *TheFileSystem;

// Release_Ref is the shared ref-counted release leaf at 0x009EB7A0.
class TextureClass
{
public:
	void Release_Ref();
	void addRef() { ++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4); }
};

// Matched 0x0044F4D0: builds the ref-counted image object from a file name.
class Rva0044F4D0
{
public:
	Rva0044F4D0(int what);
	~Rva0044F4D0()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	Rva0044F4D0 &operator=(const Rva0044F4D0 &other)
	{
		if (other.m_ptr)
			other.m_ptr->addRef();
		if (m_ptr)
			m_ptr->Release_Ref();
		m_ptr = other.m_ptr;
		return *this;
	}
	void clear()
	{
		if (m_ptr)
		{
			m_ptr->Release_Ref();
			m_ptr = NULL;
		}
	}

	TextureClass *m_ptr;
};

class Gen006C1A20ImageState
{
public:
	void initialize();
};

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

class Rva006C39D0Lock
{
public:
	Rva006C39D0Lock() { W3DRadarResetLock(); }
	~Rva006C39D0Lock() { bfmeUnlock1179(); }
};

class SurfaceClass
{
public:
	void DrawPixel(const unsigned int x, const unsigned int y, unsigned int color);
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);

	void *m_texture;
};

class BridgeInfo
{
public:
	Coord3D from, to;
	Real bridgeWidth;
	Coord3D fromLeft, fromRight, toLeft, toRight;
	Int bridgeIndex;
	Int curDamageState;
	ObjectID bridgeObjectID;
};

class Bridge
{
public:
	AsciiString getBridgeTemplateName(void);
	BridgeInfo *peekBridgeInfo(void) { return &m_bridgeInfo; }

private:
	unsigned char m_unmodelled_00[0xc];
	BridgeInfo m_bridgeInfo;
};

class TerrainLogic
{
public:
	virtual void vf00();
	virtual void vf04();
	virtual void vf08();
	virtual void vf0c();
	virtual void vf10();
	virtual void vf14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL);
	virtual void vf1c();
	virtual void vf20();
	virtual void vf24();
	virtual void vf28();
	virtual void vf2c();
	virtual void vf30();
	virtual void vf34();
	virtual void vf38();
	virtual void vf3c();
	virtual void vf40();
	virtual void vf44();
	virtual void vf48();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL);
	virtual void vf50();
	virtual void vf54();
	virtual void vf58();
	virtual void vf5c();
	virtual void vf60();
	virtual void vf64();
	virtual void vf68();
	virtual void vf6c();
	virtual void vf70();
	virtual void vf74();
	virtual void vf78();
	virtual void vf7c();
	virtual void vf80();
	virtual void vf84();
	virtual void vf88();
	virtual void vf8c();
	virtual void vf90();
	virtual void vf94();
	virtual Bridge *findBridgeAt(const Coord3D *loc);
};
extern TerrainLogic *TheTerrainLogic;

class TerrainVisual
{
public:
	virtual void vf00();
	virtual void vf04();
	virtual void vf08();
	virtual void vf0c();
	virtual void vf10();
	virtual void vf14();
	virtual void vf18();
	virtual void getTerrainColorAt(Real x, Real y, RGBColor *pColor);
};
extern TerrainVisual *TheTerrainVisual;

class TerrainRoadType
{
public:
	RGBColor getRadarColor(void) { return m_radarColor; }

private:
	unsigned char m_unmodelled_00[0x28];
	RGBColor m_radarColor;
};

class TerrainRoadCollection
{
public:
	TerrainRoadType *findBridge(AsciiString name);
};
extern TerrainRoadCollection *TheTerrainRoads;

class Object;

class BodyModuleInterface
{
public:
	virtual void vf00();
	virtual void vf04();
	virtual void vf08();
	virtual void vf0c();
	virtual void vf10();
	virtual void vf14();
	virtual void vf18();
	virtual void vf1c();
	virtual Int getDamageState() const;
};

enum { BODY_RUBBLE = 3 };

class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body200; }

private:
	unsigned char m_unmodelled_000[0x200];
	BodyModuleInterface *m_body200;
};

// STLport hash_map<ObjectID, Object *> node: next, key, value.
struct Rva006C39D0ObjectNode
{
	Rva006C39D0ObjectNode *m_next;
	ObjectID m_id;
	Object *m_object;
};

struct Rva006C39D0ObjectIterator
{
	Rva006C39D0ObjectIterator(Rva006C39D0ObjectNode *node, const void *table) : m_cur(node), m_table(table) {}
	Rva006C39D0ObjectNode *m_cur;
	const void *m_table;
};

struct Rva006C39D0BucketVector
{
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	Rva006C39D0ObjectNode *&operator[](UnsignedInt n) { return *(m_start + n); }

	Rva006C39D0ObjectNode **m_start;
	Rva006C39D0ObjectNode **m_finish;
};

class GameLogic
{
public:
	UnsignedInt bucketCount() const { return m_buckets.size(); }
	Rva006C39D0ObjectIterator find(ObjectID id)
	{
		UnsignedInt n = id % bucketCount();
		Rva006C39D0ObjectNode *first;
		for (first = m_buckets[n]; first && first->m_id != id; first = first->m_next)
		{
		}
		return Rva006C39D0ObjectIterator(first, this);
	}
	Rva006C39D0ObjectIterator end() { return Rva006C39D0ObjectIterator(NULL, this); }
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return NULL;
		Rva006C39D0ObjectIterator it = find(id);
		if (it.m_cur == end().m_cur)
			return NULL;
		return it.m_cur->m_object;
	}

private:
	unsigned char m_unmodelled_00[0xb4];
	Rva006C39D0BucketVector m_buckets;
};
extern GameLogic *TheGameLogic;

class Radar
{
public:
	Bool radarToWorld(const ICoord2D *radar, Coord3D *world);
	Real getTerrainAverageZ(void) const { return m_terrainAverageZ; }

protected:
	unsigned char m_unmodelled_00[0x18];
	Real m_terrainAverageZ;
};

class W3DRadar : public Radar
{
protected:
	void buildTerrainTexture(TerrainLogic *terrain);
	void interpolateColorForHeight(RGBColor *color, Real height, Real hiZ, Real midZ, Real loZ);

	unsigned char m_unmodelled_01c[0x143c - 0x1c];
	Coord3D m_mapExtentLo143c;
	Coord3D m_mapExtentHi1448;
	unsigned char m_unmodelled_1454[0x1478 - 0x1454];
	W3DRadarResetTexture m_texture1478;
	Rva0044F4D0 m_mapArt147c;
	unsigned char m_unmodelled_1480[0x14a4 - 0x1480];
	Int m_textureWidth14a4;
	Int m_textureHeight14a8;
	unsigned char m_unmodelled_14ac[0x14dc - 0x14ac];
	Bool m_reconstructViewBox14dc;
	Bool m_hasMapArt14dd;
};

// ?buildTerrainTexture@W3DRadar@@IAEXPAVTerrainLogic@@@Z
void W3DRadar::buildTerrainTexture(TerrainLogic *terrain)
{
	m_reconstructViewBox14dc = TRUE;

	AsciiString mapName = TheGameState->getPristineMapName();
	if (!mapName.isEmpty())
	{
		Int dot = mapName.getLength();
		while (--dot > 0 && mapName.peek()[dot] != '.')
			;
		if (dot > 0)
		{
			while (mapName.getLength() > dot)
				mapName.removeLastChar();
			mapName.concat("_art.tga");
			if (TheFileSystem->doesFileExist(mapName.str()))
			{
				m_mapArt147c.clear();
				m_mapArt147c = Rva0044F4D0((int)mapName.str());
				m_hasMapArt14dd = TRUE;
				reinterpret_cast<Gen006C1A20ImageState *>(this)->initialize();
				return;
			}
		}
	}

	m_hasMapArt14dd = FALSE;
	reinterpret_cast<Gen006C1A20ImageState *>(this)->initialize();

	{
	Rva006C39D0Lock lock;
	W3DRadarResetSurface surface = m_texture1478.getSurfaceLevel();

	RGBColor waterColor;
	waterColor.red = 0.55f;
	waterColor.green = 0.55f;
	waterColor.blue = 1.0f;

	// build the terrain
	RGBColor sampleColor;
	RGBColor color;
	Int i, j, samples;
	Int x, y, z;
	ICoord2D radarPoint;
	Coord3D worldPoint;
	Bridge *bridge;
	for (y = 0; y < m_textureHeight14a8; y++)
	{
		for (x = 0; x < m_textureWidth14a4; x++)
		{
			radarPoint.x = x;
			radarPoint.y = y;
			radarToWorld(&radarPoint, &worldPoint);

			z = terrain->getGroundHeight(worldPoint.x, worldPoint.y);

			Bool workingBridge = FALSE;
			bridge = TheTerrainLogic->findBridgeAt(&worldPoint);
			if (bridge != NULL)
			{
				Object *obj = TheGameLogic->findObjectByID(bridge->peekBridgeInfo()->bridgeObjectID);
				if (obj)
				{
					BodyModuleInterface *body = obj->getBodyModule();
					if (body->getDamageState() != BODY_RUBBLE)
						workingBridge = TRUE;
				}
			}

			Real waterZ;
			if (workingBridge == FALSE && terrain->isUnderwater(worldPoint.x, worldPoint.y, &waterZ))
			{
				const Int waterSamplesAway = 1;

				sampleColor.red = sampleColor.green = sampleColor.blue = 0.0f;
				samples = 0;

				for (j = y - waterSamplesAway; j <= y + waterSamplesAway; j++)
				{
					if (j >= 0 && j < m_textureHeight14a8)
					{
						for (i = x - waterSamplesAway; i <= x + waterSamplesAway; i++)
						{
							if (i >= 0 && i < m_textureWidth14a4)
							{
								radarPoint.x = i;
								radarPoint.y = j;
								radarToWorld(&radarPoint, &worldPoint);

								Real underwaterZ = terrain->getGroundHeight(worldPoint.x, worldPoint.y);

								if (terrain->isUnderwater(worldPoint.x, worldPoint.y))
								{
									color = waterColor;

									interpolateColorForHeight(&color, underwaterZ, waterZ,
										waterZ,
										m_mapExtentLo143c.z);

									sampleColor.red += color.red;
									sampleColor.green += color.green;
									sampleColor.blue += color.blue;
									samples++;
								}
							}
						}
					}
				}

				if (samples == 0)
					samples = 1;

				color.red = sampleColor.red / (Real)samples;
				color.green = sampleColor.green / (Real)samples;
				color.blue = sampleColor.blue / (Real)samples;
			}
			else
			{
				const Int samplesAway = 1;

				sampleColor.red = sampleColor.green = sampleColor.blue = 0.0f;
				samples = 0;

				for (j = y - samplesAway; j <= y + samplesAway; j++)
				{
					if (j >= 0 && j < m_textureHeight14a8)
					{
						for (i = x - samplesAway; i <= x + samplesAway; i++)
						{
							if (i >= 0 && i < m_textureWidth14a4)
							{
								radarPoint.x = i;
								radarPoint.y = j;
								radarToWorld(&radarPoint, &worldPoint);

								if (workingBridge)
								{
									AsciiString bridgeTName = bridge->getBridgeTemplateName();
									TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge(bridgeTName);

									if (bridgeTemplate)
										color = bridgeTemplate->getRadarColor();
									else
										color.setFromInt(0xffffffff);

									Real bridgeHeight = (bridge->peekBridgeInfo()->fromLeft.z +
										bridge->peekBridgeInfo()->fromRight.z +
										bridge->peekBridgeInfo()->toLeft.z +
										bridge->peekBridgeInfo()->toRight.z) / 4.0f;

									interpolateColorForHeight(&color, bridgeHeight,
										getTerrainAverageZ(),
										m_mapExtentHi1448.z, m_mapExtentLo143c.z);
								}
								else
								{
									TheTerrainVisual->getTerrainColorAt(worldPoint.x, worldPoint.y, &color);

									interpolateColorForHeight(&color, z, getTerrainAverageZ(),
										m_mapExtentHi1448.z, m_mapExtentLo143c.z);
								}

								sampleColor.red += color.red;
								sampleColor.green += color.green;
								sampleColor.blue += color.blue;
								samples++;
							}
						}
					}
				}

				if (samples == 0)
					samples = 1;

				color.red = sampleColor.red / (Real)samples;
				color.green = sampleColor.green / (Real)samples;
				color.blue = sampleColor.blue / (Real)samples;
			}

			((SurfaceClass *)&surface)->DrawPixel(x, y, GameMakeColor(color.red * 255,
				color.green * 255,
				color.blue * 255,
				255));
		}
	}
	}
}
