// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<1> vector-deleting
// destructor at retail RVA 0x005BF2C0. The scalar destructor is matched at
// 0x005BF220 and the wrapper reaches it through ILT 0x00049FE4.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<1>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<1> *MakeCategoryModuleTemplate00Array()
{
	return new CategoryModuleTemplate<1>[2];
}

void DeleteCategoryModuleTemplate00Array(CategoryModuleTemplate<1> *array)
{
	delete[] array;
}
}
