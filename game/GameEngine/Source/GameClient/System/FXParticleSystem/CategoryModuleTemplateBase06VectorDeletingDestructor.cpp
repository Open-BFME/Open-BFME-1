// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplateBase<7> vector-deleting
// destructor at retail RVA 0x005C19C0. The scalar destructor is matched at
// 0x005C1940 and the wrapper reaches it through ILT 0x0004362B.

void operator delete[](void *block);

namespace FXParticleSystem
{
// Same base layout as CategoryModuleTemplate06CtorThunk.cpp: ModuleTemplate at
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

template <int Category>
class CategoryModuleTemplateBase
	: public ModuleTemplate,
	  public CategoryModuleInfo<Category>
{
public:
	CategoryModuleTemplateBase() {}
	virtual ~CategoryModuleTemplateBase();
};

CategoryModuleTemplateBase<7> *MakeCategoryModuleTemplateBase06Array()
{
	return new CategoryModuleTemplateBase<7>[2];
}

void DeleteCategoryModuleTemplateBase06Array(CategoryModuleTemplateBase<7> *array)
{
	delete[] array;
}
}
