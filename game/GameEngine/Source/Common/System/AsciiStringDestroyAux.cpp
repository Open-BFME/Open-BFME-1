// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

namespace _STL
{
struct __false_type {};

template <class T>
void __destroy_aux(T, T, const __false_type &);

class AsciiStringDestroyAuxShim
{
public:
	static void destroy(void *first, void *last, const __false_type &);
};

template <class T>
void __destroy_aux(T first, T last, const __false_type &tag)
{
	AsciiStringDestroyAuxShim::destroy((void *)first, (void *)last, tag);
}

template void __destroy_aux<AsciiString *>(AsciiString *, AsciiString *, const __false_type &);
}
