// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<4> vector-deleting
// destructor at retail RVA 0x005BF9B0. The scalar destructor is matched at
// 0x005BF910 and the wrapper reaches it through ILT 0x0001DF48.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<4>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<4> *MakeCategoryModuleTemplate03Array()
{
	return new CategoryModuleTemplate<4>[2];
}

void DeleteCategoryModuleTemplate03Array(CategoryModuleTemplate<4> *array)
{
	delete[] array;
}
}
