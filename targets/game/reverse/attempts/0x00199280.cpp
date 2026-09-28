// ?writeCastleTemplates@Rva00199280Owner@@QAEXAAVDataChunkOutput@@PAVMapObject@@ABVAsciiString@@PAVPolygonTrigger@@@Z
// partial score=0.87 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <string.h>
#include "ascii_string.h"
#pragma intrinsic(strlen)

typedef int Int;
typedef float Real;
typedef bool Bool;

template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <typename T> inline const T *StringBase<T>::str() const {
    static const T TheNullChr = 0;
    return m_data ? m_data->data : &TheNullChr;
}
template <typename T> inline T StringBase<T>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
template <typename T> inline bool StringBase<T>::isEmpty() const { return m_data ? m_data->length == 0 : true; }
template <typename T> inline bool StringBase<T>::isNotEmpty() const { return m_data != 0 && m_data->length != 0; }
template <typename T> inline void StringBase<T>::concat(T c) { concat(&c, 1); }
template <typename T> inline bool StringBase<T>::endsWithNoCase(const T *s) const { return endsWithNoCase(s, strlen(s)); }

// AsciiString::TheEmptyString under its pinned address-token name.
extern const AsciiString Rva01336E50EmptyString;

struct Coord3D { Real x, y, z; };
struct ICoord3D { Int x, y, z; };

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	NameKeyType nameToKey(const AsciiString &name) { return nameToKey(name.str()); }
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;
extern const StaticNameKey TheKey_objectIsABase;
extern const StaticNameKey TheKey_objectBaseName;

class Dict
{
public:
	Bool getBool(NameKeyType key, Bool *exists = 0) const;
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void closeDataChunk();
	void writeReal(Real r);
	void writeInt(Int i);
	void writeAsciiString(const AsciiString &name);
	void writeNameKey(const NameKeyType key);
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	unsigned int getKindOfWord() const { return m_kindof; }
private:
	char m_pad00[0x20];
	AsciiString m_name;
	char m_pad24[0xc8 - 0x24];
	unsigned int m_kindof;
};

// Established address-token views of the two out-of-line MapObject accessors
// (0x00087E80 template with override chain, 0x00087CC0 location).
struct BfmeSlotJA;
class BfmeThing932A { public: BfmeSlotJA *bfmeGo932A(); };
class BfmeRetBWF;
struct BfmeThingBWF { BfmeRetBWF *bfmeGoBWF(); };

class MapObject
{
public:
	MapObject *getNext() const { return m_nextMapObject; }
	const ThingTemplate *getThingTemplate() { return (const ThingTemplate *)((BfmeThing932A *)this)->bfmeGo932A(); }
	const Coord3D *getLocation() { return (const Coord3D *)((BfmeThingBWF *)this)->bfmeGoBWF(); }
	Real getAngle() const { return m_angle; }
	Dict *getProperties() { return &m_properties; }
private:
	void *m_vftable;
	MapObject *m_nextMapObject;
	Coord3D m_location;
	AsciiString m_objectName;
	void *m_thingTemplate;
	Real m_angle;
	Int m_flags;
	Dict m_properties;
};

class PolygonTrigger
{
public:
	PolygonTrigger *getNext() const { return m_nextPolygonTrigger; }
	Int getNumPoints() const { return m_numPoints; }
	ICoord3D *getPoint(Int ndx) const
	{
		if (ndx < 0) ndx = 0;
		if (ndx >= m_numPoints) ndx = m_numPoints - 1;
		return m_points + ndx;
	}
	Bool isWaterArea() const { return m_isWaterArea; }
private:
	void *m_vftable;
	PolygonTrigger *m_nextPolygonTrigger;
	char m_pad08[0x10 - 0x08];
	ICoord3D *m_points;
	Int m_numPoints;
	char m_pad18[0x32 - 0x18];
	Bool m_isWaterArea;
};

class Rva00199280Owner
{
public:
	void writeCastleTemplates(DataChunkOutput &chunkWriter, MapObject *firstObject,
		const AsciiString &fileName, PolygonTrigger *firstTrigger);
};

void Rva00199280Owner::writeCastleTemplates(DataChunkOutput &chunkWriter, MapObject *firstObject,
	const AsciiString &fileName, PolygonTrigger *firstTrigger)
{
	chunkWriter.openDataChunk("CastleTemplates", 2);

	if (!fileName.endsWithNoCase("bse"))
	{
		chunkWriter.writeNameKey(NAMEKEY("UNKNOWN"));
		chunkWriter.writeInt(0);
		return;
	}

	AsciiString templateName;
	for (Int i = 0; ; ++i)
	{
		char c = fileName.getCharAt(i);
		if (c == '.')
			break;
		templateName.concat(c);
	}
	chunkWriter.writeNameKey(NAMEKEY(templateName));

	Bool exists = false;
	Int numObjects = 0;
	Coord3D centerSum;
	centerSum.x = 0;
	centerSum.y = 0;
	centerSum.z = 0;
	Coord3D objectSum;
	objectSum.x = 0;
	objectSum.y = 0;
	objectSum.z = 0;
	Int numCenters = 0;
	AsciiString objectName("");
	std::list<MapObject *> objects;

	for (MapObject *obj = firstObject; obj; obj = obj->getNext())
	{
		const ThingTemplate *tmpl = obj->getThingTemplate();
		if (tmpl && (tmpl->getKindOfWord() & 0x40000))
		{
			const Coord3D *pos = obj->getLocation();
			centerSum.x += pos->x;
			centerSum.y += pos->y;
			centerSum.z += pos->z;
			++numCenters;
			continue;
		}
		Bool isBase = obj->getProperties()->getBool(TheKey_objectIsABase, &exists);
		if (exists && isBase)
			continue;
		AsciiString baseName = obj->getProperties()->getAsciiString(TheKey_objectBaseName, &exists);
		if (exists && baseName.isNotEmpty())
		{
			objects.push_back(obj);
			++numObjects;
			const Coord3D *pos = obj->getLocation();
			objectSum.x += pos->x;
			objectSum.y += pos->y;
			objectSum.z += pos->z;
		}
	}

	Coord3D center;
	if (numCenters == 0)
	{
		Real scale = 1.0f / numObjects;
		center.x = objectSum.x * scale;
		center.y = objectSum.y * scale;
		center.z = objectSum.z * scale;
	}
	else
	{
		Real scale = 1.0f / numCenters;
		center.x = centerSum.x * scale;
		center.y = centerSum.y * scale;
		center.z = centerSum.z * scale;
	}

	chunkWriter.writeInt(numObjects);
	if (numObjects > 0)
	{
		for (std::list<MapObject *>::iterator it = objects.begin(); it != objects.end(); ++it)
		{
			MapObject *obj = *it;
			if (!obj)
				return;
			objectName = obj->getProperties()->getAsciiString(TheKey_objectName, &exists);
			chunkWriter.writeAsciiString(exists ? objectName : Rva01336E50EmptyString);
			const ThingTemplate *tmpl = obj->getThingTemplate();
			chunkWriter.writeAsciiString(tmpl ? tmpl->getName() : Rva01336E50EmptyString);
			Coord3D pos = *obj->getLocation();
			pos.x -= center.x;
			pos.y -= center.y;
			pos.z -= center.z;
			chunkWriter.writeReal(pos.x);
			chunkWriter.writeReal(pos.y);
			chunkWriter.writeReal(pos.z);
			chunkWriter.writeReal(obj->getAngle());
		}
	}

	Int numTriggers = 0;
	PolygonTrigger *trig;
	for (trig = firstTrigger; trig; trig = trig->getNext())
	{
		if (!trig->isWaterArea())
			++numTriggers;
	}
	chunkWriter.writeInt(numTriggers);
	for (trig = firstTrigger; trig; trig = trig->getNext())
	{
		if (trig->isWaterArea())
			continue;
		Int numPoints = trig->getNumPoints();
		chunkWriter.writeInt(numPoints);
		for (Int j = 0; j < numPoints; ++j)
		{
			ICoord3D *pt = trig->getPoint(j);
			if (!pt)
				continue;
			ICoord3D loc = *pt;
			loc.x -= (Int)center.x;
			loc.y -= (Int)center.y;
			loc.z -= (Int)center.z;
			chunkWriter.writeInt(loc.x);
			chunkWriter.writeInt(loc.y);
			chunkWriter.writeInt(loc.z);
		}
	}

	chunkWriter.closeDataChunk();
}
