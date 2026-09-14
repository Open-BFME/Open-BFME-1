// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: scalar-deleting destructors for the four concrete Vector3
// randomizers.  Their contiguous vtables at 0x011BC4B4..0x011BC508 name every
// class through the already-matched Get_Vector, Scale, and Clone slots; the
// matched constructors at 0x00B02150/0x00B02250/0x00B02350/0x00B02480 install
// those same tables.

class Vector3SolidBoxRandomizer
{
public:
	virtual ~Vector3SolidBoxRandomizer();
};

class Vector3SolidSphereRandomizer
{
public:
	virtual ~Vector3SolidSphereRandomizer();
};

class Vector3HollowSphereRandomizer
{
public:
	virtual ~Vector3HollowSphereRandomizer();
};

class Vector3SolidCylinderRandomizer
{
public:
	virtual ~Vector3SolidCylinderRandomizer();
};

__declspec(noinline) Vector3SolidBoxRandomizer::~Vector3SolidBoxRandomizer() {}
__declspec(noinline) Vector3SolidSphereRandomizer::~Vector3SolidSphereRandomizer() {}
__declspec(noinline) Vector3HollowSphereRandomizer::~Vector3HollowSphereRandomizer() {}
__declspec(noinline) Vector3SolidCylinderRandomizer::~Vector3SolidCylinderRandomizer() {}

void forceVector3RandomizerDeletingDestructors()
{
	Vector3SolidBoxRandomizer box;
	Vector3SolidSphereRandomizer solidSphere;
	Vector3HollowSphereRandomizer hollowSphere;
	Vector3SolidCylinderRandomizer cylinder;
}
