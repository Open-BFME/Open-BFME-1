// cl: /DNDEBUG /MD /EHsc

class DX8SkinFVFCategoryContainer
{
public:
	virtual ~DX8SkinFVFCategoryContainer();
};

__declspec(noinline) DX8SkinFVFCategoryContainer::~DX8SkinFVFCategoryContainer() {}

void Force_DX8SkinFVFCategoryContainer_Deleting_Destructor(DX8SkinFVFCategoryContainer *container)
{
	delete container;
}
