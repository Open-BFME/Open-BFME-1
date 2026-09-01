// cl: /DNDEBUG /MD /EHsc

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
