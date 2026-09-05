// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail at 0x0058F160 (59B).  STLport list<12-byte>::push_back:
// 0x14 node via __node_alloc / bfmeAllocNode (0x0082E540), placement-new the
// three-dword value at +8, splice in front of the sentinel at [this].
// _STLP_NO_EXCEPTIONS drops the try in _M_create_node so MSVC 7.1 inlines it
// and keeps push esi / push edi in the entry block (same lever as
// ResourceGatheringManager_addSupply.cpp / Rva0037F740ListPushBack.cpp).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0058F160Elem
{
	int m_a;
	int m_b;
	int m_c;
};

class Rva0058F160List
{
public:
	void push_back(Rva0058F160Elem const &value);

private:
	_STL::list<Rva0058F160Elem> m_list;
};

void Rva0058F160List::push_back(Rva0058F160Elem const &value)
{
	m_list.push_back(value);
}
