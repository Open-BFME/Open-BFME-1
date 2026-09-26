// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<4> vector-deleting
// destructor at retail RVA 0x005BF880. The scalar destructor is matched at
// 0x005BF7F0 and the wrapper reaches it through ILT 0x00041D5D.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplateBase;

template <> class CategoryModuleTemplateBase<4>
{
public:
	virtual ~CategoryModuleTemplateBase();

private:
	int m_pad;
};

CategoryModuleTemplateBase<4> *MakeCategoryModuleTemplateBase03Array()
{
	return new CategoryModuleTemplateBase<4>[2];
}

void DeleteCategoryModuleTemplateBase03Array(CategoryModuleTemplateBase<4> *array)
{
	delete[] array;
}
}
