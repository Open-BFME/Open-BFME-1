// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Four __thiscall members that take ONE pointer argument and do nothing but call
// a run of VIRTUAL slots on it, each time handing it the address of a member of
// this object:
//
//     mov esi,[esp+8] / mov eax,[esi] / mov edi,ecx
//     lea ecx,[edi+4] / push ecx / mov ecx,esi / call [eax+0x74]
//     mov edx,[esi] / lea eax,[edi+8] / push eax / mov ecx,esi
//     call [edx+0x8C] / ...
//
// WHAT THE BYTES SHOW.  The argument is reloaded into ecx before every call and
// its vftable is re-read from [esi] before every call, so each call is a virtual
// __thiscall on the SAME receiver -- the argument -- and the compiler could not
// prove the vptr survives, which is what a call through an opaque interface
// looks like.  What is pushed is always `lea` of an interior address, never a
// value: these are OUT/IN-OUT parameters, one member of this object per call.
//
// THE SLOT NUMBERS ARE OPERANDS, not inference: 0x74, 0x8C, 0x68, 0x60 and 0x6C
// appear literally in the `call [reg+K]` displacements, so the receiver's class
// is declared with 36 virtual functions purely to place those five at those
// displacements.  All four rows open with the same two calls -- slot 0x74 on the
// member at +4 and slot 0x8C on the member at +8 -- and then diverge; none of
// them calls another of them, so they are four separate classes that happen to
// share a two-field prefix, not a base and three overrides.
//
// TWO ROWS LEAVE THE INTERFACE for one step.  0x003BB8F0 pushes the member
// address AND the interface pointer and cleans up eight bytes itself, so that
// one is a __cdecl free function taking both; 0x003BBA40 sets ecx to a member
// address and pushes the interface, so that one is a __thiscall member of the
// member at +0xC.  Both then continue on the interface.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the two
// non-virtual callee pins are address-derived and additive.

class GenXferInterface
{
public:
	virtual void slot00( void * field );
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot0C( void * field );
	virtual void slot10( void * field );
	virtual void slot14( void * field );
	virtual void slot18( void * field );
	virtual void slot1C( void * field );
	virtual void slot20( void * field );
	virtual void slot24( void * field );
	virtual void slot28( void * field );
	virtual void slot2C( void * field );
	virtual void slot30( void * field );
	virtual void slot34( void * field );
	virtual void slot38( void * field );
	virtual void slot3C( void * field );
	virtual void slot40( void * field );
	virtual void slot44( void * field );
	virtual void slot48( void * field );
	virtual void slot4C( void * field );
	virtual void slot50( void * field );
	virtual void slot54( void * field );
	virtual void slot58( void * field );
	virtual void slot5C( void * field );
	virtual void slot60( void * field );
	virtual void slot64( void * field );
	virtual void slot68( void * field );
	virtual void slot6C( void * field );
	virtual void slot70( void * field );
	virtual void slot74( void * field );
	virtual void slot78( void * field );
	virtual void slot7C( void * field );
	virtual void slot80( void * field );
	virtual void slot84( void * field );
	virtual void slot88( void * field );
	virtual void slot8C( void * field );
};

class Gen003BB8F0Member;

class Rva00064390
{
public:
	Rva00064390();

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	int m_18;
};

struct Gen_t_000648f0_p24pod
{
	int a[ 6 ];
};

namespace _STL
{
	template <class First, class Second>
	struct pair
	{
		pair( void )
		{
		}

		pair( const First & firstValue, const Second & secondValue )
			: first( firstValue ), second( secondValue )
		{
		}

		First first;
		Second second;
	};

	template <class Pair>
	struct _Select1st
	{
	};

	template <class Type>
	struct less
	{
	};

	template <class Type>
	class allocator
	{
	};

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

	template <class Threads>
	struct _Rb_global
	{
		static _Rb_tree_node_base *_M_increment( _Rb_tree_node_base * node );
	};

	struct Gen003BBA40Iterator
	{
		Gen003BBA40Iterator( _Rb_tree_node_base * node ) : m_node( node )
		{
		}

		Rva00064390 &operator *( void ) const
		{
			return *(Rva00064390 *)( (char *)m_node + 0x10 );
		}

		Gen003BBA40Iterator &operator ++( void )
		{
			m_node = _Rb_global<bool>::_M_increment( m_node );
			return *this;
		}

		bool operator !=( const Gen003BBA40Iterator & that ) const
		{
			return m_node != that.m_node;
		}

		_Rb_tree_node_base *m_node;
	};

	typedef pair<const int, Gen_t_000648f0_p24pod> Gen003BBA40Value;

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
	public:
		typedef Gen003BBA40Iterator iterator;
		typedef Value value_type;
		typedef pair<iterator, bool> InsertResult;

		unsigned int size( void ) const
		{
			return m_node_count;
		}

		iterator begin( void )
		{
			return iterator( m_header->m_left );
		}

		iterator end( void )
		{
			return iterator( m_header );
		}

		__forceinline void clear( void )
		{
			if ( m_node_count != 0 )
			{
				_M_erase( (_Node *)(void *)_M_root() );
				_M_leftmost() = m_header;
				_M_root() = 0;
				_M_rightmost() = m_header;
				m_node_count = 0;
			}
		}

		InsertResult insert_unique( const Value & value );

	private:
		typedef _Rb_tree_node<Value> _Node;

		_Rb_tree_node_base *&_M_root( void ) const
		{
			return m_header->m_parent;
		}

		_Rb_tree_node_base *&_M_leftmost( void ) const
		{
			return m_header->m_left;
		}

		_Rb_tree_node_base *&_M_rightmost( void ) const
		{
			return m_header->m_right;
		}

		void _M_erase( _Node * node );

		_Rb_tree_node_base *m_header;
		unsigned int m_node_count;
		Compare m_key_compare;
	};
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, Gen_t_000648f0_p24pod>,
	_STL::_Select1st<_STL::pair<const int, Gen_t_000648f0_p24pod> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int,
	Gen_t_000648f0_p24pod> > > Gen003BBA40Tree;

class Gen003BBA40Member : public Gen003BBA40Tree
{
public:
	void step( GenXferInterface * xfer );
};

void Gen003BBA40Member::step( GenXferInterface * xfer )
{
	if ( xfer->isSaving() )
	{
		int count = size();
		xfer->slot78( &count );

		for ( iterator it = begin(); it != end(); ++it )
		{
			Rva00064390 * value = &*it;
			xfer->slot60( &value->m_00 );
			xfer->slot6C( &value->m_0C );
			xfer->slot6C( &value->m_10 );
			xfer->slot6C( &value->m_14 );
			xfer->slot74( &value->m_18 );
		}
	}
	else if ( xfer->isLoading() )
	{
		int count;
		xfer->slot78( &count );
		if ( size() != 0 )
			clear();

		Rva00064390 value;
		for ( int i = 0; i < count; ++i )
		{
			xfer->slot60( &value.m_00 );
			xfer->slot6C( &value.m_0C );
			xfer->slot6C( &value.m_10 );
			xfer->slot6C( &value.m_14 );
			xfer->slot74( &value.m_18 );
			insert_unique( *(Gen003BBA40Tree::value_type *) &value );
		}
	}
}

void Gen003BB8F0Free( GenXferInterface * xfer, void * field );

class Rva003BB8F0
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
};
void Rva003BB8F0::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	Gen003BB8F0Free( x, &m_at0C );
}

class Rva003BB930
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
};
void Rva003BB930::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	x->slot68( &m_at0C );
}

class Rva003BBA40
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	char m_pad0C[ 0xC ];
	int  m_at18;
};
void Rva003BBA40::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	( (Gen003BBA40Member *)( (char *)this + 0xC ) )->step( x );
	x->slot74( &m_at18 );
}

class Rva003BB9A0
{
public:
	void xfer( GenXferInterface * x );
	char m_pad00[ 0x4 ];
	int  m_at04;
	int  m_at08;
	int  m_at0C;
	char m_pad10[ 0x8 ];
	int  m_at18;
	int  m_at1C;
};
void Rva003BB9A0::xfer( GenXferInterface * x )
{
	x->slot74( &m_at04 );
	x->slot8C( &m_at08 );
	x->slot60( &m_at0C );
	x->slot6C( &m_at18 );
	x->slot74( &m_at1C );
}
