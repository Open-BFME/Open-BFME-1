// cl: /DNDEBUG /MD /EHsc

// Two gaps in Vector3SolidSphereRandomizer's vtable, whose other four slots are
// named. v3_rnd.h declares the base's virtuals as destructor, Class_ID,
// Get_Vector, Get_Maximum_Extent, Scale, Clone -- so the unclaimed slot between
// the destructor and Get_Vector is Class_ID, and the one between Get_Vector and
// Scale is Get_Maximum_Extent.
//
// The bodies agree with the declared return types independently of position:
// Class_ID returns a constant unsigned int, and Get_Maximum_Extent loads a float
// from the member at +4 onto the x87 stack, which is how a float return leaves a
// function here.
class Vector3;
class Vector3Randomizer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/v3_rnd.h
class Vector3SolidSphereRandomizer
{
public:
	virtual ~Vector3SolidSphereRandomizer();
	virtual unsigned int Class_ID(void) const;
	virtual void Get_Vector(Vector3 &vector);
	virtual float Get_Maximum_Extent(void);
	virtual void Scale(float scale);
	virtual Vector3Randomizer *Clone(void) const;

	float m_Radius;
};

// ?Class_ID@Vector3SolidSphereRandomizer@@UBEIXZ
unsigned int Vector3SolidSphereRandomizer::Class_ID(void) const
{
	return 1;
}

// ?Get_Maximum_Extent@Vector3SolidSphereRandomizer@@UAEMXZ
float Vector3SolidSphereRandomizer::Get_Maximum_Extent(void)
{
	return m_Radius;
}
