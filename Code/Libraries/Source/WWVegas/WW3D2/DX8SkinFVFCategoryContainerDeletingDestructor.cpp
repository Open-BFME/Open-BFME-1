// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
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
