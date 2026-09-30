// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: the string-keyed map bodies of the ping thread (retail
// 0x0064CBD0 hinted insert_unique, 628 bytes, and 0x0064E690 operator[],
// 229 bytes).  The class and its matched callers live in PingThread.cpp
// (Pinger::addResponse at 0x006615B0) and PeerThreadTrackStatsForPlayer.cpp
// (trackStatsForPlayer at 0x0064E7B0); the callees they share (_M_lower_bound
// at 0x00645870, operator< at 0x006451D0, the string copy ctor at 0x004FB1B0)
// are matched in those TUs.  Both instantiations sit here in one TU so the
// hinted insert the subscript calls resolves within the same object:
// the instantiation's COMDAT reproduces retail 0x0064CBD0 exactly (probe
// EXACT modulo relocs) and the ledger row there keeps its
// AsciiString/Coord3D claim, through which this TU's call resolves.
#include <map>
#include <string>

typedef _STL::map<_STL::string, int> Rva0064PingMap;
template _STL::_Rb_tree_iterator<_STL::pair<const _STL::string, int>, _STL::_Nonconst_traits<_STL::pair<const _STL::string, int> > > Rva0064PingMap::_Rep_type::insert_unique(Rva0064PingMap::_Rep_type::iterator, const Rva0064PingMap::value_type &);
template int &Rva0064PingMap::operator[](const _STL::string &key);
