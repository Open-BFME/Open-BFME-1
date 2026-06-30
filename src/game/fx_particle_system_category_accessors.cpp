#include "fx_particle_system_category.h"

namespace FXParticleSystem {

// Explicitly instantiate the simple accessor methods for every module category
// used by the original binary. The literals are shifted because MSVC 7.1 encodes
// template non-type arguments differently depending on the values present in the
// translation unit; 0 maps to category 10 ($0A@) and 1..8 map to categories 0..7.
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
