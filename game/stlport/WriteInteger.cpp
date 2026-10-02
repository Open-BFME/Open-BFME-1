// cl: /O2 /EHsc /MD
// STLport 4.5.3 __write_integer from src/num_put.cpp.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned int);

namespace _STL {

// Retail 0x00835940 is the signed long instantiation of the STLport
// formatter (game/Libraries/Source/STLport/WriteIntegerBackward.cpp), so
// the declaration keeps the upstream template shape and the call below
// deduces Integer = long.
template <class Integer>
char *__cdecl __write_integer_backward(char *buf, int flags, Integer value);

char *__cdecl __write_integer(char *buf, int flags, long x)
{
	char tmp[64];
	char *bufend = tmp + 64;
	char *beg = __write_integer_backward(bufend, flags, x);
	if (bufend == beg)
		return buf;
	unsigned int n = (unsigned int)(bufend - beg);
	return (char *)memmove(buf, beg, n) + n;
}

} // namespace _STL
