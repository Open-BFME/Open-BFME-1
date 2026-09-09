// ?erase@Gen006449B0Str@@QAEPAV1@II@Z
extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *dst, const void *src, unsigned int count);

static inline const unsigned int &bfmeMinGen006449B0(const unsigned int &a, const unsigned int &b)
{
	return a < b ? a : b;
}

class Gen006449B0Str
{
public:
	Gen006449B0Str *erase(unsigned int pos, unsigned int n);
	char *eraseRange(char *first, char *last);

	char *m_begin;
	char *m_end;
};

inline char *Gen006449B0Str::eraseRange(char *first, char *last)
{
	if (first != last)
	{
		unsigned int len = (unsigned int)(m_end - last) + 1;

		if (len != 0)
			BfmeMemMove(first, last, len);

		m_end += first - last;
	}

	return first;
}

Gen006449B0Str *Gen006449B0Str::erase(unsigned int pos, unsigned int n)
{
	unsigned int avail = (unsigned int)(m_end - m_begin) - pos;
	const unsigned int &cnt = bfmeMinGen006449B0(avail, n);
	eraseRange(m_begin + pos, (m_begin + pos) + cnt);

	return this;
}
