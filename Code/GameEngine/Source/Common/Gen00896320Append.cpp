// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Gen00896320Item
{
	void *value;
};

class Gen_00896320
{
public:
	void append(void **source);
	void helper(void *first, void *last, void *result);

private:
	unsigned m_count;
	char m_pad04[4];
	Gen00896320Item *m_begin;
};

void Gen_00896320::append(void **source)
{
	Gen00896320Item *end = &m_begin[m_count];
	Gen00896320Item *next = (Gen00896320Item *)source + 1;
	Gen00896320Item *begin = (Gen00896320Item *)source;
	helper(&begin, &next, &end);
}
