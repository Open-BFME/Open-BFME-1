// ?Rva00039577ParticleSysBoneInfoCopyThunk@@YAXXZ
// Retail RVA 0x00039577 is a five-byte tail jump to the matched STLport
// ParticleSysBoneInfo const-source copy body at RVA 0x000A78A0. The thunk
// keeps the caller's copy arguments on the stack.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ParticleSysBoneInfo
{
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
	OutputIterator result, const random_access_iterator_tag &tag,
	Distance *distance);

// The instantiation lives in ParticleSysBoneInfoVector.cpp, over the same
// 67-byte range at 0x000A78A0 that retail calls from here.
extern template ParticleSysBoneInfo *__copy<
	const ParticleSysBoneInfo *,
	ParticleSysBoneInfo *, int>(
	const ParticleSysBoneInfo *,
	const ParticleSysBoneInfo *,
	ParticleSysBoneInfo *,
	const random_access_iterator_tag &, int *);
}

void Rva00039577ParticleSysBoneInfoCopyThunk(void)
{
	// The five copy arguments are already on the stack: retail's thunk is a
	// bare jump, so the call is made through a nullary pointer type.
	typedef ParticleSysBoneInfo *(*CopyFn)(const ParticleSysBoneInfo *,
		const ParticleSysBoneInfo *, ParticleSysBoneInfo *,
		const _STL::random_access_iterator_tag &, int *);
	CopyFn copy = _STL::__copy<
		const ParticleSysBoneInfo *,
		ParticleSysBoneInfo *, int>;
	((void (*)())(void *)copy)();
}
