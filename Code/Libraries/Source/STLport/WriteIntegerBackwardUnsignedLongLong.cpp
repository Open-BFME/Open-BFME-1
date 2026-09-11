// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __write_integer_backward<unsigned long long> from _num_put.c.
// The canonical narrow num_put overload calls this formatter through vtable
// slot 2. The decimal loop remains inline in this formatter and uses the
// unsigned 64-bit division helper from the MSVC runtime.

#define _STLP_LINK_TIME_INSTANTIATION 1
#include <locale>

namespace _STL {

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
__forceinline char *_STLP_CALL __write_decimal_backward(
	char *ptr, Integer value, ios_base::fmtflags flags, const __true_type &)
{
	for (; value != 0; value /= 10)
		*--ptr = (int)(value % 10) + '0';
	if (flags & ios_base::showpos)
		*--ptr = '+';
	return ptr;
}

typedef unsigned _STLP_LONG_LONG __umax_int_t;

template <class Integer>
char *_STLP_CALL __write_integer_backward(
	char *buf, ios_base::fmtflags flags, Integer value)
{
	char *ptr = buf;
	__umax_int_t unsigned_temp;
	if (value == 0) {
		*--ptr = '0';
		if ((flags & ios_base::showpos) &&
			((flags & (ios_base::hex | ios_base::oct)) == 0))
			*--ptr = '+';
	} else {
		switch (flags & ios_base::basefield) {
		case ios_base::oct:
			unsigned_temp = value;
			if (sizeof(value) < 8 && sizeof(__umax_int_t) >= 8)
				unsigned_temp &= 0xFFFFFFFF;
			for (; unsigned_temp != 0; unsigned_temp >>= 3)
				*--ptr = ((unsigned)unsigned_temp & 7) + '0';
			if (flags & ios_base::showbase)
				*--ptr = '0';
			break;
		case ios_base::hex: {
			const char *table = (flags & ios_base::uppercase)
				? __hex_char_table_hi : __hex_char_table_lo;
			unsigned_temp = value;
			if (sizeof(value) < 8 && sizeof(__umax_int_t) >= 8)
				unsigned_temp &= 0xFFFFFFFF;
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
__write_integer_backward<unsigned _STLP_LONG_LONG>(
	char *, ios_base::fmtflags, unsigned _STLP_LONG_LONG);

} // namespace _STL
