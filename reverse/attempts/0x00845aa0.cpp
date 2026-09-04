// ?__insert_grouping@_STL@@YAHPAG0ABVstring@1@GGGH@Z
// partial score=0.92 date=2026-09-03
// cl: /O2 /EHsc /MD
// stlport
// STLport 4.5.3 __insert_grouping(wchar_t*,...) from src/num_put.cpp.
// Probe: 177/177 register-mirror wall — last in ebx vs retail edi; groupsize
// zero/sign-init in ebp vs ebx; movsx groupsize into edi vs ebx. Same class of
// wall as blocked char twin 0x00845A00 (sign/n register order). TU-flag only
// per docs/lessons.md register-allocation wall rule.

typedef int ptrdiff_t;

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)

namespace _STL {

class string {
public:
	typedef unsigned size_type;
	unsigned size() const { return (unsigned)(_M_finish - _M_start); }
	char operator[](unsigned n) const { return _M_start[n]; }

private:
	char *_M_start;
	char *_M_finish;
};

ptrdiff_t __cdecl __insert_grouping(unsigned short *first, unsigned short *last,
	const string &grouping, unsigned short separator, unsigned short Plus,
	unsigned short Minus, int basechars)
{
	if (first == last)
		return 0;

	int sign = 0;
	if (*first == Plus || *first == Minus) {
		sign = 1;
		++first;
	}

	first += basechars;
	unsigned short *cur_group = last;
	string::size_type n = 0;
	int groupsize = 0;

	while (true) {
		groupsize = n < grouping.size()
			? (int)(signed char)grouping[n] : groupsize;
		++n;

		if (groupsize <= 0 || groupsize >= (int)(cur_group - first))
			break;

		cur_group -= groupsize;
		++last;

		int nbytes = (int)((char *)last - (char *)cur_group);
		if (nbytes > 0) {
			char *src = (char *)last - nbytes + 2;
			memmove(src, cur_group, (unsigned)nbytes);
		}
		*cur_group = separator;
	}

	return (last - first) + sign + basechars;
}

} // namespace _STL
