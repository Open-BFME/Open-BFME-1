// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8RigidFVFCategoryContainer
{
public:
	virtual ~DX8RigidFVFCategoryContainer();
};

__declspec(noinline) DX8RigidFVFCategoryContainer::~DX8RigidFVFCategoryContainer() {}

void Force_DX8RigidFVFCategoryContainer_Deleting_Destructor(DX8RigidFVFCategoryContainer *container)
{
	delete container;
}
