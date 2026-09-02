// ?handle@Gen00777EE0@@QAEXPAX0@Z
// partial score=0.51 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

struct Gen00777EE0Element
{
	int words[11];
	void destroy();
};

Gen00777EE0Element *rva00777EE0MoveRange(void *last,
	Gen00777EE0Element *oldEnd, void *first, void **firstAddress, int *);

class Gen00777EE0
{
public:
	void handle(void *first, void *last);

private:
	Gen00777EE0Element *m_begin;
	Gen00777EE0Element *m_end;
};

void Gen00777EE0::handle(void *first, void *last)
{
	Gen00777EE0Element *newEnd = rva00777EE0MoveRange(last, m_end,
		first, &first, 0);
	Gen00777EE0Element *oldEnd = m_end;
	for (Gen00777EE0Element *it = newEnd; it != oldEnd; ++it)
		it->destroy();
	m_end = newEnd;
}
