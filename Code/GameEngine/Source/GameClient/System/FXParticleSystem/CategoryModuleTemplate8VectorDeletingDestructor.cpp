// cl: /O2
// Retail RVA 0x0005E420: 12-byte CategoryModuleTemplate<8> array cleanup.
// Both destructor operands route through ILT 0x000259EB to 0x0005E370.
void operator delete[](void *block);

namespace FXParticleSystem
{
template<int N> class CategoryModuleTemplate
{
public:
    virtual ~CategoryModuleTemplate();
private:
    unsigned char m_data[8];
};

CategoryModuleTemplate<8> *MakeCategoryModuleTemplate8Array()
{ return new CategoryModuleTemplate<8>[2]; }

void DeleteCategoryModuleTemplate8Array(CategoryModuleTemplate<8> *array)
{ delete[] array; }
}
