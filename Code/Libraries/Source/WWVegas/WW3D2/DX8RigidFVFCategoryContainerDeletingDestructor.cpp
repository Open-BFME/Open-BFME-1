// cl: /DNDEBUG /MD /EHsc

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
