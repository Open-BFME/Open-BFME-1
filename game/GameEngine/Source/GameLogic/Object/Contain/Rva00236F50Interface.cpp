// Retail 0x00236F50 is reached through slot 62 (+0xF8) in the AODHordeContain,
// HordeContain, and HorseHordeContain vtables. Those entries share the thunk
// at 0x0003A1E8. The method's semantic name and concrete owner remain unproven,
// so this translation unit uses an address-derived interface view.
// The body reads the list sentinel at this+0x18 and the member-index header at
// this+0xF4, then dispatches Object slot 18 for list members and hash lookups.
// The game-logic hash and STLport tree-increment layouts are shared with landed
// HordeContain member-walk bodies.
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

// STLport red-black tree node base (verbatim, matches
// STLRbGlobalBoolIncrementThunk.cpp / inputs/vendor/stlport/stl/_tree.c).
namespace _STL {

typedef bool _Rb_tree_Color_type;

struct _Rb_tree_node_base
{
	typedef _Rb_tree_Color_type _Color_type;
	typedef _Rb_tree_node_base *_Base_ptr;

	_Color_type _M_color;
	_Base_ptr _M_parent;
	_Base_ptr _M_left;
	_Base_ptr _M_right;
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

}

#define BFME_SLOT(N) virtual void bfmeSlot##N()

class Rva00236F50ObjectView
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17);
	// slot 18, +0x48
	virtual void slot18();
};

#undef BFME_SLOT

struct Rva00236F50ListNode
{
	Rva00236F50ListNode *m_next;
	void *m_pad04;
	Rva00236F50ObjectView *m_value;
};

struct Rva00236F50TreeNode : _STL::_Rb_tree_node_base
{
	unsigned int m_value;
};

typedef _STL::hash_map<unsigned int, Rva00236F50ObjectView *,
	_STL::hash<unsigned int>, _STL::equal_to<unsigned int> >
	Rva00236F50ObjectHash;

class Rva00367E30Logic
{
public:
	__forceinline Rva00236F50ObjectView *findObjectByID(unsigned int key)
	{
		Rva00236F50ObjectHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_pad00[0xB0];
	Rva00236F50ObjectHash m_objectHash;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

template <int N>
class Rva00236F50InterfaceSlots : public Rva00236F50InterfaceSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva00236F50InterfaceSlots<0>
{
};

class Rva00236F50Interface : public Rva00236F50InterfaceSlots<62>
{
public:
	virtual void rva00236f50();

private:
	char m_pad00[0x14];
	Rva00236F50ListNode *m_listSentinel;
	char m_pad1C[0xF4 - 0x18 - 4];
	Rva00236F50TreeNode *m_treeHeader;
};

void Rva00236F50Interface::rva00236f50()
{
	{
		Rva00236F50ListNode *node = m_listSentinel->m_next;
		while (node != m_listSentinel)
		{
			node->m_value->slot18();
			node = node->m_next;
		}
	}

	Rva00236F50TreeNode *header = m_treeHeader;
	Rva00236F50TreeNode *node = (Rva00236F50TreeNode *)header->_M_left;
	while (node != header)
	{
		unsigned int id = node->m_value;
		if (id != 0)
		{
			Rva00236F50ObjectView *object =
				TheBfmeGameLogic->findObjectByID(id);
			if (object != 0)
				object->slot18();
		}

		node = (Rva00236F50TreeNode *)_STL::_Rb_global<bool>::_M_increment(node);
		header = m_treeHeader;
	}
}
