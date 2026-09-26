// cl: /O2 /MD /EHsc
// stlport
// STLport 4.6.2 __format_float_fixed at retail 0x00849100 (483 bytes).

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios_base.h>
#include <algorithm>

#define MAXFSIG 35
#define MAXFCVT 36

namespace _STL
{
	static inline void flush_static_buffer(string &buffer,
		char *start, char *end, char *&current)
	{
		if (current == end)
		{
			buffer.append(start, end);
			current = start;
		}
	}

	void __format_float_fixed(string &buffer, const char *digits,
		int decimal_position, int sign, bool,
		ios_base::fmtflags flags, int precision, bool is_long)
	{
		char static_buffer[128];
		char *current = static_buffer;
		char *end = static_buffer + sizeof(static_buffer);

		if (sign && decimal_position > -precision && *digits != 0)
			*current++ = '-';
		else if (flags & ios_base::showpos)
			*current++ = '+';

		int trailing_zeroes = 0;
		int remaining_before_point = decimal_position;
		int significant_digits = 0;
		int maximum_significant_digits = is_long ? 2 * MAXFSIG : MAXFSIG;

		do
		{
			*current++ = (char)((remaining_before_point <= 0 ||
				*digits == 0 || significant_digits >= maximum_significant_digits) ?
				'0' : (significant_digits++, *digits++));
			flush_static_buffer(buffer, static_buffer, end, current);
		}
		while (--remaining_before_point > 0);

		if ((flags & ios_base::showpoint) || precision > 0)
		{
			*current++ = '.';
			flush_static_buffer(buffer, static_buffer, end, current);
		}

		int remaining_after_point = (min)(precision, MAXFCVT);
		if (precision > remaining_after_point)
			trailing_zeroes = precision - remaining_after_point;
		while (--remaining_after_point >= 0)
		{
			*current++ = (char)((++decimal_position <= 0 || *digits == 0 ||
				significant_digits >= maximum_significant_digits) ?
				'0' : (significant_digits++, *digits++));
			flush_static_buffer(buffer, static_buffer, end, current);
		}

		while (trailing_zeroes-- > 0)
		{
			*current++ = '0';
			flush_static_buffer(buffer, static_buffer, end, current);
		}
		buffer.append(static_buffer, current);
	}
}
