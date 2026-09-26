// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

enum ScienceType
{
	Rva003C2720ScienceType = 0
};

namespace _STL
{
template <class Type, class Allocator>
class public_vector : public vector<Type, Allocator>
{
public:
	using vector<Type, Allocator>::_M_start;
	using vector<Type, Allocator>::_M_finish;
	using vector<Type, Allocator>::_M_end_of_storage;
	using vector<Type, Allocator>::_M_insert_overflow;
};
}

class Rva003C2720Owner
{
public:
	void copy(const _STL::vector<ScienceType> *source);

private:
	char m_pad00[0x94];
	_STL::public_vector<ScienceType, _STL::allocator<ScienceType> > m_sciences;
};

void Rva003C2720Owner::copy(const _STL::vector<ScienceType> *source)
{
	_STL::public_vector<ScienceType, _STL::allocator<ScienceType> > &destination =
		m_sciences;
	destination.clear();

	const _STL::public_vector<ScienceType, _STL::allocator<ScienceType> > *sourceAccess =
		(const _STL::public_vector<ScienceType, _STL::allocator<ScienceType> > *)source;

	ScienceType *sourceFirst = sourceAccess->_M_start;
	ScienceType *sourceLast = sourceAccess->_M_finish;
	unsigned int sourceCount = (unsigned int)(sourceLast - sourceFirst);
	unsigned int index = 0;
	while (index < sourceCount)
	{
		ScienceType *value = sourceFirst + index;
		ScienceType *position = destination._M_finish;
		if (position != destination._M_end_of_storage._M_data)
		{
			if (position != 0)
				*position = *value;
			++destination._M_finish;
		}
		else
		{
			destination._M_insert_overflow(position, *value,
				reinterpret_cast<const _STL::__false_type &>(source), 1, true);
		}
		++index;
		sourceFirst = sourceAccess->_M_start;
		sourceLast = sourceAccess->_M_finish;
		sourceCount = (unsigned int)(sourceLast - sourceFirst);
	}
}
