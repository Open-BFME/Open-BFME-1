// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<5> vector-deleting
// destructor at retail RVA 0x005BFAF0. The scalar destructor is matched at
// 0x005BFA60 and the wrapper reaches it through ILT 0x0000B04B.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<5>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<5> *MakeCategoryModuleTemplateBase04Array()
{
	return new CategoryModuleTemplateBase<5>[2];
}

void DeleteCategoryModuleTemplateBase04Array(CategoryModuleTemplateBase<5> *array)
{
	delete[] array;
}
}
