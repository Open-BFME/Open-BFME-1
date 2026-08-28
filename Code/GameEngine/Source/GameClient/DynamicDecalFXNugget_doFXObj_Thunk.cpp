// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of DynamicDecal's object dispatch.

struct Coord3D
{
	float x, y, z;
};

class Matrix3D
{
private:
	float m_values[12];
};

class Object
{
public:
	unsigned char m_unmodelled[8];
	Matrix3D m_transform;
	Coord3D m_position;
};

class DynamicDecalFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float,
		const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;
};

// ?doFXObj@DynamicDecalFXNugget@@UBEXPBVObject@@0@Z
void DynamicDecalFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
		doFXPos(&primary->m_position, &primary->m_transform, 0.0f, 0);
}
