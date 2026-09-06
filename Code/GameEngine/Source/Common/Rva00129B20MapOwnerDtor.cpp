// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00129B20 is the STLport _Rb_tree destructor for an int-keyed pointer
// map, a byte-twin (tools/twin_scan.py) of the eighteen-way ICF fold at
// 0x006587F0 (StateMachine.cpp, map<UnsignedInt, State *>). An explicit
// `template class` instantiation compiles 10 bytes long (an extra operator
// delete path); the retail shape is the IMPLICIT instantiation the compiler
// emits for a class that owns the map as a member, so that is how it is
// reached here. The pinned callee names the payload "Open2State129B20"; no
// matched caller names the owner, so it stays address-derived.

#define _STLP_USE_NEWALLOC 1   // the game builds STLport on plain operator new/delete (STLTypedefs.h)
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Open2State129B20;

class Rva00129B20MapOwner
{
public:
	~Rva00129B20MapOwner();

private:
	_STL::map<unsigned int, Open2State129B20 *> m_states;
};

Rva00129B20MapOwner::~Rva00129B20MapOwner()
{
}
