// cl: /O2 /MD /EHsc
// stlport
// STLport 4.6.2 scientific float formatter at retail 0x00848E60.

extern "C" char *__cdecl strcpy(char *, const char *);

namespace _STL
{
	void __format_float_scientific(char *buffer, const char *digits,
		int decimal_position, int sign, bool is_zero, int flags,
		int precision)
	{
		char exponent[4];

		if (sign)
			*buffer++ = '-';
		else if (flags & 0x0800)
			*buffer++ = '+';

		*buffer++ = *digits++;
		if (precision != 0 || (flags & 0x0400))
			*buffer++ = '.';
		int remaining_precision = precision;
		const char *next_digit = digits;

		if (remaining_precision <= 0)
			goto suffix;

	loop:
		{
			char digit = *next_digit;
			--remaining_precision;
			if (digit == 0)
				goto suffix;
			*buffer++ = digit;
			++next_digit;
		}
		if (remaining_precision > 0)
			goto loop;

	suffix:

		char *suffix = exponent + 5;
		*suffix = 0;
		if (!is_zero)
		{
			int exponent_value = decimal_position - 1;
			if (exponent_value < 0)
				exponent_value = -exponent_value;
			for (; exponent_value > 9; exponent_value /= 10)
				*--suffix = (char)('0' + exponent_value % 10);
			*--suffix = (char)('0' + exponent_value);
		}

		while (suffix > exponent + 3)
			*--suffix = '0';
		*--suffix = (char)((decimal_position > 0 || is_zero) ? '+' : '-');
		*--suffix = (char)((flags & 0x4000) ? 'E' : 'e');

		strcpy(buffer, suffix);
	}
}
