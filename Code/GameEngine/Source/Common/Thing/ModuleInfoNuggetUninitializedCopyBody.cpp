// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Only opaque row dup_00772240 remains: its element construction calls
// 0x00772160, from the string/vector family. The unrelated 0x0076B010
// instantiation now belongs to Containers/Rva0013B8F0Vector.cpp.
// This legacy ModuleInfo::Nugget emitter spelling is not type identity proof.

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
