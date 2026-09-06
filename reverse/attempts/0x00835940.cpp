// ?d_00835940@@YAXXZ
// partial score=0.86 date=2026-09-06
// cl: /O2 /EHsc /MD
// stlport
// STLport 4.5.3 __write_integer_backward from src/num_put.cpp.

namespace _STL {

typedef __int64 max_int_t;
typedef unsigned __int64 umax_int_t;

struct true_type {
};

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
char *__cdecl __write_decimal_backward(
	char *ptr, Integer value, int flags, const true_type &)
{
	max_int_t temp = value;
	const bool negative = value < 0;
	if (negative) {
		temp = -temp;
	}
	for (; temp != 0; temp /= 10) {
		*--ptr = (int)(temp % 10) + '0';
	}
	if (negative) {
		*--ptr = '-';
	} else if (flags & 0x0800) {
		*--ptr = '+';
	}
	return ptr;
}

template <class Integer>
char *__cdecl __write_integer_backward(char *buf, int flags, Integer value)
{
	char *ptr = buf;
	umax_int_t temp;
	if (value == 0) {
		*--ptr = '0';
		if ((flags & 0x0800) && !(flags & 0x30)) {
			*--ptr = '+';
		}
	} else {
		switch (flags & 0x38) {
		case 0x10:
			temp = value;
			for (; temp != 0; temp >>= 3) {
				*--ptr = ((unsigned)temp & 7) + '0';
			}
			if (flags & 0x0200) {
				*--ptr = '0';
			}
			break;
		case 0x20:
		{
			const char *table = (flags & 0x4000)
				? __hex_char_table_hi : __hex_char_table_lo;
			temp = value;
			for (; temp != 0; temp >>= 4) {
				*--ptr = table[(unsigned)temp & 0xf];
			}
			if (flags & 0x0200) {
				*--ptr = table[16];
				*--ptr = '0';
			}
			break;
		}
		default:
			ptr = __write_decimal_backward(ptr, value, flags, true_type());
			break;
		}
	}
	return ptr;
}

template char *__cdecl __write_integer_backward<long>(char *, int, long);

} // namespace _STL
