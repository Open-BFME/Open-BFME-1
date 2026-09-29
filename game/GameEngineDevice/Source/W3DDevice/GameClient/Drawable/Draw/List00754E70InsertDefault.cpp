// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00754E70, 128 bytes, thiscall, ret 8.
//
// Identity: matched caller 0x00755170
// (?apply@Synchronize00755170@@QAEXPAPAUEntry00755170@@0@Z) reaches this body
// through the ILT entry E9 at 0x0002385D, which the ledger pins as
// ?insertDefault@List00754E70@@QAE?AUIter00754E70@@U2@@Z
//
// ABI read from the retail bytes:
//   thiscall, two 4-byte stack slots popped by `ret 8`:
//     [esp+4]  hidden return buffer for Iter00754E70 (a class with a
//              user-defined copy ctor, so MSVC returns it through a pointer)
//     [esp+8]  the by-value Iter00754E70 argument (its single `node` word)
//   this is never read: STLport's insert(position, value) only rewrites the
//   links around `position`, so ecx is free for the placement-new `this`.
//   - sub esp,0x14 / push esi / push edi frame; a 12-byte default-empty
//     vector<Object*> temporary is materialised at [esp+0x10] by three inline
//     null stores, a 0x14-byte node is allocated through the matched
//     __new_alloc::allocate (0x0082E540), the payload is copy-constructed at
//     node+8 through the matched vector copy ctor (ILT 0x000494AE ->
//     0x00753C60), and the four link stores follow, ending with the node
//     written through the hidden return slot.
// The class vocabulary (Node00754E70 / Iter00754E70 / List00754E70) is the one
// the matched caller file already declares for its list member, so the two TUs
// agree on the names this body is pinned under.
//
// _STLP_NO_EXCEPTIONS is load-bearing: it removes the try/unwind pair from
// _M_create_node (_list.h:236), which is what makes MSVC 7.1 inline the
// allocation and the payload copy. With the pair present the body is 92 bytes
// and never calls the allocator. Same lever as the matched sibling
// Rva000D07A0ListPushBack.cpp.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

class Object;

struct Node00754E70
{
	Node00754E70 *next;
	Node00754E70 *prev;
	_STL::vector<Object *> data;
};

struct Iter00754E70
{
	Node00754E70 *node;
	Iter00754E70(Node00754E70 *p) : node(p) {}
	Iter00754E70(const Iter00754E70 &p) : node(p.node) {}
};

class List00754E70
{
public:
	Iter00754E70 insertDefault(Iter00754E70 position);
private:
	_STL::list<_STL::vector<Object *> > m_values;
};

Iter00754E70 List00754E70::insertDefault(Iter00754E70 position)
{
	typedef _STL::vector<Object *> Value;
	typedef _STL::_List_iterator<Value, _STL::_Nonconst_traits<Value> > RvaIterator;
	RvaIterator where((_STL::_List_node<Value> *)position.node);
	RvaIterator created = m_values.insert(where, Value());
	return Iter00754E70((Node00754E70 *)created._M_node);
}
