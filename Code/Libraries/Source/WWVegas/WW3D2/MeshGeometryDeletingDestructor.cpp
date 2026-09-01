// cl: /DNDEBUG /MD /EHsc

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
