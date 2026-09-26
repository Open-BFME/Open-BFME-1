// cl: /O2 /Oy /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

template <class Type> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const Type *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;
extern void bfmeGoDZFc( int value );

static void clearValue( int value )
{
	bfmeGoDZFc( value );
	if ( g_theWindowManager != 0 )
	{
		AsciiString name;
		name.format( AsciiString( "RegionUI/Portrait%d/Portrait" ), value );
		g_theWindowManager->_bfme_removeNamedAptGadget( name );
	}
}

namespace _STL
{

template <class Type> class allocator {};
template <class Type> struct _Identity {};
template <class Type> struct less {};

void nodeDeallocate( void *block, unsigned int bytes );

struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value m_value_field;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base *node );
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;
	unsigned int size() const { return m_node_count; }

	__forceinline void clear()
	{
		Node *node = (Node *)(void *)m_header->m_left;
		while ( node != m_header )
		{
			clearValue( node->m_value_field.m_pod );
			node = (Node *)_Rb_global<bool>::_M_increment( node );
		}

		if ( m_node_count != 0 )
		{
			node = (Node *)(void *)m_header->m_parent;
			while ( node != 0 )
			{
				_M_erase( (Node *)(void *)node->m_right );
				Node *left = (Node *)(void *)node->m_left;
				nodeDeallocate( node, sizeof( Node ) );
				node = left;
			}
			m_header->m_left = m_header;
			m_header->m_parent = 0;
			m_header->m_right = m_header;
			m_node_count = 0;
		}
	}

	__forceinline void eraseRoot( Node *node )
	{
		_M_erase( node );
	}

private:
	void _M_erase( Node *node );

public:
	_Rb_tree_node_base *m_header;
	unsigned int m_node_count;
	Compare m_key_compare;
};

}

struct Gen_t_00234730_m4pod
{
	int m_pod;
};

class CampaignObject
{
public:
	unsigned char m_pad[0x2c];
	bool m_flag2c;
	bool m_flag2d;
};

extern CampaignObject *TheLivingWorldLogic;

typedef _STL::_Rb_tree<
	Gen_t_00234730_m4pod,
	Gen_t_00234730_m4pod,
	_STL::_Identity<Gen_t_00234730_m4pod>,
	_STL::less<Gen_t_00234730_m4pod>,
	_STL::allocator<Gen_t_00234730_m4pod> > AptPalantirStoreTree;

class AptPalantirStoreUpdateTree
{
public:
	typedef AptPalantirStoreTree::Node Node;

	__forceinline void clear()
	{
		AptPalantirStoreTree *tree =
			reinterpret_cast<AptPalantirStoreTree *>( this );
		Node *node = (Node *)(void *)tree->m_header->m_left;
		while ( node != tree->m_header )
		{
			clearValue( node->m_value_field.m_pod );
			node = (Node *)_STL::_Rb_global<bool>::_M_increment( node );
		}

		if ( tree->m_node_count != 0 )
		{
			tree->eraseRoot( (Node *)(void *)tree->m_header->m_parent );
			tree->m_header->m_left = tree->m_header;
			tree->m_header->m_parent = 0;
			tree->m_header->m_right = tree->m_header;
			tree->m_node_count = 0;
		}
	}
};

class AptPalantirStore
{
public:
	void clear();
	void rva00591b60();

private:
	unsigned int m_value00;
	unsigned char m_flag04;
	unsigned char m_padding05[ 3 ];
	int m_value08;
	int m_value0c;
	AptPalantirStoreTree m_firstTree;
	AptPalantirStoreTree m_secondTree;
};

void AptPalantirStore::clear()
{
	if ( m_value08 != 0 )
	{
		clearValue( m_value0c );
		m_value08 = 0;
	}

	m_firstTree.clear();
	m_secondTree.clear();
	m_value00 = 0;
	m_flag04 = false;
}

void AptPalantirStore::rva00591b60()
{
	if ( !m_flag04 )
		return;

	CampaignObject *campaign = TheLivingWorldLogic;
	if ( campaign == 0 || !campaign->m_flag2c || !campaign->m_flag2d )
	{
		clear();
		return;
	}

	reinterpret_cast<AptPalantirStoreUpdateTree *>( &m_secondTree )->clear();

	union NotEmpty
	{
		int value;
		unsigned char byte;
	} notEmpty;
	notEmpty.value = ( m_value08 != 0 ) || ( m_firstTree.size() != 0 );
	m_flag04 = notEmpty.byte;
	if ( !notEmpty.byte )
		m_value00 = 0;
}
