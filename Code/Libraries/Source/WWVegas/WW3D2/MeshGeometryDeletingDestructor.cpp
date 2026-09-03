// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
public:
	virtual ~MeshGeometryClass();
};

__declspec(noinline) MeshGeometryClass::~MeshGeometryClass() {}

void Force_MeshGeometry_Deleting_Destructor(MeshGeometryClass *geometry)
{
	delete geometry;
}
