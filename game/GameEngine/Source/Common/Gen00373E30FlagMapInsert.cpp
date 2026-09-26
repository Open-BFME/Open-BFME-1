// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen00373E30Mask
{
	unsigned char m_pad00[0x0c];
	unsigned short m_flags;
};

struct Rva000A3F30Value
{
	char m_body[4];
	Rva000A3F30Value(int value)
	{
		*(int *)m_body = value;
	}
};

typedef _STL::pair<const int, Rva000A3F30Value> Gen00373E30Pair;
typedef _STL::_Rb_tree<int, Gen00373E30Pair,
	_STL::_Select1st<Gen00373E30Pair>, _STL::less<int>,
	_STL::allocator<Gen00373E30Pair> > Gen00373E30Tree;

class Gen_00373E30
{
public:
	void bfmeInsertMask(const Gen00373E30Mask *mask);

private:
	unsigned char m_pad00[0x108];
	Gen00373E30Tree m_map;
};

extern void *TheGameLogic;

void Gen_00373E30::bfmeInsertMask(const Gen00373E30Mask *mask)
{
	unsigned short flags = mask->m_flags;
	int index = 0;

	while (flags != 0)
	{
		if ((flags & 1) != 0)
		{
			Gen00373E30Pair value(index, Rva000A3F30Value(0));
			_STL::pair<Gen00373E30Tree::iterator, bool> result =
				m_map.insert_unique(value);
			*((int *)((unsigned char *)result.first._M_node + 0x14)) =
				*((int *)((unsigned char *)TheGameLogic + 0x3c));
		}
		flags >>= 1;
		++index;
	}
}
