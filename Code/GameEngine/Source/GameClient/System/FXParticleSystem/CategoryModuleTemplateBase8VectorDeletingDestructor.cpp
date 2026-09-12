// cl: /O2
// Retail RVA 0x0005E2D0: array vector-deleting destructor for
// FXParticleSystem::CategoryModuleTemplateBase<8>. The wrapper's scalar-destructor
// operand routes via ILT to the matched destructor at 0x0005E250. Element size 0x08.
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

CategoryModuleTemplateBase<8> *MakeCategoryModuleTemplateBase8Array()
{ return new CategoryModuleTemplateBase<8>[2]; }

void DeleteCategoryModuleTemplateBase8Array(CategoryModuleTemplateBase<8> *array)
{ delete[] array; }
}
