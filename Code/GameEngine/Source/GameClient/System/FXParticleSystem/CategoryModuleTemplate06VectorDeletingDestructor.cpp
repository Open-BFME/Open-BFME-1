// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<6> vector-deleting
// destructor at retail RVA 0x005BFE70. The scalar destructor is matched at
// 0x005BFDD0 and the wrapper reaches it through ILT 0x00022C64.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<6>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<6> *MakeCategoryModuleTemplate06Array()
{
	return new CategoryModuleTemplate<6>[2];
}

void DeleteCategoryModuleTemplate06Array(CategoryModuleTemplate<6> *array)
{
	delete[] array;
}
}
