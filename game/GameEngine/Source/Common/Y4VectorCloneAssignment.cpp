// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class ChainVictim005C92F0
{
public:
	virtual ~ChainVictim005C92F0();
	virtual ChainVictim005C92F0 *clone() const;
};

class Sub005C92F0
{
public:
	Sub005C92F0 &operator=(const Sub005C92F0 &other);

private:
	_STL::vector<ChainVictim005C92F0 *> m_items;
};

// ??4Sub005C92F0@@QAEAAV0@ABV0@@Z
Sub005C92F0 &Sub005C92F0::operator=(const Sub005C92F0 &other)
{
	Sub005C92F0 *self = this;
	_STL::vector<ChainVictim005C92F0 *> copied;
	copied.reserve(other.m_items.size());
	for (_STL::vector<ChainVictim005C92F0 *>::const_iterator it = other.m_items.begin();
		it != other.m_items.end(); ++it)
	{
		copied.push_back((*it)->clone());
	}
	copied.swap(self->m_items);
	for (_STL::vector<ChainVictim005C92F0 *>::iterator it = copied.begin();
		it != copied.end(); ++it)
	{
		if (*it != 0)
			delete *it;
	}
	return *self;
}
