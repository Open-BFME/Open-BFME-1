// cl: /EHsc
// stlport
// Retail 0x00C6DB80 initializes the hash_map at VA 0x0130CE58 and registers
// its 0x00C70E60 cleanup wrapper (mov ecx, g; jmp ~hashtable 0x00853460).
// The 0x00853EC0 constructor is STLport's default hash_map() over
// hashtable<pair<const int, P>, int, hash<int>, ...>: three empty functors,
// the bucket vector at +4..+0xC (EH state 0), the element count at +0x10
// and _M_initialize_buckets(100) (0x00853510, the same int-keyed payload).
// 0x00853510 is the only _M_initialize_buckets body this constructor and the
// (n, hash, equal, alloc) constructor at 0x008535C0 call, so both belong to
// one instantiation: the payload reuses that row's anonymous
// Gen_t_008535c0_p12cd. The map's application-level identity is not
// established.
#include <hash_map>

struct Gen_t_008535c0_p12cd
{
    int a[3];
    Gen_t_008535c0_p12cd();
    Gen_t_008535c0_p12cd(const Gen_t_008535c0_p12cd &);
    ~Gen_t_008535c0_p12cd();
    Gen_t_008535c0_p12cd &operator=(const Gen_t_008535c0_p12cd &);
};

typedef _STL::pair<const int, Gen_t_008535c0_p12cd> Rva00C6DB80Pair;
typedef _STL::hash_map<int, Gen_t_008535c0_p12cd, _STL::hash<int>, _STL::equal_to<int>,
    _STL::allocator<Rva00C6DB80Pair> > Rva00C6DB80Map;

class Rva00C6DB80Init
{
public:
	Rva00C6DB80Init()
	{
		((Rva00C6DB80Map *)this)->Rva00C6DB80Map::hash_map();
	}
	~Rva00C6DB80Init();
};

// 0x0130CE58 is recorded (DIR32) as ?TheBfmeObject_00C70E60@@3VGen_00C70E60Target@@A,
// the name its consumers bind; define the storage under that symbol.
// Retire ?g_rva0130CE58@@3VRva00C6DB80Init@@A
extern "C" { Rva00C6DB80Init __identifier("?TheBfmeObject_00C70E60@@3VGen_00C70E60Target@@A"); }
