// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail at 0x0037F740 (59B) on d_0036dcc0.  STLport list<12-byte>::push_back:
// 0x14 node via __node_alloc / bfmeAllocNode (0x0082E540), placement-new the
// three-dword value at +8, splice in front of the sentinel at [this].
// _STLP_NO_EXCEPTIONS drops the try in _M_create_node so MSVC 7.1 inlines it
// and keeps push esi / push edi in the entry block (same lever as
// ResourceGatheringManager_addSupply.cpp / Rva000D07A0ListPushBack.cpp).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0037F740Elem
{
	int m_a;
	int m_b;
	int m_c;
};

class Rva0037F740List
{
public:
	void push_back(Rva0037F740Elem const &value);

private:
	_STL::list<Rva0037F740Elem> m_list;
};

void Rva0037F740List::push_back(Rva0037F740Elem const &value)
{
	m_list.push_back(value);
}
