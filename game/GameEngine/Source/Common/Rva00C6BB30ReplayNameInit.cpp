// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// Retail 0x00C6BB30 (22 B) is the dynamic initializer of the std::string LastReplayFileName
// (VA 0x012F418C, defined in ScoreScreen.cpp). It passes the object address in ECX to the
// string default constructor, which retail reaches through ILT 0x0004048A, then registers
// the cleanup bfmeForward_00C70190 with atexit. The STLport headers mark the constructor
// dllimport under /MD, which compiles a call through an import pointer, so this file
// declares the string type itself as matched-source WWLib/stlport_numpunct_grouping.cpp does.

extern "C" int __cdecl atexit(void (__cdecl *)(void));
void bfmeForward_00C70190(void);

namespace _STL
{

template <class T>
class allocator {};

template <class T>
class char_traits {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string();
	~basic_string();
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

} // namespace _STL

extern _STL::string LastReplayFileName;

inline void *operator new(unsigned int, void *place)
{
	return place;
}

void rva00C6BB30Initialize(void)
{
	new (&LastReplayFileName) _STL::string;
	atexit((void (__cdecl *)(void))bfmeForward_00C70190);
}
