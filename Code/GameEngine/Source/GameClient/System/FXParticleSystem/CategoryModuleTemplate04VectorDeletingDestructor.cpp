// cl: /O2
// BFME FXParticleSystem::CategoryModuleTemplate<5> vector-deleting
// destructor at retail RVA 0x005BFC20. The scalar destructor is matched at
// 0x005BFB80 and the wrapper reaches it through ILT 0x0001DA02.

void operator delete[](void *block);

namespace FXParticleSystem
{
template <int Category> class CategoryModuleTemplate;

template <> class CategoryModuleTemplate<5>
{
public:
	virtual ~CategoryModuleTemplate();

private:
	int m_pad;
};

CategoryModuleTemplate<5> *MakeCategoryModuleTemplate04Array()
{
	return new CategoryModuleTemplate<5>[2];
}

void DeleteCategoryModuleTemplate04Array(CategoryModuleTemplate<5> *array)
{
	delete[] array;
}
}
