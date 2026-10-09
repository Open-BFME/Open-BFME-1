// cl: /O2

class AsciiString;

class Rva0019A260Owned
{
public:
	virtual ~Rva0019A260Owned() {}
};

class Dict
{
public:
    void clear();
    Dict &operator=(const Dict &);
private:
    char m_padding[4];
};

struct Gen_t_00065960_p4cd;
namespace _STL
{
template <class Value> class allocator;
template <class Value, class Alloc> class vector
{
public:
    Value *erase(Value *, Value *);
    Value *m_first;
    Value *m_last;
};
}

class Rva0019A260State
{
public:
	void cleanup(void *object);

private:
	Rva0019A260Owned *m_first;
	Dict m_extra;
	Rva0019A260Owned *m_second;
	_STL::vector<Gen_t_00065960_p4cd, _STL::allocator<Gen_t_00065960_p4cd> > m_range;
};

void Rva0019A260State::cleanup(void *object)
{
	if (m_first != 0)
		delete m_first;
	m_first = 0;
	m_extra.clear();

	if (m_second != 0)
		delete m_second;
	m_second = 0;
	_STL::vector<Gen_t_00065960_p4cd, _STL::allocator<Gen_t_00065960_p4cd> > *range = &m_range;
	range->erase(range->m_first, range->m_last);

	if (object != 0)
		m_extra = *reinterpret_cast<const Dict *>(object);
}
