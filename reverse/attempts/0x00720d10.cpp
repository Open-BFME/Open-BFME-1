// ?rva00720D10@W3DShrubBuffer@@QAEXIUCoord3D@@MPBVMatrix3D@@MPBURva00720D10Data@@HABVAsciiString@@3@Z
// partial score=0.97 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringinline
// Near miss (1308 of 1312 B): only the location store differs. Retail copies X, Z, then Y through a lea base;
// this operator= copies X, Y, Z, and Vector3(x, y, z) goes through the FPU once getPartitionBucket takes &location.

#include "StringInline.h"
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
	center.X = position.X + center.X;
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
		if (types[i].data->modelName.compareNoCase(data->modelName) == 0 &&
			types[i].data->nameC.compareNoCase(data->nameC) == 0) { type = i; break; }
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
