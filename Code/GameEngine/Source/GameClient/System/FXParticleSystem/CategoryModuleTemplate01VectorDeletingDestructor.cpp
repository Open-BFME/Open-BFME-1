// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<2> vector-deleting
// destructor at retail RVA 0x005BF510. The scalar destructor is matched at
// 0x005BF470 and the wrapper reaches it through ILT 0x00037E66.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<2>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<2> *MakeCategoryModuleTemplate01Array()
{
	return new CategoryModuleTemplate<2>[2];
}

void DeleteCategoryModuleTemplate01Array(CategoryModuleTemplate<2> *array)
{
	delete[] array;
}
}
