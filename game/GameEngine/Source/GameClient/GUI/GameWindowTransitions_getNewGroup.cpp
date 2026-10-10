#include <stddef.h>
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

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

class BFMETransitionAsciiString
{
public:
	BFMETransitionAsciiString( const BFMETransitionAsciiString &other )
	{
		((AsciiString *)this)->AsciiString::AsciiString(
			*(const AsciiString *)&other );
	}
	~BFMETransitionAsciiString()
	{
		((AsciiString *)this)->AsciiString::~AsciiString();
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
private:
	char m_unmodelled[0x14];
};

class TransitionGroup;
class GameWindowTransitionsHandler
{
public:
	TransitionGroup *findGroup(AsciiString name);
};

class Gen00489B60
{
public:
	void bfmeSet(AsciiString name);
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
private:
	char m_unmodelled[0x1c];
	BFMETransitionGroupNode *m_groupHead;
};

BFMETransitionGroup *BFMETransitionHandler::getNewGroup( BFMETransitionAsciiString name )
{
	if ( name.isEmpty() )
		return 0;
	// ILT00024172 -> matched0048A520; the callee owns the outgoing string.
	if ( ((GameWindowTransitionsHandler *)this)->findGroup(
		*(const AsciiString *)&name ) != 0 )
		return 0;

	BFMETransitionGroup *group = new BFMETransitionGroup;
	// ILT0000F894 -> matched00489B60, also taking one string by value.
	((Gen00489B60 *)group)->bfmeSet( *(const AsciiString *)&name );

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
