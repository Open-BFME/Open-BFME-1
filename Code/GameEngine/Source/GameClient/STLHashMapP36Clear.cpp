// cl: /EHsc
// stlport
// STLport hashtable::clear over hash_map<int, 36-byte copy-destruct value>.
// Retail deallocates 0x2c-byte nodes: 4-byte next, 4-byte int key, 36-byte value.

#include <hash_map>

struct Gen_t_0042dc10_p36cd
{
	int a[9];
	Gen_t_0042dc10_p36cd();
	Gen_t_0042dc10_p36cd(const Gen_t_0042dc10_p36cd &);
	~Gen_t_0042dc10_p36cd();
	Gen_t_0042dc10_p36cd &operator=(const Gen_t_0042dc10_p36cd &);
};

bool operator==(const Gen_t_0042dc10_p36cd &, const Gen_t_0042dc10_p36cd &);
bool operator<(const Gen_t_0042dc10_p36cd &, const Gen_t_0042dc10_p36cd &);

typedef _STL::pair<const int, Gen_t_0042dc10_p36cd> TgPair_0042dc10;
typedef _STL::hash_map<int, Gen_t_0042dc10_p36cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_0042dc10> > TgMap_0042dc10;

template class _STL::hash_map<int, Gen_t_0042dc10_p36cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_0042dc10> >;
