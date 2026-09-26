// cl: /EHsc
// stlport
// STLport's hash-table iterator for_each instantiation used by the 87C20
// owner destructor.  The payload is a 12-byte copy-destruct value.

#include <algorithm>
#include <hash_map>

struct Gen_t_00786db0_p12cd
{
	int a[3];
	Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd(const Gen_t_00786db0_p12cd &);
	~Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd &operator=(const Gen_t_00786db0_p12cd &);
};

bool operator==(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);
bool operator<(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);

struct Gen_t_00786e70_p12cd
{
	int a[3];
	Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd(const Gen_t_00786e70_p12cd &);
	~Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd &operator=(const Gen_t_00786e70_p12cd &);
};

bool operator==(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);
bool operator<(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);

typedef _STL::pair<const int, Gen_t_00786db0_p12cd> Rva00787260Pair;
typedef _STL::hash_map<int, Gen_t_00786db0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00787260Pair> > Rva00787260Map;
typedef void (__cdecl *Rva00787260Function)(Rva00787260Pair &);

template void (__cdecl * _STL::for_each<Rva00787260Map::iterator,
	Rva00787260Function>(Rva00787260Map::iterator, Rva00787260Map::iterator,
	Rva00787260Function))(Rva00787260Pair &);

typedef _STL::pair<const int, Gen_t_00786e70_p12cd> Rva007872f0Pair;
typedef _STL::hash_map<int, Gen_t_00786e70_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva007872f0Pair> > Rva007872f0Map;
typedef void (__cdecl *Rva007872f0Function)(Rva007872f0Pair &);

template void (__cdecl * _STL::for_each<Rva007872f0Map::iterator,
	Rva007872f0Function>(Rva007872f0Map::iterator, Rva007872f0Map::iterator,
	Rva007872f0Function))(Rva007872f0Pair &);
