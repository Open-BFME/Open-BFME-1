// cl: /O2
// Retail RVA 0x0005D8E0: array vector-deleting destructor for
// FXParticleSystem::CategoryModuleTemplateBase<0>. The wrapper's scalar-destructor
// operand routes via ILT to the matched destructor at 0x0005D850. Element size 0x08.
void operator delete[](void *block);

namespace FXParticleSystem
{
template<int N> class CategoryModuleTemplateBase
{
public:
	virtual ~CategoryModuleTemplateBase();
private:
	unsigned char m_data[0x04];
};

CategoryModuleTemplateBase<0> *MakeCategoryModuleTemplateBase0Array()
{ return new CategoryModuleTemplateBase<0>[2]; }

void DeleteCategoryModuleTemplateBase0Array(CategoryModuleTemplateBase<0> *array)
{ delete[] array; }
}
