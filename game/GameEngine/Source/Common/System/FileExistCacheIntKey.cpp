// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// FILE: FileExistCacheIntKey.cpp /////////////////////////////////////////////
//
// _STL::map<Int, Bool>::operator[], retail 0x00596C90.
//
// FileSystem.cpp already instantiates this operator through its own cache-touch
// scaffold and compiles 108 of the 112 bytes.  Four of the remainder are the
// insert_unique call; the other two are the whole finding: retail's two key
// comparisons are `jl' and `jge', and FileSystem.cpp's are `jb' and `jae'.
// Signed.  The reference Common/FileSystem.h declares the cache
// std::map<unsigned,bool>, so less<unsigned> gives the unsigned branches -- but
// BFME's key is Int, and less<Int> is what retail compiled.
//
// The unsigned instantiation stays where it is: FileSystem.cpp carries 27 rows
// and several are helpers of that spelling.  This TU adds the signed one beside
// it, which is additive -- the two operator[] bodies are different COMDATs with
// different mangled names, and only this one claims 0x00596C90.
//
///////////////////////////////////////////////////////////////////////////////

#include <map>

// The touch is the whole point: it is what makes the compiler emit operator[].
static void bfmeFileExistCacheTouchIntKey( _STL::map<int, bool> &cache, int key, bool value )
{
	cache[key] = value;
}

void (*g_bfmeFileExistCacheTouchIntKey)( _STL::map<int, bool> &, int, bool ) =
	bfmeFileExistCacheTouchIntKey;
