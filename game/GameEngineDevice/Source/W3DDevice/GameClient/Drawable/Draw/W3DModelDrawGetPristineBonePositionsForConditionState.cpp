// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?getPristineBonePositionsForConditionState@W3DModelDraw@@: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
//
// W3DModelDraw::getPristineBonePositionsForConditionState, retail 0x00775760
// (1036 bytes), BFME's seven-argument form.
//
// Identity: its ILT thunk 0x0000DC29 fills slot 3 of all seven W3DModelDraw
// family ObjectDrawInterface tables (e.g. 0x011223A0, which the matched
// W3DHordeModelDraw constructor 0x00751CF0 stores at +0x0C), between the matched
// W3DModelDraw getCurrentWorldspaceClientBonePositions (slot 2) and
// getCurrentBonePositions (slot 4); the matched Drawable caller (Drawable_getPristineBonePositions.cpp)
// dispatches the seven-argument pristine-bone query through that slot, and the
// body is Zero Hour's W3DModelDraw.cpp algorithm step for step. Retail returns
// with ret 0x1c: BFME added a seventh argument, an optional array that receives
// each found bone's index (zero for the missing bone).
//
// BFME changes read from the retail body: the bone lookup runs on a second
// state from the module data (0x00765DC0, address-derived name) instead of the
// best-info state; validateStuff takes that state and a drawable-owned bone
// list at Drawable+0x2F0 as two more arguments; tmpMtx is a function static.
// `this` is the ObjectDrawInterface subobject at W3DModelDraw+0x0C, as in the
// matched getCurrentBonePositions (m_renderObject at this+0x28) and the
// W3DHordeModelDraw constructor's interface-table store at +0x0C. That puts
// m_curState (the first member after the bases, as in Zero Hour) at +0x10;
// tools/bfme_layout.py's +0x14 witness for it conflicts with that store.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23
};

template <int N>
class BitFlags
{
	unsigned int value[4];
};

enum { MODELCONDITION_COUNT = 117 };
typedef BitFlags<MODELCONDITION_COUNT> ModelConditionFlags;

class Vector3
{
public:
	Real X, Y, Z;
	Vector3() {}
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
};

class Vector4
{
public:
	Real X, Y, Z, W;
	Vector4() {}
	Vector4(const Vector4 &other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}
	Vector4 &operator=(const Vector4 &other)
	{
		X = other.X; Y = other.Y; Z = other.Z; W = other.W;
		return *this;
	}
	void Set(Real x, Real y, Real z, Real w)
	{
		X = x; Y = y; Z = z; W = w;
	}
};

struct Coord3D
{
	Real x, y, z;
};

class Matrix3D
{
public:
	Matrix3D();											///< 0x000458EF
	Matrix3D &operator=(const Matrix3D &other)
	{
		Row[0] = other.Row[0];
		Row[1] = other.Row[1];
		Row[2] = other.Row[2];
		return *this;
	}

	Vector3 Get_Translation() const
	{
		return Vector3(Row[0].W, Row[1].W, Row[2].W);
	}

	void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	Vector4 Row[3];
};

class RenderObjClass;
class Object
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	UnsignedByte m_unmodelled00[0x8];
	Matrix3D m_transform;
};

class AsciiString;
struct Rva00774AA0DrawableBones;

class Drawable
{
public:
	Real getScale() const;
	const Object *getObject() const { return m_object; }

	UnsignedByte m_unmodelled000[0xfc];
	Object *m_object;									///< +0xFC
	UnsignedByte m_unmodelled100[0x1f0];
	const Rva00774AA0DrawableBones *m_rva2F0Bones;		///< +0x2F0
};

struct PristineBoneInfo
{
	Matrix3D mtx;
	Int boneIndex;
};
typedef _STL::map<NameKeyType, PristineBoneInfo> PristineBoneInfoMap;

enum { PRISTINE_BONES_VALID = 0x00000001 };

struct ModelConditionInfo
{
	UnsignedByte m_unmodelled00[0x70];
	PristineBoneInfoMap m_pristineBones;				///< +0x70
	UnsignedByte m_unmodelled7C[0x30];
	UnsignedByte m_validStuff;							///< +0xAC

	// 0x00774AA0 through ILT 0x00006E92
	void validateStuff(RenderObjClass *robj, Real scale,
		const _STL::vector<AsciiString> &extraPublicBones,
		const ModelConditionInfo *boneState,
		const Rva00774AA0DrawableBones &drawableBones) const;

	const Matrix3D *findPristineBone(NameKeyType boneName, Int *boneIndex) const
	{
		if (!(m_validStuff & PRISTINE_BONES_VALID))
		{
			if (boneIndex)
				*boneIndex = 0;
			return NULL;
		}
		if (boneName == NAMEKEY_INVALID)
		{
			if (boneIndex)
				*boneIndex = 0;
			return NULL;
		}
		PristineBoneInfoMap::const_iterator it = m_pristineBones.find(boneName);
		if (it != m_pristineBones.end())
		{
			if (boneIndex)
				*boneIndex = it->second.boneIndex;
			return &it->second.mtx;
		}
		else
		{
			if (boneIndex)
				*boneIndex = 0;
			return NULL;
		}
	}
};

class W3DModelDrawModuleData
{
public:
	// 0x00765B70 through ILT 0x00005024
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const;
	// 0x00765DC0 through ILT 0x0000CE5F: BFME-only, the state whose pristine
	// bones this query reads.
	const ModelConditionInfo *rva00765DC0(const ModelConditionFlags &c) const;

	UnsignedByte m_unmodelled00[0x30];
	_STL::vector<AsciiString> m_extraPublicBones;		///< +0x30
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class DrawModule
{
public:
	virtual void drawModuleSlot00();
	const W3DModelDrawModuleData *getModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }

	const W3DModelDrawModuleData *m_moduleData;		///< +0x04
	Drawable *m_drawable;								///< +0x08
};

class ObjectDrawInterface
{
public:
	virtual void objectDrawSlot00() const = 0;
	virtual void objectDrawSlot01() const = 0;
	virtual void objectDrawSlot02() const = 0;
	virtual Int getPristineBonePositionsForConditionState(const ModelConditionFlags &condition,
		const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *boneIndices) const = 0;
};

class W3DModelDraw : public DrawModule, public ObjectDrawInterface
{
public:
	virtual void objectDrawSlot00() const;
	virtual void objectDrawSlot01() const;
	virtual void objectDrawSlot02() const;
	virtual Int getPristineBonePositionsForConditionState(const ModelConditionFlags &condition,
		const char *boneNamePrefix, Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *boneIndices) const;

	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return getModuleData(); }
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const
	{
		return getW3DModelDrawModuleData()->findBestInfo(c);
	}

	const ModelConditionInfo *m_curState;				///< +0x10
	UnsignedByte m_unmodelled14[0x20];
	RenderObjClass *m_renderObject;						///< +0x34
};

Int W3DModelDraw::getPristineBonePositionsForConditionState(
	const ModelConditionFlags &condition,
	const char *boneNamePrefix,
	Int startIndex,
	Coord3D *positions,
	Matrix3D *transforms,
	Int maxBones,
	Int *boneIndices
) const
{
	const W3DModelDrawModuleData *d = getW3DModelDrawModuleData();
	const ModelConditionInfo *stateToUse = d->findBestInfo(condition);
	if (!stateToUse)
		return 0;

	const ModelConditionInfo *boneState = d->rva00765DC0(condition);
	RenderObjClass *robj = stateToUse == m_curState ? m_renderObject : NULL;
	const Rva00774AA0DrawableBones *drawBones = getDrawable()->m_rva2F0Bones;
	stateToUse->validateStuff(
		robj,
		getDrawable()->getScale(),
		d->m_extraPublicBones,
		boneState,
		*drawBones);

	const int MAX_BONE_GET = 64;
	static Matrix3D tmpMtx[MAX_BONE_GET];

	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;

	if (transforms == NULL)
		transforms = tmpMtx;

	Int posCount = 0;
	Int endIndex = (startIndex == 0) ? 0 : 99;
	char buffer[256];
	Int i;
	for (i = startIndex; i <= endIndex; ++i)
	{
		if (i == 0)
			strcpy(buffer, boneNamePrefix);
		else
			sprintf(buffer, "%s%02d", boneNamePrefix, i);

		for (char *c = buffer; c && *c; ++c)
		{
			*c = tolower(*c);
		}

		const Matrix3D *mtx = boneState->findPristineBone(NAMEKEY(buffer), NULL);
		if (mtx)
		{
			transforms[posCount] = *mtx;
			if (boneIndices)
				boneIndices[posCount] = i;
		}
		else
		{
			if (boneIndices)
				boneIndices[posCount] = 0;
			const Object *obj = getDrawable()->getObject();
			if (obj)
				transforms[posCount] = *obj->getTransformMatrix();
			else
				transforms[posCount].Make_Identity();
			break;
		}

		++posCount;
		if (posCount >= maxBones)
			break;
	}

	if (positions && transforms)
	{
		for (i = 0; i < posCount; ++i)
		{
			Vector3 pos = transforms[i].Get_Translation();
			positions[i].x = pos.X;
			positions[i].y = pos.Y;
			positions[i].z = pos.Z;
		}
	}

	return posCount;
}
