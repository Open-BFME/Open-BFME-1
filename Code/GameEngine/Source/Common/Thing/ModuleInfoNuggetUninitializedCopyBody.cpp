// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Open-BFME5: the real out-of-line body of
// __uninitialized_copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *>.
// The sibling *UninitializedCopy*.cpp claims the 5-byte incremental-link thunk
// at 0x0001819C that reaches it; this TU carries the body it jumps to. The
// per-element _Construct is DECLARED WITHOUT A BODY so it stays out of line,
// exactly as retail calls it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	struct Nugget
	{
		int m_raw[5];
	};
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

template ModuleInfo::Nugget *__uninitialized_copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *>(
    const ModuleInfo::Nugget *, const ModuleInfo::Nugget *, ModuleInfo::Nugget *, const __false_type &);
}
