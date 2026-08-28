// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
	int m_data[12];
};

class Thing
{
public:
	void convertBonePosToWorldPos(const Coord3D *bonePos, const Matrix3D *boneTransform,
		Coord3D *worldPos, Matrix3D *worldTransform) const;
};

class Drawable : public Thing
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

class Object
{
public:
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones,
		Coord3D *positions, Matrix3D *transforms, Bool convertToWorld, Int extra) const;

private:
	unsigned char m_unmodelled_000[0x80];
	Drawable *m_drawable;
};

Int Object::getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones,
	Coord3D *positions, Matrix3D *transforms, Bool convertToWorld, Int extra) const
{
	Int count;
	if (m_drawable != 0 &&
		(count = m_drawable->getPristineBonePositions(
			boneNamePrefix, 1, positions, transforms, maxBones, extra)) > 0)
	{
		if (convertToWorld)
		{
			for (Int i = 0; i < count; ++i)
			{
				m_drawable->convertBonePosToWorldPos(
					positions ? &positions[i] : 0,
					transforms ? &transforms[i] : 0,
					positions ? &positions[i] : 0,
					transforms ? &transforms[i] : 0);
			}
		}
		return count;
	}
	return 0;
}
