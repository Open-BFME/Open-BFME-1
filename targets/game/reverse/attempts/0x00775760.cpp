// ?getPristineBonePositionsForConditionState@Rva00775760@@QBEHABV?$BitFlags@$0HF@@@PBDHPAUCoord3D@@PAVMatrix3D@@HPAH@Z
// partial score=0.981 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath

#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef int Int;
typedef float Real;
typedef int NameKeyType;

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
	Matrix3D() {}
	Vector4 Row[3];
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
};

struct RvaVector
{
	void *begin;
	void *end;
	void *capacity;
};

struct RvaPristineNode
{
	unsigned char color[4];
	RvaPristineNode *parent;
	RvaPristineNode *left;
	RvaPristineNode *right;
	NameKeyType key;
	Matrix3D matrix;
};

struct RvaPristineMap
{
	RvaPristineNode *head;
	RvaPristineNode *begin;
	RvaPristineNode *end;
	unsigned char padding[8];
};

struct RvaModelConditionInfo
{
	unsigned char prefix[0x70];
	RvaPristineMap pristineBones;
	unsigned char middle[0x28];
	unsigned char validStuff;

	void validateStuff(void *renderObject, Real scale, const RvaVector &moduleBones,
		const RvaModelConditionInfo *conditionInfo, const RvaVector &drawableBones) const;
};

class RvaModuleData
{
public:
	unsigned char prefix[0x30];
	RvaVector extraPublicBones;

	const RvaModelConditionInfo *findBestInfo(const ModelConditionFlags &condition) const;
	const RvaModelConditionInfo *findByCondition(const ModelConditionFlags &condition) const;
};

class Object
{
public:
	const Matrix3D *getTransformMatrix() const
	{
		return reinterpret_cast<const Matrix3D *>(reinterpret_cast<const char *>(this) + 8);
	}
};

class Drawable
{
public:
	Real getScale() const;
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this) + 0xfc);
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00775760
{
public:
	Int getPristineBonePositionsForConditionState(
		const ModelConditionFlags &condition, const char *boneNamePrefix,
		Int startIndex, Coord3D *positions, Matrix3D *transforms,
		Int maxBones, Int *extra) const;
};

Int Rva00775760::getPristineBonePositionsForConditionState(
	const ModelConditionFlags &condition, const char *boneNamePrefix,
	Int startIndex, Coord3D *positions, Matrix3D *transforms,
	Int maxBones, Int *extra) const
{
	RvaModuleData *module = *reinterpret_cast<RvaModuleData *const *>(
		reinterpret_cast<const char *>(this) - 8);
	const char *volatile savedThis = reinterpret_cast<const char *>(this);
	const RvaModelConditionInfo *stateToUse = module->findBestInfo(condition);
	if (stateToUse == NULL)
		return 0;

	const RvaModelConditionInfo *boneState = module->findByCondition(condition);
	register const char *savedThisForCompare = savedThis;
	void *renderObject = stateToUse == *reinterpret_cast<const RvaModelConditionInfo *const *>(
		savedThisForCompare + 4) ? *reinterpret_cast<void *const *>(savedThisForCompare + 0x28) : NULL;

	Drawable *draw = *reinterpret_cast<Drawable *const *>(
		savedThisForCompare - 4);
	const RvaVector *drawableBones = *reinterpret_cast<const RvaVector *const *>(
		reinterpret_cast<const char *>(draw) + 0x2f0);
	stateToUse->validateStuff(renderObject, draw->getScale(), module->extraPublicBones,
		boneState, *drawableBones);

	const Int MAX_BONE_GET = 64;
	static Matrix3D tmpMtx[MAX_BONE_GET];
	if (maxBones > MAX_BONE_GET)
		maxBones = MAX_BONE_GET;
	if (transforms == NULL)
		transforms = tmpMtx;

	Int posCount = 0;
	Int endIndex = (startIndex == 0) ? 0 : 99;
	char buffer[256];
	for (Int i = startIndex; i <= endIndex; ++i)
	{
		if (i == 0)
			strcpy(buffer, boneNamePrefix);
		else
			sprintf(buffer, "%s%02d", boneNamePrefix, i);

		for (char *c = buffer; c && *c; ++c)
			*c = tolower(*c);

		NameKeyType key = TheNameKeyGenerator->nameToKey(buffer);
		const Matrix3D *mtx = NULL;
		if ((boneState->validStuff & 1) && key)
		{
			RvaPristineNode *head = boneState->pristineBones.head;
			RvaPristineNode *node = head->parent;
			RvaPristineNode *found = head;
			while (node)
			{
				if (node->key >= key)
				{
					found = node;
					node = node->left;
				}
				else
					node = node->right;
			}
			if (found != boneState->pristineBones.head)
			{
				mtx = &found->matrix;
				if (key < found->key)
					mtx = NULL;
			}
		}

		if (mtx)
		{
			transforms[posCount] = *mtx;
			if (extra)
				extra[posCount] = i;
		}
		else
		{
			if (extra)
				extra[posCount] = 0;
			const char *savedDraw = *reinterpret_cast<const char *const *>(savedThisForCompare - 4);
			const Object *obj = *reinterpret_cast<Object *const *>(savedDraw + 0xfc);
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
		for (Int i = 0; i < posCount; ++i)
		{
			Vector3 pos = transforms[i].Get_Translation();
			positions[i].x = pos.X;
			positions[i].y = pos.Y;
			positions[i].z = pos.Z;
		}
	}

	return posCount;
}
