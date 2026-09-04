// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXListAtBonePosFXNugget::doFxAtBones, retail 0x0042D8E0, 356B.
// Layout matches the landed ctor thunk: m_fx at +0xB4, m_boneName at +0xB8.
// BFME uses getPristineBonePositions (not ZH getCurrentClientBonePositions)
// and skips an empty FXList before the four-arg doFXPos.

enum { MAX_BONE_POINTS = 40 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
// Out-of-line empty ctor/dtor so the 40-element stack array goes through
// __ehvec_ctor / __ehvec_dtor (size 0x0C, count 0x28). The world-space
// output slot is a POD so the loop does not emit a per-iteration ctor.
struct Coord3D
{
	Coord3D();
	~Coord3D();
	float x;
	float y;
	float z;
};

Coord3D::Coord3D()
{
}

Coord3D::~Coord3D()
{
}

struct WorldPos
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/matrix3d.h
// One implicit Matrix3D ctor is ??_H over three 16-byte rows. Trivial dtor so
// the 40-element array is a counted ??_H loop, not ehvec.
class Vector4
{
public:
	// Declared, not defined: an empty body in this TU inlines to nothing and
	// drops the 40-iteration ??_H row-ctor loop retail emits for Matrix3D[40].
	Vector4();

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
	Vector4 Row[3];
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? (const char *)(m_data + 1) : "";
	}

private:
	BfmeAsciiStringData *m_data;
};

class FXList
{
public:
	bool isEmpty() const;
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const;
};

class Drawable
{
public:
	int getPristineBonePositions(const char *boneNamePrefix, int startIndex,
		Coord3D *positions, Matrix3D *transforms, int maxBones) const;
};

class Object
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual Drawable *getDrawable() const;
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class FXListAtBonePosDoFxAtBonesShim : public FXNugget
{
public:
	void run(const Object *obj, int start) const;

private:
	const FXList *m_fx;
	AsciiString m_boneName;
};

// ?run@FXListAtBonePosDoFxAtBonesShim@@QBEXPBVObject@@H@Z
void FXListAtBonePosDoFxAtBonesShim::run(const Object *obj, int start) const
{
	const Object *object = obj;
	Coord3D bonePos[MAX_BONE_POINTS];
	Matrix3D boneMtx[MAX_BONE_POINTS];

	Drawable *draw = object->getDrawable();
	if (draw)
	{
		int count = draw->getPristineBonePositions(m_boneName.str(), start, bonePos, boneMtx, MAX_BONE_POINTS);
		for (int i = 0; i < count; ++i)
		{
			WorldPos p;
			Matrix3D worldMtx[1];
			object->convertBonePosToWorldPos(&bonePos[i], &boneMtx[i],
				reinterpret_cast<Coord3D *>(&p), worldMtx);
			const FXList *fx = m_fx;
			if (fx && !fx->isEmpty())
				fx->doFXPos(reinterpret_cast<const Coord3D *>(&p), worldMtx, 0.0f, 0);
		}
	}
}
