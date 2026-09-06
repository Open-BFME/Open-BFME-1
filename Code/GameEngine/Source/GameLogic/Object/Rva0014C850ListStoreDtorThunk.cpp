// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived: 0.852 difflib match to the landed
// ??1Rva001B0820Store@@UAE@XZ (Code/GameEngine/Source/GameLogic/Object/
// Rva001B0820HashMapDtorThunk.cpp) -- same "own vtable, member container
// teardown, string release" shape -- but the retail callee set proves a
// different container: the first callee (ILT thunk 0x0001947F) is the
// already-matched STLport ?clear@?$_List_base@UGen_t_0014bd80_p8cd@@...@Z
// (Code/gen_small/tgrid_105.cpp), not a hash_map clear, and after it the
// body manually frees the list's own dummy head node via
// _M_deallocate(node, 0x10) (Code/Libraries/Source/WWVegas/WWLib/
// node_alloc_M_deallocateThunk.cpp) -- the standard STLport
// `_List_base::~_List_base()` idiom (clear() then free the sentinel),
// inlined here rather than called out of line. No base-class destructor is
// called, unlike the hash_map twin's SubsystemInterface chain, so this
// class has no polymorphic base with an out-of-line destructor. Installs
// vtable 0x010959D4. Real class, member and value-type names not recovered.

#include <list>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

// reused verbatim from the already-instantiated list value type
// (Code/gen_small/tgrid_105.cpp) so the list's own destructor chain matches.
struct Gen_t_0014bd80_p8cd
{
	int a[ 2 ];
	Gen_t_0014bd80_p8cd();
	Gen_t_0014bd80_p8cd( const Gen_t_0014bd80_p8cd & );
	~Gen_t_0014bd80_p8cd();
	Gen_t_0014bd80_p8cd &operator=( const Gen_t_0014bd80_p8cd & );
};

// address-derived
class Rva0014C850Store
{
public:
	virtual ~Rva0014C850Store();

private:
	AsciiString m_name;
	int m_unmodelled;
	_STL::list<Gen_t_0014bd80_p8cd> m_list;
	int m_count;
};

// address-derived: ?d_0014c850@@YAXXZ real name and identity not recovered
Rva0014C850Store::~Rva0014C850Store()
{
	m_count = 0;
}
