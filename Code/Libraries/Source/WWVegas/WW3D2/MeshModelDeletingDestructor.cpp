// cl: /DNDEBUG /MD /EHsc

class MeshModelClass
{
public:
	virtual ~MeshModelClass();
};

__declspec(noinline) MeshModelClass::~MeshModelClass() {}

void Force_MeshModel_Deleting_Destructor(MeshModelClass *model)
{
	delete model;
}
