// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __write_decimal_backward<long> from _num_put.c.
//
// Signed decimal backward formatting, retail body 0x00835A20 (118 bytes,
// [0x00835A20,0x00835A96)). Identity: the matched caller
// ??$__write_integer_backward@J@_STL@@YAPADPADHJ@Z at 0x00835940 pushes
// (ptr, x, flags, &__true_type()) and calls it; the row in
// targets/game/reverse/symbols.csv names the same body. Callee __alldvrm
// at 0x009F7C30 is the MSVC signed 64-bit divide-remainder helper.
//
// The 64-bit sibling at 0x00835730 keeps the literal upstream
// inputs/vendor/stlport/stl/_num_put.c spelling, so this file carries only
// the long instantiation, in the order the compiler needs to reach retail's
// register allocation:
//
//   * __negative is computed before __max_int_t __temp is initialized, so
//     the widening load lands in EAX and setl writes BL. Reversing the two
//     declarations moves the whole prologue into ECX/CL (measured: 115 B,
//     76 differing bytes, shape 0.846).
//   * the loop runs on an unsigned long long copy assigned in both arms of
//     the sign branch. That second wide object is what makes MSVC 7.1
//     allocate EBX before the setl and keep the sign byte there, instead of
//     parking it in the dead __x argument slot as CL. Without it the same
//     source compiles to the CL form (measured: 115 B, 76 differing bytes).
//
// The arithmetic is the vendor's: negate the widened magnitude, then emit
// digits low-order-first through __alldvrm, then put the sign.

#define _STLP_LINK_TIME_INSTANTIATION 1
#include <locale>

namespace _STL {

typedef _STLP_LONG_LONG __max_int_t;

template <class Integer>
char *_STLP_CALL __write_decimal_backward(
	char *ptr, Integer x, ios_base::fmtflags flags, const __true_type &);

template <class Integer>
char *_STLP_CALL __write_decimal_backward(
	char *ptr, Integer x, ios_base::fmtflags flags, const __true_type &)
{
	const bool __negative = x < 0;
	__max_int_t __temp = x;
	unsigned long long __u;
	if (__negative) {
		__temp = -__temp;
		__u = __temp;
	} else {
		__u = __temp;
	}
	for (; __u != 0; __u /= 10)
		*--ptr = (int)(__u % 10) + '0';
	if (__negative)
		*--ptr = '-';
	else if (flags & ios_base::showpos)
		*--ptr = '+';
	return ptr;
}

template char *_STLP_CALL __write_decimal_backward<long>(
	char *, long, ios_base::fmtflags, const __true_type &);

} // namespace _STL
