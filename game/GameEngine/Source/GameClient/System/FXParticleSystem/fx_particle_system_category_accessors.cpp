#include "fx_particle_system_category.h"

namespace FXParticleSystem {

#define CAT_BASE(N)                                                                                 \
    template <> CategoryModuleClassBase<N>::CategoryModuleClassBase(const CategoryModuleClass<N> &module, bool setDefault) \
    {                                                                                               \
        if (setDefault)                                                                             \
            s_defaultModule = const_cast<CategoryModuleClass<N> *>(&module);                        \
    }

#define CAT_DERIVED(N)                                                                              \
    template <> CategoryModuleClass<N>::CategoryModuleClass(bool setDefault, const char *key, const char *name) \
        : CategoryModuleClassBase<N>(*this, setDefault)                                             \
    {                                                                                               \
        m_key = key;                                                                                \
        m_name = name;                                                                              \
        m_next = s_firstList;                                                                       \
        s_firstList = this;                                                                         \
    }

// Categories 0..7 have a default module; the base constructor records it.
CAT_BASE(0)
CAT_BASE(1)
CAT_BASE(2)
CAT_BASE(3)
CAT_BASE(4)
CAT_BASE(5)
CAT_BASE(6)
CAT_BASE(7)

// Categories 0..7 register their default-capable module lists.
CAT_DERIVED(0)
CAT_DERIVED(1)
CAT_DERIVED(2)
CAT_DERIVED(3)
CAT_DERIVED(4)
CAT_DERIVED(5)
CAT_DERIVED(6)
CAT_DERIVED(7)

// Category 8 registers its module list without a category default.
template <> CategoryModuleClass<8>::CategoryModuleClass(bool, const char *key, const char *name)
{
    m_key = key;
    m_name = name;
    m_next = s_firstList;
    s_firstList = this;
}

// getDefault returns the registered default module for categories that have one.
#define CAT_DEFAULT(N) \
    template <> const CategoryModuleClass<N> &CategoryModuleClassBase<N>::getDefault() { return *s_defaultModule; }

CAT_DEFAULT(0)
CAT_DEFAULT(1)
CAT_DEFAULT(2)
CAT_DEFAULT(3)
CAT_DEFAULT(4)
CAT_DEFAULT(5)
CAT_DEFAULT(6)
CAT_DEFAULT(7)

// Destructors: the compiler emits the vtable reset automatically because
// CategoryModuleClass has a virtual destructor; the exact vtable address is
// filled in by the patcher from the original binary.
template <> CategoryModuleClass<0>::~CategoryModuleClass() {}
template <> CategoryModuleClass<1>::~CategoryModuleClass() {}
template <> CategoryModuleClass<2>::~CategoryModuleClass() {}
template <> CategoryModuleClass<3>::~CategoryModuleClass() {}
template <> CategoryModuleClass<4>::~CategoryModuleClass() {}
template <> CategoryModuleClass<5>::~CategoryModuleClass() {}
template <> CategoryModuleClass<6>::~CategoryModuleClass() {}
template <> CategoryModuleClass<7>::~CategoryModuleClass() {}
template <> CategoryModuleClass<8>::~CategoryModuleClass() {}

// Explicitly instantiate the module categories present in retail. MSVC encodes
// zero as $0A@ and integers 1..8 as $00..$07.
template class CategoryModuleClass<0>;
template class CategoryModuleClass<1>;
template class CategoryModuleClass<2>;
template class CategoryModuleClass<3>;
template class CategoryModuleClass<4>;
template class CategoryModuleClass<5>;
template class CategoryModuleClass<6>;
template class CategoryModuleClass<7>;
template class CategoryModuleClass<8>;

}
