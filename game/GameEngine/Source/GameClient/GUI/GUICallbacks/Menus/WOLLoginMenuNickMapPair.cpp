// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

#include "PreRTS.h"
#include "Common/STLTypedefs.h"

// Retail calls a TU-local list-layout copy thunk at 0x00443D60 rather than
// the standard STLport list copy constructor used elsewhere.  Only the ABI
// shape is needed here: the pair constructor passes the second member to it.
class WOLLoginNickList
{
public:
	WOLLoginNickList();
	WOLLoginNickList( const WOLLoginNickList &that );

private:
	void *m_node;
};

template class _STL::pair<const AsciiString, WOLLoginNickList>;
