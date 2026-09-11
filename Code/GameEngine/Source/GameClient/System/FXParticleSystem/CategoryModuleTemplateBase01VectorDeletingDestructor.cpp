// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<2> vector-deleting
// destructor at retail RVA 0x005BF3E0. The scalar destructor is matched at
// 0x005BF350 and the wrapper reaches it through ILT 0x0000EAB1.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<2>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<2> *MakeCategoryModuleTemplateBase01Array()
{
	return new CategoryModuleTemplateBase<2>[2];
}

void DeleteCategoryModuleTemplateBase01Array(CategoryModuleTemplateBase<2> *array)
{
	delete[] array;
}
}
