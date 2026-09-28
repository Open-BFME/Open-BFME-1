// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x003D14D0..0x003D1570. STLport reserve with outlined cleanup.
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"
// Expose the nested type for explicit instantiation without duplicating its layout.
#define private public
#include "GameLogic/Module/ParkingPlaceBehavior.h"
#undef private

namespace _STL {
template<> void vector<ParkingPlaceBehavior::ParkingPlaceInfo>::_M_clear();
}
template void _STL::vector<ParkingPlaceBehavior::ParkingPlaceInfo>::reserve(unsigned int);
