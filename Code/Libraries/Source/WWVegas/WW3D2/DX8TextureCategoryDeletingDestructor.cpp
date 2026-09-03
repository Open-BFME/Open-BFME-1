// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8TextureCategoryClass
{
public:
	virtual ~DX8TextureCategoryClass();
};

__declspec(noinline) DX8TextureCategoryClass::~DX8TextureCategoryClass() {}

void Force_DX8TextureCategory_Deleting_Destructor(DX8TextureCategoryClass *category)
{
	delete category;
}
