// cl: /DNDEBUG /MD /EHsc

class MeshMatDescClass
{
public:
	virtual ~MeshMatDescClass();
};

__declspec(noinline) MeshMatDescClass::~MeshMatDescClass() {}

void Force_MeshMatDesc_Deleting_Destructor(MeshMatDescClass *material)
{
	delete material;
}
