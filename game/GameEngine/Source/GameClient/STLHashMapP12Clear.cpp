// cl: /EHsc
// stlport
// Near-twin of STLHashMapP36Clear.cpp: STLport hashtable::clear over
// hash_map<int, 12-byte value>. Same shape, smaller node (0x2c-byte in the
// twin vs a smaller node here) and a virtual element destructor pinned as
// ??1Gen_dtor_0045f7f0@@UAE@XZ (0x0003D2B7) instead of the twin's.

#include <hash_map>

struct Gen_t_00461d30_p12cd
{
	virtual ~Gen_t_00461d30_p12cd();

	int a[10];
	Gen_t_00461d30_p12cd();
	Gen_t_00461d30_p12cd( const Gen_t_00461d30_p12cd & );
	Gen_t_00461d30_p12cd &operator=( const Gen_t_00461d30_p12cd & );
};

bool operator==( const Gen_t_00461d30_p12cd &, const Gen_t_00461d30_p12cd & );
bool operator<( const Gen_t_00461d30_p12cd &, const Gen_t_00461d30_p12cd & );

typedef _STL::pair<const int, Gen_t_00461d30_p12cd> TgPair_00461d30;
typedef _STL::hash_map<int, Gen_t_00461d30_p12cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_00461d30> > TgMap_00461d30;

template class _STL::hash_map<int, Gen_t_00461d30_p12cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_00461d30> >;
