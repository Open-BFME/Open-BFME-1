// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __write_integer_backward<long> from _num_put.c.
//
// The retail body is the signed-long instantiation called by the matched
// __write_integer wrapper at 0x008459B0.  The link-time-instantiation macro
// suppresses header implementations here; this TU emits only the integer-
// backward specialization and leaves the real out-of-line decimal callee at
// 0x00835A20 unresolved.

#define _STLP_LINK_TIME_INSTANTIATION 1
#include <locale>

namespace _STL {

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
char *_STLP_CALL __write_decimal_backward(
	char *, Integer, ios_base::fmtflags, const __true_type &);

template <class Integer>
char *_STLP_CALL __write_integer_backward(
	char *buf, ios_base::fmtflags flags, Integer value)
{
	char *ptr = buf;
	unsigned __int64 unsigned_temp;
	if (value == 0) {
		*--ptr = '0';
		if ((flags & ios_base::showpos) &&
			((flags & (ios_base::hex | ios_base::oct)) == 0))
			*--ptr = '+';
	} else {
		switch (flags & ios_base::basefield) {
		case ios_base::oct:
			unsigned_temp = value;
			unsigned_temp &= 0xffffffffULL;
			for (; unsigned_temp != 0; unsigned_temp >>= 3)
				*--ptr = ((unsigned)unsigned_temp & 7) + '0';
			if (flags & ios_base::showbase)
				*--ptr = '0';
			break;
		case ios_base::hex: {
			const char *table = (flags & ios_base::uppercase)
				? __hex_char_table_hi : __hex_char_table_lo;
			unsigned_temp = value;
			unsigned_temp &= 0xffffffffULL;
			for (; unsigned_temp != 0; unsigned_temp >>= 4)
				*--ptr = table[(unsigned)unsigned_temp & 0xf];
			if (flags & ios_base::showbase) {
				*--ptr = table[16];
				*--ptr = '0';
			}
			break;
		}
		default:
			ptr = __write_decimal_backward(ptr, value, flags, __true_type());
			break;
		}
	}
	return ptr;
}

template char *_STLP_CALL
__write_integer_backward<long>(char *, ios_base::fmtflags, long);

} // namespace _STL
