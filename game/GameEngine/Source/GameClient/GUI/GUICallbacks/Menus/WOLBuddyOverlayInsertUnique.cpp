// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

// The tree's _M_insert is retail 0x004EBC90 (stlport_rb_tree_int_buddyinfo_insert.cpp);
// instantiated here it came out as a different COMDAT copy (link_census
// RetailTruth: "wrong") that the link kept ahead of retail's, so this TU only
// declares it.
typedef std::pair<const GPProfile, BuddyInfo> BuddyInfoPair;
template <>
std::_Rb_tree<GPProfile, BuddyInfoPair, std::_Select1st<BuddyInfoPair>, std::less<GPProfile>,
	std::allocator<BuddyInfoPair> >::iterator
std::_Rb_tree<GPProfile, BuddyInfoPair, std::_Select1st<BuddyInfoPair>, std::less<GPProfile>,
	std::allocator<BuddyInfoPair> >::_M_insert(
	std::_Rb_tree_node_base *, std::_Rb_tree_node_base *, const BuddyInfoPair &,
	std::_Rb_tree_node_base * );

template class std::map<GPProfile, BuddyInfo>;
