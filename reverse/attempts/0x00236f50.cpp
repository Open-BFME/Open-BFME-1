// ?bfmeSlot00@Rva00236F50Interface@@QAEXXZ
// partial score=0.43 date=2026-09-22
// STLport red-black tree node base (verbatim, matches
// STLRbGlobalBoolIncrementThunk.cpp / vendor/stlport/stl/_tree.c).
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

}

extern "C" _STL::_Rb_tree_node_base *__cdecl
bfme_RbGlobalBoolIncrement_82B870(_STL::_Rb_tree_node_base *node);

#define BFME_SLOT(N) virtual void bfmeSlot##N()

class Rva00236F50ObjectView
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17);
	// slot 18, +0x48
	virtual void bfmeDefectionComplete();
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

struct Rva00236F50HashNode
{
	Rva00236F50HashNode *m_next;
	unsigned int m_key;
	Rva00236F50ObjectView *m_object;
};

class Rva00367E30Logic
{
public:
	char m_pad00[0xB4];
	Rva00236F50HashNode **m_hashBegin;
	Rva00236F50HashNode **m_hashEnd;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Rva00236F50Interface
{
public:
	void bfmeSlot00();

private:
	char m_pad00[0x18];
	Rva00236F50ListNode *m_listSentinel;
	char m_pad1C[0xF4 - 0x18 - 4];
	Rva00236F50TreeNode *m_treeHeader;
};

void Rva00236F50Interface::bfmeSlot00()
{
	{
		Rva00236F50ListNode *node = m_listSentinel->m_next;
		while (node != m_listSentinel)
		{
			node->m_value->bfmeDefectionComplete();
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
			unsigned int idCopy = id;
			Rva00367E30Logic *logic = TheBfmeGameLogic;
			unsigned int bucketCount = (unsigned int)(logic->m_hashEnd - logic->m_hashBegin);
			unsigned int bucket = idCopy % bucketCount;
			Rva00236F50HashNode *entry = logic->m_hashBegin[bucket];
			while (entry != 0)
			{
				if (entry->m_key == id)
				{
					if (entry->m_object != 0)
						entry->m_object->bfmeDefectionComplete();
					break;
				}
				entry = entry->m_next;
			}
		}

		node = (Rva00236F50TreeNode *)bfme_RbGlobalBoolIncrement_82B870(node);
		header = m_treeHeader;
	}
}
