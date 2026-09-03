// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
	virtual ~MeshClass();
};

__declspec(noinline) MeshClass::~MeshClass() {}

void Force_MeshClass_Deleting_Destructor(MeshClass *mesh)
{
	delete mesh;
}
