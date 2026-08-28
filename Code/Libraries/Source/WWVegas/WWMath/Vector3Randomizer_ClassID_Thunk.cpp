// cl: /DNDEBUG /MD /EHsc

// Class_ID for two more Vector3Randomizer subclasses. Each sits in its own
// vtable in the slot between the destructor and Get_Vector, which is where
// v3_rnd.h declares it, and each body is a constant unsigned int -- the same
// shape as Vector3SolidSphereRandomizer::Class_ID, which returns 1. The three
// identifiers run 1, 2, 3 in the order the subclasses appear.
class Vector3;
class Vector3Randomizer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/v3_rnd.h
class Vector3HollowSphereRandomizer
{
public:
	virtual ~Vector3HollowSphereRandomizer();
	virtual unsigned int Class_ID(void) const;
	virtual void Get_Vector(Vector3 &vector);
	virtual float Get_Maximum_Extent(void);
	virtual void Scale(float scale);
	virtual Vector3Randomizer *Clone(void) const;

	float m_Radius;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/v3_rnd.h
class Vector3SolidCylinderRandomizer
{
public:
	virtual ~Vector3SolidCylinderRandomizer();
	virtual unsigned int Class_ID(void) const;
	virtual void Get_Vector(Vector3 &vector);
	virtual float Get_Maximum_Extent(void);
	virtual void Scale(float scale);
	virtual Vector3Randomizer *Clone(void) const;

	float m_Radius;
	float m_Height;
};

// ?Class_ID@Vector3HollowSphereRandomizer@@UBEIXZ
unsigned int Vector3HollowSphereRandomizer::Class_ID(void) const
{
	return 2;
}

// ?Class_ID@Vector3SolidCylinderRandomizer@@UBEIXZ
unsigned int Vector3SolidCylinderRandomizer::Class_ID(void) const
{
	return 3;
}
