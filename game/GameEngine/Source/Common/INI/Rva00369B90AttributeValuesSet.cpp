// cl: /DNDEBUG /MD /EHsc
// The INI parser at 0x00369C30 resolves an attribute name and calls this
// method to replace or append its value. The parser's entry pair and the
// pinned STLport overflow body at 0x00369590 establish the record and vector
// types used here.

#include <new>

struct Gen_t_00369920_p8pod
{
	int first;
	float second;
};

class Rva00369B90AttributeValues;

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	friend class ::Rva00369B90AttributeValues;

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;

	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &tag, unsigned int n, bool atEnd);
};
}

class Rva00369B90AttributeValues
{
public:
	void set(int attribute, float value);

private:
	_STL::vector<Gen_t_00369920_p8pod,
		_STL::allocator<Gen_t_00369920_p8pod> > m_values;
};

// ?set@Rva00369B90AttributeValues@@QAEXHM@Z
void Rva00369B90AttributeValues::set(int attribute, float value)
{
	for (Gen_t_00369920_p8pod *it = m_values.m_start;
		it != m_values.m_finish; ++it)
	{
		if (it->first == attribute)
		{
			it->second = value;
			return;
		}
	}

	Gen_t_00369920_p8pod entry = { attribute, value };
	if (m_values.m_finish != m_values.m_endOfStorage)
	{
		new(m_values.m_finish) Gen_t_00369920_p8pod(entry);
		++m_values.m_finish;
	}
	else
	{
		const _STL::__false_type &tag =
			*reinterpret_cast<const _STL::__false_type *>(&value);
		m_values._M_insert_overflow(m_values.m_finish, entry, tag, 1, true);
	}
}
