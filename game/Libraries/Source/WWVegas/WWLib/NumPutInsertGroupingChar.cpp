// cl: /O2 /EHsc /MD
// STLport 4.5.3 __insert_grouping(char*,...) at retail 0x00845A00 (155B).

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)

namespace _STL
{

template <class CharT>
class char_traits
{
};

template <class CharT>
class allocator
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	size_type size() const { return (size_type)(_M_finish - _M_start); }
	CharT operator[](size_type n) const { return _M_start[n]; }

private:
	CharT *_M_start;
	CharT *_M_finish;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

int __cdecl __insert_grouping(char *first, char *last,
	const string &grouping, char separator, char Plus, char Minus,
	int basechars)
{
	if (first == last)
		return 0;

	int sign = 0;
	if (*first == Plus || *first == Minus)
	{
		sign = 1;
		++first;
	}

	first += basechars;
	string::size_type n = 0;
	char *cur_group = last;
	int groupsize = 0;

	while (true)
	{
		groupsize = n < grouping.size()
			? (int)(signed char)grouping[n] : groupsize;
		++n;

		if (groupsize <= 0 || groupsize >= cur_group - first)
			break;

		cur_group -= groupsize;
		++last;

		int nbytes = last - cur_group;
		if (nbytes > 0)
		{
			char *destination = last - nbytes + 1;
			memmove(destination, cur_group, (unsigned)nbytes);
		}
		*cur_group = separator;
	}

	return (last - first) + sign + basechars;
}

} // namespace _STL
