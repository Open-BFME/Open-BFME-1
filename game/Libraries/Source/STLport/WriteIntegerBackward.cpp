// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __write_integer_backward instantiations from _num_put.c.
//
// The long and __int64 bodies share the upstream size-dependent mask.
// Their matched callers identify the specializations: 0x008459B0 calls the
// long formatter; the VW/VZ num_put callers pass both words for __int64.
// Keep the signed decimal helpers out of line at 0x00835A20 and 0x00835730.
// Unsigned decimal formatting stays inline, including retail's showpos behavior.
// The tag selection and size-dependent mask follow inputs/vendor/stlport/stl/_num_put.c.

#define _STLP_LINK_TIME_INSTANTIATION 1
#include <locale>
#include <limits>

namespace _STL {

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
char *_STLP_CALL __write_decimal_backward(
	char *, Integer, ios_base::fmtflags, const __true_type &);

template <class Integer>
__forceinline char *_STLP_CALL __write_decimal_backward(
	char *ptr, Integer value, ios_base::fmtflags flags, const __false_type &)
{
	for (; value != 0; value /= 10)
		*--ptr = (int)(value % 10) + '0';
	if (flags & ios_base::showpos)
		*--ptr = '+';
	return ptr;
}

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
			if (sizeof(value) < 8 && sizeof(unsigned_temp) >= 8)
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
			if (sizeof(value) < 8 && sizeof(unsigned_temp) >= 8)
				unsigned_temp &= 0xffffffffULL;
			for (; unsigned_temp != 0; unsigned_temp >>= 4)
				*--ptr = table[(unsigned)unsigned_temp & 0xf];
			if (flags & ios_base::showbase) {
				*--ptr = table[16];
				*--ptr = '0';
			}
			break;
		}
		default: {
			typedef typename __bool2type<numeric_limits<Integer>::is_signed>::_Ret IsSigned;
			ptr = __write_decimal_backward(ptr, value, flags, IsSigned());
			break;
		}
		}
	}
	return ptr;
}

template char *_STLP_CALL
__write_integer_backward<long>(char *, ios_base::fmtflags, long);

template char *_STLP_CALL
__write_integer_backward<__int64>(char *, ios_base::fmtflags, __int64);

template char *_STLP_CALL
__write_integer_backward<unsigned long>(char *, ios_base::fmtflags,
	unsigned long);

template char *_STLP_CALL
__write_integer_backward<unsigned _STLP_LONG_LONG>(
	char *, ios_base::fmtflags, unsigned _STLP_LONG_LONG);

} // namespace _STL
