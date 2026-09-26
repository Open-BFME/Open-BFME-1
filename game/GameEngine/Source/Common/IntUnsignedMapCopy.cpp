// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: map<Int, UnsignedInt>'s tree copy, _M_copy at 0x000AAC70, 171
// bytes. The name was parked on the 5-byte thunk at 0x00042BB3, which jumps
// here.
//
// STLport's own _M_copy out of the real header. The node is 0x18 bytes --
// sixteen of header and eight of value -- and the pair is two dwords, so the
// value is copied inline rather than through the out-of-line _Construct the
// class-typed trees need.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;

typedef _STL::map<Int, UnsignedInt> BfmeIntMap;

void BfmeIntMapCopyAnchor(BfmeIntMap &out, const BfmeIntMap &in)
{
	out = in;
}
