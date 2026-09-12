// cl: /O2
// Retail RVA 0x0005DA10: array vector-deleting destructor for
// FXParticleSystem::CategoryModuleTemplate<0>. The wrapper's scalar-destructor
// operand routes via ILT to the matched destructor at 0x0005D970. Element size 0x08.
void operator delete[](void *block);

namespace FXParticleSystem
{
template<int N> class CategoryModuleTemplate
{
public:
	virtual ~CategoryModuleTemplate();
private:
	unsigned char m_data[0x04];
};

CategoryModuleTemplate<0> *MakeCategoryModuleTemplate0Array()
{ return new CategoryModuleTemplate<0>[2]; }

void DeleteCategoryModuleTemplate0Array(CategoryModuleTemplate<0> *array)
{ delete[] array; }
}
