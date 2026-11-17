// cl: /O2
// Retail RVA 0x0005D8E0: array vector-deleting destructor for
// FXParticleSystem::CategoryModuleTemplateBase<0>. The wrapper's scalar-destructor
// operand routes via ILT to the matched destructor at 0x0005D850. Element size 0x08.
void operator delete[](void *block);

namespace FXParticleSystem
{
// Same base layout as DefaultModuleTemplate0ACtorThunk.cpp: ModuleTemplate at
// +0 and CategoryModuleInfo at +4, so the array-new constructor loop emits the
// retail-identical default constructor COMDAT instead of a one-vptr view's.
class ModuleTemplate
{
public:
	ModuleTemplate() {}
	virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
	CategoryModuleInfo() {}
	virtual void unusedVirtual();

protected:
	~CategoryModuleInfo() {}
};

template <int N>
class CategoryModuleTemplateBase
	: public ModuleTemplate,
	  public CategoryModuleInfo<N>
{
public:
	CategoryModuleTemplateBase() {}
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<0> *MakeCategoryModuleTemplateBase0Array()
{ return new CategoryModuleTemplateBase<0>[2]; }

void DeleteCategoryModuleTemplateBase0Array(CategoryModuleTemplateBase<0> *array)
{ delete[] array; }
}
