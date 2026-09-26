// Retail RVA 0x002396F0 is installed at vtable slot 95 in several Horde-family
// tables. The shared slot does not establish an owning class or method name,
// so this source keeps the address-derived identity.
// The generated 480-byte extent cuts the `add esp, 0x2c` at +0x1DF; retail's
// `ret` at +0x1E2 makes the verified body 483 bytes.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <hash_map>
#include <bitset>

// This body uses only the 40-byte ABI of BFME's BitFlags<320>; its backing
// storage is the upstream std::bitset wrapper.
template <size_t N>
class BitFlags
{
private:
	std::bitset<N> m_bits;
};

#define OBJECT_TU_MEMBERS \
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear, \
		const BitFlags<320> &set);
#include "../object.h"
#undef OBJECT_TU_MEMBERS

struct Rva002396F0MemberNode
{
	Rva002396F0MemberNode *next;
	void *unused;
	Object *object;
};
typedef char Rva002396F0MemberNodeSize[
	(sizeof(Rva002396F0MemberNode) == 0x0C) ? 1 : -1];

struct Rva002396F0TreeValue
{
	int value;
};

struct Rva002396F0TreeNode
{
	unsigned int color;
	Rva002396F0TreeNode *parent;
	Rva002396F0TreeNode *left;
	Rva002396F0TreeNode *right;
	Rva002396F0TreeValue value;
	unsigned int padding;
};

struct Rva002396F0TreeHeader
{
	unsigned int color;
	Rva002396F0TreeNode *parent;
	Rva002396F0TreeNode *left;
	Rva002396F0TreeNode *right;
};

struct Rva002396F0TreeView
{
	Rva002396F0TreeHeader *header;
	unsigned int nodeCount;
};
typedef char Rva002396F0TreeNodeSize[
	(sizeof(Rva002396F0TreeNode) == 0x18) ? 1 : -1];
typedef char Rva002396F0TreeHeaderSize[
	(sizeof(Rva002396F0TreeHeader) == 0x10) ? 1 : -1];
typedef char Rva002396F0TreeViewSize[
	(sizeof(Rva002396F0TreeView) == 0x08) ? 1 : -1];
typedef char Rva002396F0ModelConditionFlagsSize[
	(sizeof(BitFlags<320>) == 0x28) ? 1 : -1];

extern void __cdecl Gen0082E5F0(void *node, unsigned int size);

struct Gen_t_002221b0_p4pod
{
	int value;
};

typedef _STL::pair<const int, Gen_t_002221b0_p4pod>
	Rva002396F0TreeValuePair;

// 0x002221B0 is the matched STLport _M_erase specialization for this 24-byte
// node. Keep the declaration narrow so this caller emits its real tree call.
class Rva002396F0TreeAccess;

namespace _STL
{
template <class Value>
struct _Rb_tree_node;

template <class Value>
struct _Select1st;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> *_Link_type;

private:
	friend class ::Rva002396F0TreeAccess;
	void _M_erase(_Link_type node);
};
}

typedef _STL::_Rb_tree<int, Rva002396F0TreeValuePair,
	_STL::_Select1st<Rva002396F0TreeValuePair>, _STL::less<int>,
	_STL::allocator<Rva002396F0TreeValuePair> > Rva002396F0FormationTree;

class Rva002396F0TreeAccess
{
public:
	static __forceinline void erase(Rva002396F0FormationTree *tree,
		Rva002396F0TreeNode *node)
	{
		tree->_M_erase((Rva002396F0FormationTree::_Link_type)node);
	}
};

typedef _STL::hash_map<int, Object *,
	_STL::hash<int>, _STL::equal_to<int> > Rva002396F0ObjectHash;

// BFME's inline ID lookup uses the original STLport hash map; the object hash
// starts at +0xB0, as it does in the matched GameLogic lookup body.
class GameLogic
{
public:
	__forceinline Object *findObjectByID(int id)
	{
		if (id == 0)
			return 0;
		Rva002396F0ObjectHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_pad00[0xB0];
	Rva002396F0ObjectHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

template <int N>
class Rva002396F0SlotPrefix : public Rva002396F0SlotPrefix<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva002396F0SlotPrefix<0>
{
};

class Rva002396F0 : public Rva002396F0SlotPrefix<95>
{
public:
	virtual void rva002396f0();

private:
	char m_pad00[0x68];
	int m_idA;
	int m_idB;
	BitFlags<320> m_clearMaskA;
	BitFlags<320> m_clearMaskB;
	Rva002396F0TreeView m_tree;
};

void Rva002396F0::rva002396f0()
{
	Rva002396F0MemberNode *member =
		(*(Rva002396F0MemberNode **)((char *)this - 0xAC))->next;
	while (member != *(Rva002396F0MemberNode **)((char *)this - 0xAC))
	{
		member->object->clearAndSetModelConditionFlags(
			m_clearMaskB, BitFlags<320>());
		member = member->next;
	}

	Rva002396F0TreeView *tree = &m_tree;
	if (tree->nodeCount != 0)
	{
		Rva002396F0TreeNode *node = tree->header->parent;
		while (node != 0)
		{
		Rva002396F0TreeAccess::erase(
			(Rva002396F0FormationTree *)tree, node->right);
			Rva002396F0TreeNode *left = node->left;
			Gen0082E5F0(node, 0x18);
			node = left;
		}

		tree->header->left = (Rva002396F0TreeNode *)tree->header;
		tree->header->parent = 0;
		tree->header->right = (Rva002396F0TreeNode *)tree->header;
		tree->nodeCount = 0;
	}

	Object *first = TheBfmeGameLogic->findObjectByID(m_idA);
	Object *second = TheBfmeGameLogic->findObjectByID(m_idB);

	if (first != 0)
		first->clearAndSetModelConditionFlags(m_clearMaskA, BitFlags<320>());

	if (second != 0)
		second->clearAndSetModelConditionFlags(m_clearMaskA, BitFlags<320>());

	m_idA = 0;
}
