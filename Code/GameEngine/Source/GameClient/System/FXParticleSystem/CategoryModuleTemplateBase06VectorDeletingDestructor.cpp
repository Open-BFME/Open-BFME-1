// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<7> vector-deleting
// destructor at retail RVA 0x005C19C0. The scalar destructor is matched at
// 0x005C1940 and the wrapper reaches it through ILT 0x0004362B.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<7>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<7> *MakeCategoryModuleTemplateBase06Array()
{
	return new CategoryModuleTemplateBase<7>[2];
}

void DeleteCategoryModuleTemplateBase06Array(CategoryModuleTemplateBase<7> *array)
{
	delete[] array;
}
}
