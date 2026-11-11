// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

// STLport vector<unsigned int>::_M_fill_insert, retail 0x003D3D50: the
// LargeGroupAudioKeyMap bit-word vector.
//
// Not vector<void*>: retail was linked without identical-COMDAT folding, and
// vector<void*>::_M_fill_insert is 0x00067740, the body every hashtable
// _M_initialize_buckets/_M_copy_from calls (STLport _hashtable.h: the bucket
// vector is vector<void*>).  This copy is reached only from the resize at
// 0x003D4210 (ILT 0x0002570C), whose callers are LargeGroupAudioKeyMap
// bfmeMerge 0x003D4580 and bfmeAddKey 0x003D46A0.
//
// Element type, from three independent retail links to one instantiation:
// - its overflow call goes through ILT 0x0001CBFC to 0x000BBC80, the overflow
//   addAudioHandle 0x006145C0 uses for its vector of AudioHandle
//   (GameAudio.h: typedef UnsignedInt AudioHandle);
// - the LargeGroupAudioKeyMap copy constructor 0x003D3BB0 calls get_allocator
//   0x003D32D0, already pinned (ilt_oracle) as vector<unsigned int>'s;
// - bfmeMerge/bfmeAddKey pass the fill value as `push 0`, a scalar, not a
//   wrapped struct.
// Callees: fill ILT 0x0000A060 -> 0x003D31A0, overflow ILT 0x0001CBFC.

template void _STL::vector<unsigned int, _STL::allocator<unsigned int> >::_M_fill_insert(
	unsigned int *, unsigned int, const unsigned int &);
