// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<W3DRopeDraw::SegInfo> reallocating insert, retail
// 0x0075A330, 271 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x0000AE93 and the body it jumps to carried only a machine byte-dump row.
//
// The address settles which of the five names sharing that thunk owns the body:
// vector<SegInfo>::erase is at 0x0075A280 and vector<SegInfo>::clear at
// 0x0075A300, both already matched out of W3DRopeDraw.cpp, and this body is the
// next one along. The other four names on the thunk are identical-code aliases
// and keep their thunk rows.
//
// The element is 16 bytes and trivially copied, so the size arithmetic shifts
// the byte distance by four and the single-element insert opens into four dword
// moves. The bulk phases stay out of line -- __uninitialized_copy through the
// ILT at 0x00017765 and __uninitialized_fill_n through the ILT at 0x00042334 --
// and both take a trailing dispatch tag. Retail hands that empty tag the
// address of its own trailing bool argument rather than spending a frame slot
// on it, which is the only way the function comes out with one local dword
// instead of two.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
class W3DRopeDraw
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
	struct SegInfo
	{
		unsigned char m_data[16];
	};
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *block);
void __cdecl vectorSmallDeallocate(void *block, unsigned int bytes);

struct __false_type
{
};

template <class Type>
class allocator
{
};

// Both reach retail's shared 16-byte-element helpers through their link thunks;
// naming them apart from the _STL spellings keeps those names on their real
// bodies at 0x00759FB0 and 0x0075A000.
W3DRopeDraw::SegInfo *__cdecl BfmeSegInfoUninitializedCopy(
	const W3DRopeDraw::SegInfo *first, const W3DRopeDraw::SegInfo *last,
	W3DRopeDraw::SegInfo *result, const __false_type &);

W3DRopeDraw::SegInfo *__cdecl BfmeSegInfoUninitializedFillN(
	W3DRopeDraw::SegInfo *result, unsigned int count,
	const W3DRopeDraw::SegInfo &value, const __false_type &);

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Type);
		if (bytes > 128)
			newStart = (Type *)vectorLargeAllocate(bytes);
		else
			newStart = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = BfmeSegInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeSegInfoUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeSegInfoUninitializedCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}

template class vector<W3DRopeDraw::SegInfo, allocator<W3DRopeDraw::SegInfo> >;
}
