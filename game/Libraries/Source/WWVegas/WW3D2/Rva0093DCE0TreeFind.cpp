// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "Rva0093DCE0TreeFind.h"

// Only the node prefix read by this routine is modeled. No mapped value
// field or complete node allocation size is inferred from these bytes.
struct Rva0093DCE0Node
{
	unsigned int m_uninterpreted00;
	Rva0093DCE0Node *m_parent;
	Rva0093DCE0Node *m_left;
	Rva0093DCE0Node *m_right;
	unsigned short m_key;
};

Rva0093DCE0Node *Rva0093DCE0Tree::find(const unsigned short &key) const
{
	Rva0093DCE0Node *result = m_header;
	Rva0093DCE0Node *node = m_header->m_parent;
	while (node != 0)
	{
		if (!(node->m_key < key))
		{
			result = node;
			node = node->m_left;
		}
		else
			node = node->m_right;
	}
	return result == m_header || key < result->m_key ? m_header : result;
}
