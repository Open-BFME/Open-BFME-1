#include <stddef.h>

inline void *operator new( size_t, void *where ) { return where; }

// The group itself is a plain ::operator new (retail: push 0x14; call
// 0x00881F30), but the list node beside it comes from STLport's node pool:
// push 0xc; call 0x0082E540, __node_alloc<true,0>::_M_allocate, which buckets
// by (n-1)>>3 into the free-list array at 0x0130B1C0.  Shape copied from
// inputs/vendor/stlport/stl/_alloc.h, ternary included -- the node size is a constant
// under _MAX_BYTES, so it folds to the one direct call retail encodes.
void *__cdecl operator new( unsigned int );

namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	enum { _MAX_BYTES = 128 };
	static void *__cdecl _M_allocate( unsigned int __n );

public:
	static void *__cdecl allocate( unsigned int __n )
	{ return (__n > (unsigned int)_MAX_BYTES) ? ::operator new( __n ) : _M_allocate( __n ); }
};

typedef __node_alloc<true, 0> _Node_alloc;
}

template <typename T> class StringBase
{
friend class BFMETransitionAsciiString;
private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
};

class BFMETransitionAsciiString
{
public:
	BFMETransitionAsciiString( const BFMETransitionAsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other );
	}
	~BFMETransitionAsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	bool isEmpty() const
	{
		return m_data == 0 || *(unsigned short *)(m_data + 4) == 0;
	}
private:
	char *m_data;
};

class BFMETransitionGroup
{
public:
	BFMETransitionGroup();
	void setName( BFMETransitionAsciiString name );
private:
	char m_unmodelled[0x14];
};

struct BFMETransitionGroupNode
{
	BFMETransitionGroupNode *m_next;
	BFMETransitionGroupNode *m_previous;
	BFMETransitionGroup *m_value;
};

class BFMETransitionHandler
{
public:
	BFMETransitionGroup *getNewGroup( BFMETransitionAsciiString name );
	BFMETransitionGroup *findGroup( BFMETransitionAsciiString name );
private:
	char m_unmodelled[0x1c];
	BFMETransitionGroupNode *m_groupHead;
};

BFMETransitionGroup *BFMETransitionHandler::getNewGroup( BFMETransitionAsciiString name )
{
	if ( name.isEmpty() )
		return 0;
	if ( findGroup( name ) != 0 )
		return 0;

	BFMETransitionGroup *group = new BFMETransitionGroup;
	group->setName( name );

	BFMETransitionGroupNode *head = m_groupHead;
	BFMETransitionGroupNode *node = static_cast<BFMETransitionGroupNode *>(
		_STL::_Node_alloc::allocate( sizeof(BFMETransitionGroupNode) ) );
	new ( &node->m_value ) BFMETransitionGroup *( group );
	BFMETransitionGroupNode *previous = head->m_previous;
	node->m_previous = previous;
	node->m_next = head;
	previous->m_next = node;
	head->m_previous = node;
	return group;
}
