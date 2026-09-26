// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<6> vector-deleting
// destructor at retail RVA 0x005BFD40. The scalar destructor is matched at
// 0x005BFCB0 and the wrapper reaches it through ILT 0x0002B751.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<6>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<6> *MakeCategoryModuleTemplateBase05Array()
{
	return new CategoryModuleTemplateBase<6>[2];
}

void DeleteCategoryModuleTemplateBase05Array(CategoryModuleTemplateBase<6> *array)
{
	delete[] array;
}
}
