// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

// The ILT at RVA 0x000266BB is called by the named Rva002E8FC0 copy
// constructor for its +0x08 member.  Its body is the retail STLport vector
// copy constructor at RVA 0x002E7320.
#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

struct BfmeSortElem20TailElement
{
	int m_value;
	AsciiString m_name;
	char m_flag;
};

class BfmeSortElem20Tail
	: public _STL::_Vector_base<BfmeSortElem20TailElement,
		_STL::allocator<BfmeSortElem20TailElement> >
{
private:
	typedef BfmeSortElem20TailElement Element;
	typedef _STL::allocator<Element> Allocator;
	typedef _STL::_Vector_base<Element, Allocator> Base;

public:
	BfmeSortElem20Tail( const BfmeSortElem20Tail &other );
	~BfmeSortElem20Tail();

	unsigned int size() const
	{
		return (unsigned int)( this->_M_finish - this->_M_start );
	}

	Allocator get_allocator() const
	{
		return (const Allocator &)this->_M_end_of_storage;
	}
};

namespace _STL
{
	template <class InputIter, class ForwardIter>
	__forceinline ForwardIter __uninitialized_copy(
		InputIter first, InputIter last, ForwardIter result)
	{
		ForwardIter current = result;
		for( ; first != last; ++first, ++current )
			_Construct( &*current, *first );
		return current;
	}
}

BfmeSortElem20Tail::BfmeSortElem20Tail(
	const BfmeSortElem20Tail &other )
	: Base( other.size(), other.get_allocator() )
{
	this->_M_finish = _STL::__uninitialized_copy(
		other._M_start, other._M_finish, this->_M_start );
}
