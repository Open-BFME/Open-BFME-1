// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport vector<T>::_M_allocate_and_copy, 23 bodies of 97 bytes.
// Every one carried only a machine byte-dump row; the same shape is already
// converted at 0x0076B3B0, 0x003B5E20 and 0x003B6460.
//
// Allocate room for the count it is given -- through the large allocator above
// 128 bytes and the small one below -- then walk the source range copying one
// element at a time into it, at a constant offset from the source pointer that
// the compiler hoists out of the loop.
//
// The element width is the multiply in front of the allocation and it is the
// same multiply the loop strides by.  `lea eax,[eax+eax*4]` then `shl eax,2` is
// twenty bytes; `lea eax,[eax+eax*8]` then `shl eax,2` is thirty-six.  Seven
// widths appear in all: 12, 20, 24, 36, 40, 48 and the loop stride confirms
// each one.  Beyond
// its width nothing here names the element -- the per-element copy is a call --
// so each is a byte array named for the address of the body.
//
// The copy helper is deliberately NOT spelled _STL::_Construct: giving it its
// own name lets each of these call sites pin to its own ILT without disturbing
// the _Construct name the ledger already pins elsewhere.

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

template <class Type>
void __cdecl BfmeElementConstruct(void *destination, const Type &value);

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(
	unsigned int count, Iterator first, Iterator last)
{
	Type *result;
	if (count)
	{
		unsigned int bytes = count * sizeof(Type);
		if (bytes > 128)
			result = (Type *)vectorLargeAllocate(bytes);
		else
			result = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	if (first != last)
	{
		int offset = (char *)result - (char *)first;
		do
		{
			BfmeElementConstruct((Type *)((char *)first + offset), *first);
			++first;
		}
		while (first != last);
	}
	return result;
}

}

struct Rva00136330Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x00136330, a 20-byte element
template Rva00136330Element *vector<Rva00136330Element, allocator<Rva00136330Element> >::
	_M_allocate_and_copy<const Rva00136330Element *>(
		unsigned int, const Rva00136330Element *, const Rva00136330Element *);

}

struct Rva00355320Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x00355320, a 20-byte element
template Rva00355320Element *vector<Rva00355320Element, allocator<Rva00355320Element> >::
	_M_allocate_and_copy<const Rva00355320Element *>(
		unsigned int, const Rva00355320Element *, const Rva00355320Element *);

}

struct Rva003553A0Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x003553A0, a 20-byte element
template Rva003553A0Element *vector<Rva003553A0Element, allocator<Rva003553A0Element> >::
	_M_allocate_and_copy<const Rva003553A0Element *>(
		unsigned int, const Rva003553A0Element *, const Rva003553A0Element *);

}

struct Rva003B4F00Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x003B4F00, a 20-byte element
template Rva003B4F00Element *vector<Rva003B4F00Element, allocator<Rva003B4F00Element> >::
	_M_allocate_and_copy<const Rva003B4F00Element *>(
		unsigned int, const Rva003B4F00Element *, const Rva003B4F00Element *);

}

struct Rva003B4F80Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x003B4F80, a 20-byte element
template Rva003B4F80Element *vector<Rva003B4F80Element, allocator<Rva003B4F80Element> >::
	_M_allocate_and_copy<const Rva003B4F80Element *>(
		unsigned int, const Rva003B4F80Element *, const Rva003B4F80Element *);

}

struct Rva0076B330Element
{
	unsigned char m_body[ 20 ];
};

namespace _STL
{
// retail 0x0076B330, a 20-byte element
template Rva0076B330Element *vector<Rva0076B330Element, allocator<Rva0076B330Element> >::
	_M_allocate_and_copy<const Rva0076B330Element *>(
		unsigned int, const Rva0076B330Element *, const Rva0076B330Element *);

}

struct Rva000FD960Element
{
	unsigned char m_body[ 36 ];
};

namespace _STL
{
// retail 0x000FD960, a 36-byte element
template Rva000FD960Element *vector<Rva000FD960Element, allocator<Rva000FD960Element> >::
	_M_allocate_and_copy<const Rva000FD960Element *>(
		unsigned int, const Rva000FD960Element *, const Rva000FD960Element *);

}

struct Rva00138CC0Element
{
	unsigned char m_body[ 36 ];
};

namespace _STL
{
// retail 0x00138CC0, a 36-byte element
template Rva00138CC0Element *vector<Rva00138CC0Element, allocator<Rva00138CC0Element> >::
	_M_allocate_and_copy<const Rva00138CC0Element *>(
		unsigned int, const Rva00138CC0Element *, const Rva00138CC0Element *);

}

struct Rva003B6020Element
{
	unsigned char m_body[ 36 ];
};

namespace _STL
{
// retail 0x003B6020, a 36-byte element
template Rva003B6020Element *vector<Rva003B6020Element, allocator<Rva003B6020Element> >::
	_M_allocate_and_copy<const Rva003B6020Element *>(
		unsigned int, const Rva003B6020Element *, const Rva003B6020Element *);

}

struct Rva000E7F90Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x000E7F90, a 12-byte element
template Rva000E7F90Element *vector<Rva000E7F90Element, allocator<Rva000E7F90Element> >::
	_M_allocate_and_copy<const Rva000E7F90Element *>(
		unsigned int, const Rva000E7F90Element *, const Rva000E7F90Element *);

}

struct Rva00135C90Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x00135C90, a 12-byte element
template Rva00135C90Element *vector<Rva00135C90Element, allocator<Rva00135C90Element> >::
	_M_allocate_and_copy<const Rva00135C90Element *>(
		unsigned int, const Rva00135C90Element *, const Rva00135C90Element *);

}

struct Rva001508E0Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x001508E0, a 12-byte element
template Rva001508E0Element *vector<Rva001508E0Element, allocator<Rva001508E0Element> >::
	_M_allocate_and_copy<const Rva001508E0Element *>(
		unsigned int, const Rva001508E0Element *, const Rva001508E0Element *);

}

struct Rva001A6E50Element
{
	unsigned char m_body[ 48 ];
};

namespace _STL
{
// retail 0x001A6E50, a 48-byte element
template Rva001A6E50Element *vector<Rva001A6E50Element, allocator<Rva001A6E50Element> >::
	_M_allocate_and_copy<const Rva001A6E50Element *>(
		unsigned int, const Rva001A6E50Element *, const Rva001A6E50Element *);

}

struct Rva001E4E50Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x001E4E50, a 12-byte element
template Rva001E4E50Element *vector<Rva001E4E50Element, allocator<Rva001E4E50Element> >::
	_M_allocate_and_copy<const Rva001E4E50Element *>(
		unsigned int, const Rva001E4E50Element *, const Rva001E4E50Element *);

}

struct Rva001EFAA0Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x001EFAA0, a 12-byte element
template Rva001EFAA0Element *vector<Rva001EFAA0Element, allocator<Rva001EFAA0Element> >::
	_M_allocate_and_copy<const Rva001EFAA0Element *>(
		unsigned int, const Rva001EFAA0Element *, const Rva001EFAA0Element *);

}

struct Rva002E0A10Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x002E0A10, a 12-byte element
template Rva002E0A10Element *vector<Rva002E0A10Element, allocator<Rva002E0A10Element> >::
	_M_allocate_and_copy<const Rva002E0A10Element *>(
		unsigned int, const Rva002E0A10Element *, const Rva002E0A10Element *);

}

struct Rva002E1610Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x002E1610, a 12-byte element
template Rva002E1610Element *vector<Rva002E1610Element, allocator<Rva002E1610Element> >::
	_M_allocate_and_copy<const Rva002E1610Element *>(
		unsigned int, const Rva002E1610Element *, const Rva002E1610Element *);

}

struct Rva003B4D00Element
{
	unsigned char m_body[ 40 ];
};

namespace _STL
{
// retail 0x003B4D00, a 40-byte element
template Rva003B4D00Element *vector<Rva003B4D00Element, allocator<Rva003B4D00Element> >::
	_M_allocate_and_copy<const Rva003B4D00Element *>(
		unsigned int, const Rva003B4D00Element *, const Rva003B4D00Element *);

}

struct Rva003B4D80Element
{
	unsigned char m_body[ 48 ];
};

namespace _STL
{
// retail 0x003B4D80, a 48-byte element
template Rva003B4D80Element *vector<Rva003B4D80Element, allocator<Rva003B4D80Element> >::
	_M_allocate_and_copy<const Rva003B4D80Element *>(
		unsigned int, const Rva003B4D80Element *, const Rva003B4D80Element *);

}

struct Rva003B4E80Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x003B4E80, a 12-byte element
template Rva003B4E80Element *vector<Rva003B4E80Element, allocator<Rva003B4E80Element> >::
	_M_allocate_and_copy<const Rva003B4E80Element *>(
		unsigned int, const Rva003B4E80Element *, const Rva003B4E80Element *);

}

struct Rva003B5080Element
{
	unsigned char m_body[ 12 ];
};

namespace _STL
{
// retail 0x003B5080, a 12-byte element
template Rva003B5080Element *vector<Rva003B5080Element, allocator<Rva003B5080Element> >::
	_M_allocate_and_copy<const Rva003B5080Element *>(
		unsigned int, const Rva003B5080Element *, const Rva003B5080Element *);

}

struct Rva007417A0Element
{
	unsigned char m_body[ 24 ];
};

namespace _STL
{
// retail 0x007417A0, a 24-byte element
template Rva007417A0Element *vector<Rva007417A0Element, allocator<Rva007417A0Element> >::
	_M_allocate_and_copy<const Rva007417A0Element *>(
		unsigned int, const Rva007417A0Element *, const Rva007417A0Element *);

}

struct Rva00769170Element
{
	unsigned char m_body[ 24 ];
};

namespace _STL
{
// retail 0x00769170, a 24-byte element
template Rva00769170Element *vector<Rva00769170Element, allocator<Rva00769170Element> >::
	_M_allocate_and_copy<const Rva00769170Element *>(
		unsigned int, const Rva00769170Element *, const Rva00769170Element *);

}
