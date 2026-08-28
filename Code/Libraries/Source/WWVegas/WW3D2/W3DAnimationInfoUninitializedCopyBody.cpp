// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Open-BFME5: the real out-of-line body of
// __uninitialized_copy<const W3DAnimationInfo *, W3DAnimationInfo *>.
// The sibling *UninitializedCopy*.cpp claims the 5-byte incremental-link thunk
// at 0x0001D5F7 that reaches it; this TU carries the body it jumps to. The
// per-element _Construct is DECLARED WITHOUT A BODY so it stays out of line,
// exactly as retail calls it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	int m_raw[4];
};

namespace _STL
{
struct __false_type
{
};

template <class T1, class T2>
void _Construct(T1 *destination, const T2 &value);

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &)
{
	Out current = result;
	while (first != last)
	{
		_Construct(current, *first);
		++first;
		++current;
	}
	return current;
}

template W3DAnimationInfo *__uninitialized_copy<const W3DAnimationInfo *, W3DAnimationInfo *>(
    const W3DAnimationInfo *, const W3DAnimationInfo *, W3DAnimationInfo *, const __false_type &);
}
