// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<3> vector-deleting
// destructor at retail RVA 0x005BF630. The scalar destructor is matched at
// 0x005BF5A0 and the wrapper reaches it through ILT 0x00035111.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<3>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<3> *MakeCategoryModuleTemplateBase02Array()
{
	return new CategoryModuleTemplateBase<3>[2];
}

void DeleteCategoryModuleTemplateBase02Array(CategoryModuleTemplateBase<3> *array)
{
	delete[] array;
}
}
