// stlport
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
#include <string>

// Three two-byte-element reserves and range assignments.
//
// The reserve guards its count twice: once against the largest count the
// address space could hold for a two-byte element, which is why the immediate
// is 0x7FFFFFFF and MSVC does not fold it, and once against zero -- written as
// greater-than-zero, since a not-equal gives je where retail has jbe. Nothing
// is written when either guard fails, so the three pointers are only stored
// inside it.
//
// The two range assignments size themselves from the pointer difference plus
// one for the terminator, then copy the bytes through the imported copier --
// an indirect call through a function pointer, not a direct one -- and step
// the finish pointer past what was copied before writing the terminator. The
// copier's return value is what the step is applied to, so the destination is
// read once before the branch and used on both paths.

void *__cdecl operator new(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return ::operator new(bytes);

	return bfmeAllocNode(bytes);
}

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class Gen_004F9C80
{
public:
	void bfmeReserve(unsigned int count);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

class Gen_004FA770
{
public:
	void bfmeAssign(const short *first, const short *last, void *tag);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

class Gen_006616A0
{
public:
	void bfmeAssign(const short *first, const short *last, void *tag);
	void Rva00661730(const short *first, const short *last);

private:
	short *m_bfmeStart;					// +0x00
	short *m_bfmeFinish;					// +0x04
	short *m_bfmeEnd;					// +0x08
};

// ?bfmeReserve@Gen_004F9C80@@QAEXI@Z
void Gen_004F9C80::bfmeReserve(unsigned int count)
{
	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}
}

// ?bfmeAssign@Gen_004FA770@@QAEXPBF0PAX@Z
void Gen_004FA770::bfmeAssign(const short *first, const short *last, void *tag)
{
	int bytes = (const char *)last - (const char *)first;
	unsigned int count = (unsigned int)(last - first) + 1;

	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}

	short *cursor = m_bfmeStart;

	if (last != first)
		cursor = (short *)((char *)bfmeMemCopy(cursor, first, bytes) + bytes);

	m_bfmeFinish = cursor;
	*cursor = 0;
}

// ?bfmeAssign@Gen_006616A0@@QAEXPBF0PAX@Z
void Gen_006616A0::bfmeAssign(const short *first, const short *last, void *tag)
{
	int bytes = (const char *)last - (const char *)first;
	unsigned int count = (unsigned int)(last - first) + 1;

	if (count <= (unsigned int)-1 / sizeof(short) && count > 0)
	{
		short *block = (short *)bfmeAllocate(count * sizeof(short));

		m_bfmeEnd = block + count;
		m_bfmeStart = block;
		m_bfmeFinish = block;
	}

	short *cursor = m_bfmeStart;

	if (last != first)
		cursor = (short *)((char *)bfmeMemCopy(cursor, first, bytes) + bytes);

	m_bfmeFinish = cursor;
	*cursor = 0;
}

// Retail 0x00661730 forwards a pointer range and the unused iterator-tag
// address to the same thiscall range initializer at ILT 0x00042BB8.
// ECX is the string owner, not a third stdcall argument.
void Gen_006616A0::Rva00661730(const short *first, const short *last)
{
	bfmeAssign(first, last, &last);
}

// The native forward-range adapter keeps the existing address-qualified helper.
// Its complete body above is visible to VC7.1: the unused empty iterator tag
// can then reuse the hidden result-pointer home, as in retail 0x00844460.
// Both the 106-byte helper and all prior claims in this TU remain byte-exact.
namespace _STL
{
template<> template<>
__forceinline void basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::_M_range_initialize<const wchar_t *>(
    const wchar_t *first, const wchar_t *last, const forward_iterator_tag &tag)
{
    reinterpret_cast<Gen_006616A0 *>(this)->bfmeAssign(
        reinterpret_cast<const short *>(first),
        reinterpret_cast<const short *>(last),
        const_cast<forward_iterator_tag *>(&tag));
}
}

#include <locale>

namespace _STL
{
// STLport 4.5.3 collate<unsigned short>::do_transform, 87 bytes.
// RTTI identifies the wide collate vtable at VA 0x0112EAE8; slot 2 is this body.
// The native string base destructor supplies the independently verified
// 43-byte construction cleanup through ILT 0x00032D85 -> 0x004D4DE0.
wstring collate<wchar_t>::do_transform(const wchar_t *low, const wchar_t *high) const
{
    return wstring(low, high);
}
}
