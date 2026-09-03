// cl: /EHsc /MD
// stlport
// STLport 4.5.3 codecvt<unsigned short, char> do_out / do_in (C-locale copy).

#include <algorithm>

typedef int mbstate_t;

namespace _STL {

struct codecvt_wide_char
{
	int do_out(mbstate_t &state, const unsigned short *from,
	           const unsigned short *from_end, const unsigned short *&from_next,
	           char *to, char *to_end, char *&to_next) const;
	int do_in(mbstate_t &state, const char *from, const char *from_end,
	          const char *&from_next, unsigned short *to, unsigned short *to_end,
	          unsigned short *&to_next) const;
};

int codecvt_wide_char::do_out(mbstate_t &,
	const unsigned short *from, const unsigned short *from_end,
	const unsigned short *&from_next, char *to, char *to_end, char *&to_next) const
{
	int space = (int)(to_end - to);
	int avail = (int)(from_end - from);
	int n = (min)(avail, space);
	int off = n << 1;
	int count = off >> 1;
	char *dst = to;
	const unsigned short *src = from;
	if (count > 0) {
		int left = count;
		do {
			*dst = (char)*src;
			++src;
			++dst;
			--left;
		} while (left);
	}
	from_next = (const unsigned short *)((const char *)from + off);
	to_next = to + n;
	return 0;
}

int codecvt_wide_char::do_in(mbstate_t &,
	const char *from, const char *from_end, const char *&from_next,
	unsigned short *to, unsigned short *to_end, unsigned short *&to_next) const
{
	int space = (int)(to_end - to);
	int avail = (int)(from_end - from);
	int n = (min)(avail, space);
	unsigned short *dst = to;
	const char *src = from;
	if (n > 0) {
		int left = n;
		do {
			*dst = (unsigned short)(signed char)*src;
			++src;
			++dst;
			--left;
		} while (left);
	}
	from_next = from + n;
	to_next = to + n;
	return 0;
}

}
