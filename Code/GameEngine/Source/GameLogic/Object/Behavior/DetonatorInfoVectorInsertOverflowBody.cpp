// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<MinefieldBehavior::DetonatorInfo> reallocating
// insert, retail 0x00573F40, 271 bytes. The body carried only a machine
// byte-dump row and the name was one of five sharing the 5-byte incremental-link
// thunk at 0x0000AE93, which jumps to 0x0075A330 -- the vector<SegInfo> body
// landed earlier today.
//
// The callees put it here: both bulk phases reach helpers the ledger names for
// DetonatorInfo, __uninitialized_copy at 0x00570920 through the ILT at
// 0x00027782 and __uninitialized_fill_n at 0x00570970 through the ILT at
// 0x00019E89, and vector<DetonatorInfo>::push_back is the next function along at
// 0x00574CD0, matched out of MinefieldBehavior.cpp.
//
// The element is 16 bytes and trivially copied, so the size arithmetic shifts
// the byte distance by four and the single-element insert opens into four dword
// moves. Retail hands the helpers' empty dispatch tag the address of its own
// trailing bool argument rather than spending a frame slot on it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h
class MinefieldBehavior
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h
	struct DetonatorInfo
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

// Both reach the helpers the ledger names for this element through their link
// thunks; naming them apart from the _STL spellings keeps those names on their
// real bodies at 0x00570920 and 0x00570970. This instantiation takes its input
// iterators non-const.
MinefieldBehavior::DetonatorInfo *__cdecl BfmeDetonatorInfoUninitializedCopy(
	MinefieldBehavior::DetonatorInfo *first, MinefieldBehavior::DetonatorInfo *last,
	MinefieldBehavior::DetonatorInfo *result, const __false_type &);

MinefieldBehavior::DetonatorInfo *__cdecl BfmeDetonatorInfoUninitializedFillN(
	MinefieldBehavior::DetonatorInfo *result, unsigned int count,
	const MinefieldBehavior::DetonatorInfo &value, const __false_type &);

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

	Type *newFinish = BfmeDetonatorInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeDetonatorInfoUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeDetonatorInfoUninitializedCopy(position, _M_finish, newFinish,
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

template class vector<MinefieldBehavior::DetonatorInfo, allocator<MinefieldBehavior::DetonatorInfo> >;
}
