// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail at 0x000D07A0.  STLport list<8-byte>::push_back: 16-byte node via
// __node_alloc / bfmeAllocNode (0x0082E540), placement-new the value at +8,
// splice in front of the sentinel at [this].  _STLP_NO_EXCEPTIONS drops the
// try in _M_create_node so MSVC 7.1 inlines it and keeps push esi / push edi
// in the entry block (same lever as ResourceGatheringManager_addSupply.cpp).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva000D07A0Elem
{
	void *m_a;
	void *m_b;
};

class Rva000D07A0List
{
public:
	void push_back(Rva000D07A0Elem const &value);

private:
	_STL::list<Rva000D07A0Elem> m_list;
};

void Rva000D07A0List::push_back(Rva000D07A0Elem const &value)
{
	m_list.push_back(value);
}
