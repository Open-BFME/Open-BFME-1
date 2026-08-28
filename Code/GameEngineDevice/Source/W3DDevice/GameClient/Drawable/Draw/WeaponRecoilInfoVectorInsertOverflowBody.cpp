// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<W3DModelDraw::WeaponRecoilInfo> reallocating
// insert, retail 0x002109B0, 314 bytes. The name shared the 5-byte
// incremental-link thunk at 0x0000E868 with the vector<State::TransitionInfo>
// spelling, and the body it jumps to carried only a machine byte-dump row.
//
// The callees settle which of the two owns it: both bulk phases reach helpers
// the ledger already names for WeaponRecoilInfo -- __uninitialized_copy at
// 0x0020E2C0 through the ILT at 0x00027525 and __uninitialized_fill_n at
// 0x0020E310 through the ILT at 0x00049459 -- and both sit a couple of KB below
// this body. The TransitionInfo spelling keeps its thunk row.
//
// The element is 12 bytes -- a state enum and two Reals -- so both size
// computations go through the signed divide-by-twelve magic multiply and the
// new end-of-storage is a pair of leas. Retail hands the helpers' empty dispatch
// tag the address of its own trailing bool argument rather than spending a frame
// slot on it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct WeaponRecoilInfo
	{
		int m_state;
		float m_shift;
		float m_recoilRate;
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

// Both reach the 12-byte-element helpers through their link thunks; naming them
// apart from the _STL spellings keeps those names on their real bodies at
// 0x0020E2C0 and 0x0020E310.
W3DModelDraw::WeaponRecoilInfo *__cdecl BfmeWeaponRecoilInfoUninitializedCopy(
	W3DModelDraw::WeaponRecoilInfo *first, W3DModelDraw::WeaponRecoilInfo *last, W3DModelDraw::WeaponRecoilInfo *result, const __false_type &);

W3DModelDraw::WeaponRecoilInfo *__cdecl BfmeWeaponRecoilInfoUninitializedFillN(
	W3DModelDraw::WeaponRecoilInfo *result, unsigned int count,
	const W3DModelDraw::WeaponRecoilInfo &value, const __false_type &);

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

	Type *newFinish = BfmeWeaponRecoilInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeWeaponRecoilInfoUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeWeaponRecoilInfoUninitializedCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

template class vector<W3DModelDraw::WeaponRecoilInfo, allocator<W3DModelDraw::WeaponRecoilInfo> >;
}
