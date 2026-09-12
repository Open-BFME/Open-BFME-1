// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<7> vector-deleting
// destructor at retail RVA 0x005C1B80. The scalar destructor is matched at
// 0x005C1AC0 and the wrapper reaches it through ILT 0x000081C5.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<7>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad[19];
};

CategoryModuleTemplate<7> *MakeCategoryModuleTemplate07Array()
{
	return new CategoryModuleTemplate<7>[2];
}

void DeleteCategoryModuleTemplate07Array(CategoryModuleTemplate<7> *array)
{
	delete[] array;
}
}
