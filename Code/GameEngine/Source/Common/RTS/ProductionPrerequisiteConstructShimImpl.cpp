// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

inline void *operator new(unsigned int, void *place) { return place; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
    ProductionPrerequisite(const ProductionPrerequisite &);
};

namespace _STL
{
class ProductionPrerequisiteConstructShim
{
public:
    static void construct(ProductionPrerequisite *p, const ProductionPrerequisite &v);
};

// ?ProductionPrerequisiteConstructShim::construct present-unmatched
void ProductionPrerequisiteConstructShim::construct(ProductionPrerequisite *p, const ProductionPrerequisite &v)
{
    if (p)
        new (p) ProductionPrerequisite(v);
}
}
