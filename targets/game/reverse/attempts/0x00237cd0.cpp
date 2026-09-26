// ?d_00237cd0@@YAXXZ
// partial score=0.3140495868 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <set>

struct Rva00237CD0HashEntry
{
	Rva00237CD0HashEntry *m_next;
	unsigned int m_04;
	void *m_08;
};

struct Rva00237CD0BucketOwner
{
	char m_pad00[0xB4];
	Rva00237CD0HashEntry **m_bucketBegin;
	Rva00237CD0HashEntry **m_bucketEnd;
};

// The retail operand at 0x00237CE7 addresses this data pointer at VA
// 0x012F0898. Its address is witnessed; the original global name is not.
extern Rva00237CD0BucketOwner * volatile g_rva00237cd0_012f0898;

struct Rva00237CD0TreeNode : _STL::_Rb_tree_node<unsigned int>
{
};

struct Rva00237CD0Owner
{
	char m_pad00[0x30];
	_STL::_Rb_tree_node_base *m_30;

	bool _bfme_rva00237CD0();
};

bool Rva00237CD0Owner::_bfme_rva00237CD0()
{
	_STL::_Rb_tree_node_base *header = m_30;
	Rva00237CD0TreeNode *node = reinterpret_cast<Rva00237CD0TreeNode *>(
		header->_M_left);
	for (; node != reinterpret_cast<Rva00237CD0TreeNode *>(m_30);
		node = reinterpret_cast<Rva00237CD0TreeNode *>(
			_STL::_Rb_global<bool>::_M_increment(
				reinterpret_cast<_STL::_Rb_tree_node_base *>(node))))
	{
		unsigned int id = node->_M_value_field;
		if (id != 0)
		{
			Rva00237CD0BucketOwner *bucketOwner = g_rva00237cd0_012f0898;
			Rva00237CD0HashEntry **bucketBegin = bucketOwner->m_bucketBegin;
			Rva00237CD0HashEntry **bucketEnd = bucketOwner->m_bucketEnd;
			unsigned int bucketCount =
				static_cast<unsigned int>(bucketEnd - bucketBegin);
			Rva00237CD0HashEntry *entry = bucketBegin[id % bucketCount];
			while (entry != 0 && entry->m_04 != id)
				entry = entry->m_next;
			if (entry != 0 && entry->m_08 != 0)
				return true;
		}
	}
	return false;
}
