// cl: /DNDEBUG /MD /EHsc

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
