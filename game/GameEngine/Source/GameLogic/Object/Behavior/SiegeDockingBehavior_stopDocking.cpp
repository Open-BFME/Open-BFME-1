// cl: /DNDEBUG /MD /EHsc

// SiegeDockingBehavior::stopDocking, retail 0x00206710. Delete every entry the
// behaviour is holding, then empty the vector.
//
// The vector is at +0x24 and is spelled locally for the same reason the resize
// family is: the loop walks _M_start to _M_finish deleting through the global
// operator delete behind an explicit null test - so the element type has no
// destructor of its own, and the test is in the source, since delete alone
// compiles to the bare call - and
// clear() goes through erase(begin(), end()), whose copy is trivial and whose
// guard is decided on the POINTERS. That is the dead cmp eax,eax and the
// memmove of a length that is always zero, the same shape the vector resizes
// carry.

extern "C" void *(__cdecl *bfme_memmove_ptr)( void *, const void *, unsigned int );
#define memmove (*bfme_memmove_ptr)

class BfmeSiegeDockEntry
{
private:
	unsigned int m_unmodelled_00;
};

namespace _STL
{

template < class Type >
class allocator
{
};

template < class Type >
inline Type *__copy_trivial( Type *first, Type *last, Type *result )
{
	if( first == last )
		return result;

	unsigned int n = (unsigned int)( (const char *)last - (const char *)first );

	return (Type *)( (char *)memmove( result, first, n ) + n );
}

template < class Type, class Allocator >
class vector
{
public:
	Type *begin()
	{
		return _M_start;
	}

	Type *end()
	{
		return _M_finish;
	}

	Type *erase( Type *first, Type *last )
	{
		Type *i = __copy_trivial( last, _M_finish, first );

		_M_finish = i;

		return first;
	}

	void clear()
	{
		erase( begin(), end() );
	}

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

}

class SiegeDockingBehavior
{
private:
	void stopDocking();

	unsigned char m_unmodelled_00[ 0x24 ];
	_STL::vector< BfmeSiegeDockEntry *, _STL::allocator< BfmeSiegeDockEntry * > > m_entries;	// +0x24
};

// ?stopDocking@SiegeDockingBehavior@@AAEXXZ
void SiegeDockingBehavior::stopDocking()
{
	for( BfmeSiegeDockEntry **it = m_entries.begin(); it != m_entries.end(); ++it )
	{
		if( *it )
			delete *it;
	}

	m_entries.clear();
}
