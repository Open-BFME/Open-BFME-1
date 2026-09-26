// ?resize@?$vector@URva00244A80Element@@V?$allocator@URva00244A80Element@@@_STL@@@_STL@@QAEXIURva00244A80Element@@@Z
// partial score=0.95 date=2026-09-08
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: STLport vector<Rva00244A80Element>::resize, retail 0x00246850.
// The shrink copy and growth fill calls identify the existing 28-byte element
// family at 0x00233A20 and 0x002403E0.

struct Rva00244A80Element
{
	int m_words[7];
};

namespace _STL
{
	struct random_access_iterator_tag
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class InputIterator, class OutputIterator, class Distance>
	OutputIterator __copy(InputIterator first, InputIterator last,
		OutputIterator result, const random_access_iterator_tag &, Distance *);

	template <class Type, class Allocator>
	class vector
	{
	public:
		Type *begin() { return _M_start; }
		Type *end() { return _M_finish; }
		int size()
		{
			return (unsigned int)(_M_finish - _M_start);
		}

		void resize(unsigned int newSize, Type value);
		void _M_fill_insert(Type *pos, unsigned int n, const Type &value);

	private:
		Type *_M_start;
		Type *_M_finish;
		Type *_M_end_of_storage;
	};

	template <class Type, class Allocator>
	void vector<Type, Allocator>::resize(unsigned int newSize, Type value)
	{
		if (newSize < size())
		{
			Type *destination = begin() + newSize;
			random_access_iterator_tag tag;
			_M_finish = __copy(end(), end(), destination, tag, (int *)0);
		}
		else
		{
			_M_fill_insert(end(), newSize - size(), value);
		}
	}

	template void vector<Rva00244A80Element,
		allocator<Rva00244A80Element> >::resize(unsigned int,
		Rva00244A80Element);
}
