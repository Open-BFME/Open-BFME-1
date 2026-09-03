// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
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
