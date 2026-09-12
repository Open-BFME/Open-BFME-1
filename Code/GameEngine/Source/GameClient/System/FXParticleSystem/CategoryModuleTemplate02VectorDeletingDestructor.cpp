// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<3> vector-deleting
// destructor at retail RVA 0x005BF760. The scalar destructor is matched at
// 0x005BF6C0 and the wrapper reaches it through ILT 0x0002E6EA.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<3>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<3> *MakeCategoryModuleTemplate02Array()
{
	return new CategoryModuleTemplate<3>[2];
}

void DeleteCategoryModuleTemplate02Array(CategoryModuleTemplate<3> *array)
{
	delete[] array;
}
}
