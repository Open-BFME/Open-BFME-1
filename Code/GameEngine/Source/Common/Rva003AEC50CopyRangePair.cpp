// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of _Rva0036D9E0CopyRange (0x0036D9E0,
// Rva0036D9E0CopyRange.cpp); same stride-12 STL-style copy loop, but the element
// here has only one string-shaped member (at +4) and a trailing byte (at +8) --
// the leading dword at +0 is never touched by either the source or dest walk.
// Two retail sites (0x003AEC50, 0x003B3460) share this exact shape; both are
// instantiated below from the one struct/function pair.

class Rva003AEC50Str
{
public:
	void set(const Rva003AEC50Str &other);

private:
	void *m_data;
};

struct Rva003AEC50Entry
{
	int m_unused;
	Rva003AEC50Str m_str;
	unsigned char m_flag;
	unsigned char m_pad[3];
};

// ?d_003aec50@@YAXXZ
extern "C" Rva003AEC50Entry *__cdecl Rva003AEC50CopyRange(
	const Rva003AEC50Entry *first, const Rva003AEC50Entry *last, Rva003AEC50Entry *result)
{
	int count = last - first;
	while (count > 0)
	{
		result->m_str.set(first->m_str);
		result->m_flag = first->m_flag;
		++first;
		++result;
		--count;
	}
	return result;
}

// ?d_003b3460@@YAXXZ
extern "C" Rva003AEC50Entry *__cdecl Rva003B3460CopyRange(
	const Rva003AEC50Entry *first, const Rva003AEC50Entry *last, Rva003AEC50Entry *result)
{
	int count = last - first;
	while (count > 0)
	{
		result->m_str.set(first->m_str);
		result->m_flag = first->m_flag;
		++first;
		++result;
		--count;
	}
	return result;
}
