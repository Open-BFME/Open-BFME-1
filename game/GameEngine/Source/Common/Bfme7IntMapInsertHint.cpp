// cl: /EHsc
// stlport

// Five copies of STLport's map<int,T>::insert(iterator, const value_type&) --
// the 31-byte forwarder that shuffles the hint and the pair into the tree's
// insert_unique and returns the iterator through the caller's slot.
//
// The forwarder's own bytes say nothing about T: it only passes references,
// so every instantiation of it is the same 31 bytes and the ONE call target
// is what separates them.  Each of these five calls a different
// _Rb_tree<int, pair<const int, T> >::insert_unique already carried in the
// ledger as a tree_int_p12cd instantiation (0x000A4C90, 0x000E1F40,
// 0x001B79E0, 0x002250B0, 0x00225FE0), which is why they are five rows and
// not five claims on one body -- and why they are not the
// map<int,_SBServer*> forwarder they were once landed as: that map's payload
// is a 4-byte pointer, and its tree is 0x00224AD0.
//
// The payload declarations mirror game/gen_small/tgrid_101.cpp's: a 12-byte
// layout with a nontrivial lifecycle and no identity.  Nothing here defines a
// function; the member-pointer initialisers exist only to make the compiler
// emit the COMDAT.

#include <map>

#define BFME_INT_MAP_INSERT_HINT(RVA)                                                        \
	struct Gen_t_##RVA##_p12cd {                                                             \
		int a[3];                                                                            \
		Gen_t_##RVA##_p12cd();                                                               \
		Gen_t_##RVA##_p12cd(const Gen_t_##RVA##_p12cd&);                                     \
		~Gen_t_##RVA##_p12cd();                                                              \
		Gen_t_##RVA##_p12cd& operator=(const Gen_t_##RVA##_p12cd&);                          \
	};                                                                                       \
	typedef _STL::map<int, Gen_t_##RVA##_p12cd, _STL::less<int>,                             \
	                  _STL::allocator<_STL::pair<const int, Gen_t_##RVA##_p12cd> > >         \
	        BfmeIntMap_##RVA;                                                                \
	static BfmeIntMap_##RVA::iterator (BfmeIntMap_##RVA::*bfmeEmit_##RVA)(                   \
	        BfmeIntMap_##RVA::iterator, const BfmeIntMap_##RVA::value_type&)                 \
	        = &BfmeIntMap_##RVA::insert;

BFME_INT_MAP_INSERT_HINT(000a4c90)
BFME_INT_MAP_INSERT_HINT(000e1f40)
BFME_INT_MAP_INSERT_HINT(001b79e0)
BFME_INT_MAP_INSERT_HINT(002250b0)
BFME_INT_MAP_INSERT_HINT(00225fe0)
