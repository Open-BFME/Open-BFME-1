// ?d_00426c60@@YAXXZ
// partial score=0.46 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// Address-derived Eva event parser; its branch tables and record ABI are read from retail.

#include "ascii_string.h"

typedef int Int;

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *object, const FieldParse *fieldParse );
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	void releaseBuffer();
	char *m_data;
};

class INIException
{
public:
	INIException( Int code, const char *message, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_message;
};

namespace _STL
{
template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	T1 first;
	T2 second;

	pair( const T1 &left, const T2 &right ) : first( left ), second( right ) {}
};

template <class T> struct allocator {};
template <class T> struct less {};

template <class T>
struct _Select1st
{
	const typename T::first_type &operator()( const T &value ) const;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	~_Rb_tree();

private:
	char m_raw[ 12 ];
};

template <class Value>
struct _Hashtable_node
{
	_Hashtable_node<Value> *m_next;
	Value m_val;
};

template <class Value, class Key, class HashFcn, class ExtractKey,
	class EqualKey, class Alloc>
class hashtable;

template <class Value>
struct _Nonconst_traits
{
	typedef Value &reference;
	typedef Value *pointer;
};

template <class Value, class Traits, class Key, class HashFcn,
	class ExtractKey, class EqualKey, class Alloc>
struct _Ht_iterator
{
	typedef _Hashtable_node<Value> _Node;
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> _Hashtable;

	_Node *m_cur;
	_Hashtable *m_ht;

	_Ht_iterator( _Node *node, _Hashtable *table ) : m_cur( node ), m_ht( table ) {}
};

template <class Value, class Key, class HashFcn, class ExtractKey,
	class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;
	typedef _Ht_iterator<Value, _Nonconst_traits<Value>, Key, HashFcn, ExtractKey, EqualKey, Alloc>
		iterator;

	const _Node *find( const Key &key ) const
	{
		return _M_find( key );
	}

	_STL::pair<iterator, bool> insert_unique_noresize( const Value &value );
	void resize( unsigned int count );

	char m_buckets[ 16 ];
	unsigned int m_num_elements;

private:
	template <class KT>
	_Node *_M_find( const KT &key ) const;
};
}

namespace rts
{
template <class T> struct hash;
template <class T> struct equal_to;
}

struct Rva004246F0Value
{
	AsciiString m_key;
	Int m_message;
};

struct Rva004246F0ExtractKey
{
	const AsciiString &operator()( const Rva004246F0Value &value ) const
	{
		return value.m_key;
	}
};

typedef _STL::hashtable<Rva004246F0Value, AsciiString,
	rts::hash<AsciiString>, Rva004246F0ExtractKey,
	rts::equal_to<AsciiString>, _STL::allocator<Rva004246F0Value> >
	Rva00426C60NameMap;

struct Rva00424D30Value
{
	int m_payload;
};

typedef _STL::pair<const AsciiString, Rva00424D30Value *> Rva00424D30Pair;

struct Rva00424D30ExtractKey
{
	const AsciiString &operator()( const Rva00424D30Pair &value ) const
	{
		return value.first;
	}
};

typedef _STL::hashtable<Rva00424D30Pair, AsciiString,
	rts::hash<AsciiString>, Rva00424D30ExtractKey,
	rts::equal_to<AsciiString>, _STL::allocator<Rva00424D30Pair> >
	Rva00426C60InsertMap;

struct Rva004240F0Value
{
	unsigned int m_payload;
};

typedef _STL::pair<const AsciiString, Rva004240F0Value *> Rva004240F0Pair;

typedef _STL::hashtable<Rva004240F0Pair, AsciiString,
	rts::hash<AsciiString>, _STL::_Select1st<Rva004240F0Pair>,
	rts::equal_to<AsciiString>, _STL::allocator<Rva004240F0Pair> >
	Rva00426C60ResizeMap;

struct Gen00425060
{
	char m_body[ 28 ];
	~Gen00425060();
};

class Rva00425680Object : public Gen00425060
{
public:
	Rva00425680Object();
};

struct Rva00426C00Element
{
	char m_body[ 28 ];
};

struct Gen_t_004258e0_p24cd
{
	char m_body[ 24 ];
};

namespace _STL
{
template <class Type, class Allocator>
class vector;

template <>
class vector<Rva00426C00Element, allocator<Rva00426C00Element> >
{
public:
	void push_back( const Rva00426C00Element *value );
	Rva00426C00Element *m_begin;
	Rva00426C00Element *m_finish;
	Rva00426C00Element *m_end_of_storage;
};

template <>
class vector<Gen_t_004258e0_p24cd, allocator<Gen_t_004258e0_p24cd> >
{
public:
	void push_back( const Gen_t_004258e0_p24cd &value );
	Gen_t_004258e0_p24cd *m_begin;
	Gen_t_004258e0_p24cd *m_finish;
	Gen_t_004258e0_p24cd *m_end_of_storage;
};
}

class Eva;
extern Eva *TheEva;

class Rva00426C60EvaEvent
{
public:
	static void parse( INI *ini );
};

void Rva00426C60EvaEvent::parse( INI *ini )
{
	const char *token = ini->getNextToken( 0 );
	BFMERetailAsciiString name( token );
	if ( ( (AsciiString *)&name )->compareNoCase( "None" ) == 0 )
		throw INIException( 3,
			"Cannot use 'None' as a new Eva event's name" );

	const Int loadType = *(const Int *)((const char *)ini + 8);
	if ( loadType == 2 )
	{
		const _STL::_Hashtable_node<Rva004246F0Value> *found =
			reinterpret_cast<Rva00426C60NameMap *>( (char *)TheEva + 0x24 )->find(
			*(const AsciiString *)&name );
		Int index = found ? found->m_val.m_message : -1;
		if ( index != -1 )
		{
			if ( index < 0x11 )
				throw INIException( 3,
					"'%s' is a predefined Eva event name, and cannot be used as a new",
					name.str() );
			Rva00426C00Element *destination =
				reinterpret_cast<_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *>( (char *)TheEva + 0x0c )->m_begin
				+ index;
			ini->initFromINI( destination, (const FieldParse *)0x010F1B68 );
			return;
		}

		{
			Rva00425680Object value;
			_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *messages =
				reinterpret_cast<_STL::vector<Rva00426C00Element,
					_STL::allocator<Rva00426C00Element> > *>( (char *)TheEva + 0x0c );
			index = (Int)( messages->m_finish - messages->m_begin );
			messages->push_back( (const Rva00426C00Element *)&value );
		}
		{
			Rva00424D30Pair value( *(const AsciiString *)&name,
				(Rva00424D30Value *)(unsigned long)index );
			Rva00426C60ResizeMap *resizeMap =
				reinterpret_cast<Rva00426C60ResizeMap *>( (char *)TheEva + 0x24 );
			resizeMap->resize( resizeMap->m_num_elements + 1 );
			reinterpret_cast<Rva00426C60InsertMap *>( (char *)TheEva + 0x24 )
				->insert_unique_noresize( value );
		}
		Gen_t_004258e0_p24cd check;
		*(float *)( check.m_body + 0 ) = -1.0f;
		*(float *)( check.m_body + 4 ) = -1.0f;
		*( check.m_body + 0x14 ) = 0;
		reinterpret_cast<_STL::vector<Gen_t_004258e0_p24cd,
			_STL::allocator<Gen_t_004258e0_p24cd> > *>( (char *)TheEva + 0x4c )
			->push_back( check );
		Rva00426C00Element *destination =
		reinterpret_cast<_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *>( (char *)TheEva + 0x0c )->m_begin
			+ index;
		ini->initFromINI( destination, (const FieldParse *)0x010F1B68 );
	}
	else
	{
		const _STL::_Hashtable_node<Rva004246F0Value> *found =
			reinterpret_cast<Rva00426C60NameMap *>( (char *)TheEva + 0x38 )->find(
			*(const AsciiString *)&name );
		if ( found != 0 )
		{
			if ( found->m_val.m_message < 0x11 )
				throw INIException( 3,
					"'%s' is a predefined Eva event name, and cannot be used as a new",
					name.str() );
			throw INIException( 3,
				"Cannot redefine existing Eva event '%s' in Eva.ini",
				name.str() );
		}

		Int index;
		{
			Rva00425680Object value;
			_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *messages =
				reinterpret_cast<_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *>( (char *)TheEva + 0x18 );
			index = (Int)( messages->m_finish - messages->m_begin );
			messages->push_back( (const Rva00426C00Element *)&value );
		}
		{
			Rva00424D30Pair value( *(const AsciiString *)&name,
				(Rva00424D30Value *)(unsigned long)index );
			Rva00426C60ResizeMap *resizeMap =
				reinterpret_cast<Rva00426C60ResizeMap *>( (char *)TheEva + 0x38 );
			resizeMap->resize( resizeMap->m_num_elements + 1 );
			reinterpret_cast<Rva00426C60InsertMap *>( (char *)TheEva + 0x38 )
				->insert_unique_noresize( value );
		}
		Gen_t_004258e0_p24cd check;
		*(float *)( check.m_body + 0 ) = -1.0f;
		*(float *)( check.m_body + 4 ) = -1.0f;
		*( check.m_body + 0x14 ) = 0;
		reinterpret_cast<_STL::vector<Gen_t_004258e0_p24cd,
			_STL::allocator<Gen_t_004258e0_p24cd> > *>( (char *)TheEva + 0x4c )
			->push_back( check );
		Rva00426C00Element *destination =
			reinterpret_cast<_STL::vector<Rva00426C00Element,
				_STL::allocator<Rva00426C00Element> > *>( (char *)TheEva + 0x18 )->m_begin
			+ index;
		ini->initFromINI( destination, (const FieldParse *)0x010F1B68 );
	}
}
