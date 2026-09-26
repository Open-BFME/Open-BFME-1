// ?rva00720D10@W3DShrubBuffer@@QAEXIUCoord3D@@MPBVMatrix3D@@MPBURva00720D10Data@@HABVAsciiString@@3@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// RVA 0x00720D10 is the BFME shrub append body, witnessed by its W3DShrubBuffer.cpp
// literal, addTreeType callee, and the named terrain receiver at +0x3098.
// The public BFME method spelling is unknown; retain the address-derived name.
// Keeping the exact getPartitionBucket body visible proves that location does
// not escape, which restores retail's X/Z/Y integer copies into the tree record.

#include "ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

struct Coord3D
{
	float x, y, z;
};

struct Rva00720D10GlobalData
{
	unsigned char m_pad00[0x18];
	bool m_flag18;
};

extern Rva00720D10GlobalData *TheGlobalData;

struct Rva00720D10Data
{
	unsigned char prefix[8];
	AsciiString modelName, nameC;
	unsigned int framesToMoveOutward;
	unsigned char gap14[0x3d - 0x14];
	bool doTopple;
	unsigned char gap3e[0x48 - 0x3e];
	AsciiString name48;
	unsigned char gap4c[8];
	bool flag54;
};

struct Rva00720D10Type
{
	void *mesh;
	Vector3 offset;
	SphereClass bounds;
	const Rva00720D10Data *data;
	unsigned char gap24[0x58 - 0x24];
	int field58;
};

struct Rva00720D10Tree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	bool flag45;
	bool flag46;
	unsigned char alignment47;
	SphereClass bounds;
	float sortKey;
	unsigned int drawableID;
	float pushAside;
	float pushAsideDelta;
	float pushAsideSin;
	float pushAsideCos;
	unsigned int pushAsideSource;
	unsigned int lastFrame;
	int nextInPartition;
	int swayType;
	int firstIndex;
	int bufferIndex;
	int toppleState;
	int uprightType;
	int toppledType;
	unsigned int sinkFrames;
	void *toppleObject;
	void *pushAsideObject;
	int fielda0;
};

extern float GetGameClientRandomValueReal(float, float, char *, int);
extern int GetGameClientRandomValue(int, int, char *, int);

static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
	// Preserve the observed x87 load order for this alias-sensitive aggregate update.
	const volatile float &x = position.X;
	center.X += x;
	center.Y = position.Y + center.Y;
	center.Z = position.Z + center.Z;
}

class W3DShrubBuffer
{
public:
	int addTreeType(const AsciiString &, const AsciiString &, const void *, int, const AsciiString &, const AsciiString &);
	int rva007209F0(const AsciiString &, int, const AsciiString &);
	void rva00720D10(unsigned int id, Coord3D location, float scale, const Matrix3D *transform, float randomScaleAmount,
		const Rva00720D10Data *data, int shadowKind, const AsciiString &textureName, const AsciiString &nameD);

protected:
	int getPartitionBucket(const Coord3D &location) const;

private:
	unsigned char prefix[0xb8];
	short areaPartition[(0x1548 - 0xb8) / 2];
	Rva00720D10Tree trees[12000];
	int numTrees;
	unsigned char gapcc[2];
	bool changed, initialized;
	unsigned char gapd0;
	bool needUpdate;
	unsigned char gapd2[2];
	Rva00720D10Type types[64];
	int numTypes;
};

extern "C" __declspec(dllimport) double __cdecl floor(double);
// Original BaseType.h helper, used by the already matched partition lookup.
// A C++ cast calls __ftol2; retail uses the two-instruction x87 conversion.
__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

// ?getPartitionBucket@W3DShrubBuffer@@IBEHABUCoord3D@@@Z
// The 50-by-50 partition places its bounds at +0x1440, as witnessed in retail.
// This exact definition must precede the append body: VC7.1 then knows that
// passing location by reference does not let the callee retain or change it.
__declspec(noinline) int W3DShrubBuffer::getPartitionBucket(const Coord3D &pos) const
{
	const float *bounds = (const float *)((const char *)this + 0x1440);
	float x = pos.x;
	float y = pos.y;
	if (x < bounds[0]) x = bounds[0];
	if (y < bounds[1]) y = bounds[1];
	if (x > bounds[2]) x = bounds[2];
	if (y > bounds[3]) y = bounds[3];
	float xRatio = x / (bounds[2] - bounds[0]) * 49.9f;
	int xIndex = fast_float2long_round((float)floor((double)xRatio));
	float yRatio = y / (bounds[3] - bounds[1]) * 49.9f;
	int yIndex = fast_float2long_round((float)floor((double)yRatio));
	return yIndex * 50 + xIndex;
}

// ?rva00720D10@W3DShrubBuffer@@QAEXIUCoord3D@@MPBVMatrix3D@@MPBURva00720D10Data@@HABVAsciiString@@3@Z
void W3DShrubBuffer::rva00720D10(unsigned int id, Coord3D location, float scale, const Matrix3D *transform,
	float randomScaleAmount, const Rva00720D10Data *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD)
{
	if (!TheGlobalData->m_flag18) return;
	if (numTrees >= 12000) return;
	if (!initialized) return;
	int type = -2;
	for (int i = 0; i < numTypes; ++i) {
		if (((const StringBase<char> *)&types[i].data->modelName)->compareNoCase(*(const StringBase<char> *)&data->modelName) == 0 &&
			((const StringBase<char> *)&types[i].data->nameC)->compareNoCase(*(const StringBase<char> *)&data->nameC) == 0) { type = i; break; }
	}
	if (type < 0) {
		type = addTreeType(data->modelName, data->nameC, data, shadowKind, textureName, nameD);
		if (type < 0) return;
		needUpdate = true;
	}
	types[type].field58 = rva007209F0(data->name48, shadowKind, textureName);
	if (data->framesToMoveOutward > 0 || data->doTopple) {
		short bucket = getPartitionBucket(location);
		trees[numTrees].nextInPartition = areaPartition[bucket];
		areaPartition[bucket] = numTrees;
	} else {
		trees[numTrees].nextInPartition = -1;
	}
	float randomScale = GetGameClientRandomValueReal(1.0f - randomScaleAmount, 1.0f + randomScaleAmount,
		"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x527);
	trees[numTrees].transform = *transform;
	if (randomScaleAmount > 0.0f) trees[numTrees].scale = scale * randomScale;
	else trees[numTrees].scale = scale;
	trees[numTrees].location = (const Vector3 &)location;
	trees[numTrees].treeType = type;
	trees[numTrees].uprightType = type;
	trees[numTrees].toppledType = types[type].field58;
	trees[numTrees].fielda0 = 1;
	trees[numTrees].bounds = types[type].bounds;
	trees[numTrees].bounds.Center *= trees[numTrees].scale;
	trees[numTrees].bounds.Radius *= trees[numTrees].scale;
	translateBounds(trees[numTrees].bounds.Center, trees[numTrees].location);
	trees[numTrees].visible = false;
	trees[numTrees].drawableID = id;
	trees[numTrees].firstIndex = 0;
	trees[numTrees].bufferIndex = -1;
	trees[numTrees].swayType = data->flag54 ? 0 : GetGameClientRandomValue(1, 9,
		"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x542);
	trees[numTrees].pushAside = 0;
	trees[numTrees].lastFrame = 0;
	trees[numTrees].pushAsideSource = 0;
	trees[numTrees].pushAsideDelta = 0;
	trees[numTrees].pushAsideCos = 1;
	trees[numTrees].pushAsideSin = 1;
	trees[numTrees].toppleState = 0;
	trees[numTrees].toppleObject = 0;
	trees[numTrees].pushAsideObject = 0;
	trees[numTrees].flag45 = false;
	trees[numTrees].flag46 = false;
	trees[numTrees].sortKey = 0;
	trees[numTrees].sinkFrames = 0;
	++numTrees;
	changed = true;
}
