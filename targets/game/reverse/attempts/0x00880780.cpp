// ?d_00880780@@YAXXZ
// partial score=0.39 date=2026-09-23
// cl: /O2 /GR- /EHsc- /G6 /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: address-derived GeometryOther callback, retail 0x00880780.

#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0
};

extern "C" const char *const GeometryNames[];
extern "C" int __cdecl strncmp(const char *, const char *, unsigned int);
#pragma intrinsic(strncmp)

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators);
	static int scanIndexList(const char *token, const char *const *names);
	static bool scanBool(const char *token);
	static Real scanReal(const char *token);
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_centerOffset;
	AsciiString m_name;
	Bool m_enabled;
	char m_padding[3];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

template <class T>
struct VectorStorage
{
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

typedef std::vector<GeometryShape> GeometryShapeVector;
typedef std::vector<GeometryRecord> GeometryRecordVector;

class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	void calcBoundingStuff() throw();

	void *m_snapshotVTable;
	Bool m_isSmall;

private:
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;

public:
	VectorStorage<GeometryShape> m_shapes;
	VectorStorage<GeometryRecord> m_records;

private:
	int m_cached44;
	int m_cached48;
	Real m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

struct BfmeFalse2E
{
};

struct BfmeElem2E
{
	char m_data[0x5C];
	void copyFrom(const BfmeElem2E *source);
};

class BfmeVec2E
{
public:
	void overflow(BfmeElem2E *position, const BfmeElem2E &value,
		const BfmeFalse2E &, unsigned int fill, bool atEnd);
	BfmeElem2E *m_start;
	BfmeElem2E *m_finish;
	BfmeElem2E *m_endOfStorage;
};

class Rva00880780
{
public:
	static void parseGeometryOther(INI *ini, void *instance, void *store,
		const void *userData);
};

void Rva00880780::parseGeometryOther(INI *ini, void *, void *store, const void *)
{
	GeometryInfo geometry(GEOMETRY_SPHERE, false, 10.0f, 10.0f, 10.0f);
	const char *separators = *(const char **)((char *)ini + 0x41C);
	const char *key = ini->getNextTokenOrNull(separators);
	if (key != 0)
	{
		GeometryShape *shape = geometry.m_shapes.m_start;
		do
		{
			const char *value = ini->getNextTokenOrNull(separators);
			if (value == 0)
				break;
			if (strncmp(key, "GeomType", 9) == 0)
			{
				shape->m_type = INI::scanIndexList(value, GeometryNames);
			}
			else if (strncmp(key, "IsSmall", 8) == 0)
			{
				geometry.m_isSmall = INI::scanBool(value);
			}
			else if (strncmp(key, "Height", 7) == 0)
			{
				shape->m_height = INI::scanReal(value);
			}
			else if (strncmp(key, "MajorRadius", 12) == 0)
			{
				shape->m_majorRadius = INI::scanReal(value);
			}
			else if (strncmp(key, "MinorRadius", 12) == 0)
			{
				shape->m_minorRadius = INI::scanReal(value);
			}
			else if (strncmp(key, "OffsetX", 8) == 0)
			{
				shape->m_centerOffset.x = INI::scanReal(value);
			}
			else if (strncmp(key, "OffsetY", 8) == 0)
			{
				shape->m_centerOffset.y = INI::scanReal(value);
			}
			else if (strncmp(key, "OffsetZ", 8) == 0)
			{
				shape->m_centerOffset.z = INI::scanReal(value);
			}
			key = ini->getNextTokenOrNull(separators);
		} while (key != 0);
	}
	geometry.calcBoundingStuff();
	BfmeVec2E *output = (BfmeVec2E *)store;
	BfmeElem2E *finish = output->m_finish;
	if (finish != output->m_endOfStorage)
	{
		if (finish != 0)
			finish->copyFrom((const BfmeElem2E *)&geometry);
		++output->m_finish;
	}
	else
	{
		output->overflow(finish, (const BfmeElem2E &)geometry,
			reinterpret_cast<const BfmeFalse2E &>(ini), 1, true);
	}
	((GeometryRecordVector *)&geometry.m_records)->~GeometryRecordVector();
	((GeometryShapeVector *)&geometry.m_shapes)->~GeometryShapeVector();
}
