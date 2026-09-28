// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The out-of-line push_back for SubsystemInterfaceList::m_subsystems
// (vector<pair<SubsystemInterface *, void *> >, subsystem_interface.h).
//
// Retail 0x009A1FF0 lies in SubsystemInterface.cpp's run of code, between this
// vector's _M_insert_overflow at 0x009A1E50 and SubsystemInterfaceList::
// initSubsystem at 0x009A20B0. initSubsystem inlines push_back and calls
// 0x009A1E50 for the growth path, which fixes the element type; this body's
// slow path calls the same 0x009A1E50. The OCLSpecialPowerModuleData::Upgrades
// vector, the other eight-byte element with an identical body, has its own
// copies at 0x009F3A40 / 0x009F36F0. Nothing in the image references
// 0x009A1FF0.
//
// Retail's pair copies as a plain eight-byte record. With STLport's member
// templates on, pair gains a user-declared copy constructor, _Construct stays
// out of line and neither this body (62 B) nor the 0x009A1E50 overflow (306 B)
// reproduces; without them both are exact. Only this TU drops them.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_NO_MEMBER_TEMPLATES 1
#include <utility>
#include <vector>

class SubsystemInterface;

template void _STL::vector<_STL::pair<SubsystemInterface *, void *> >::push_back(
	const _STL::pair<SubsystemInterface *, void *> &);
