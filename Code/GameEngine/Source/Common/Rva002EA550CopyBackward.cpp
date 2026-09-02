// cl: /O2

class Rva002EA550Str
{
public:
	Rva002EA550Str &operator=(const Rva002EA550Str &other)
	{
		set(other);
		return *this;
	}

	void set(const Rva002EA550Str &other);

private:
	void *m_data;
};

class Rva002EA550Mid
{
public:
	Rva002EA550Mid &operator=(const Rva002EA550Mid &other);

private:
	int m_body[3];
};

struct Rva002EA550Elem
{
	Rva002EA550Str m_name;
	char m_flag;
	Rva002EA550Mid m_tail;

	Rva002EA550Elem &operator=(const Rva002EA550Elem &other)
	{
		m_name = other.m_name;
		m_flag = other.m_flag;
		m_tail = other.m_tail;
		return *this;
	}
};

Rva002EA550Elem *rva002EA550CopyBackward(Rva002EA550Elem *first,
	Rva002EA550Elem *last, Rva002EA550Elem *result)
{
	for (int count = last - first; count > 0; --count)
	{
		--last;
		--result;
		result->m_name = last->m_name;
		result->m_flag = last->m_flag;
		result->m_tail = last->m_tail;
	}
	return result;
}
