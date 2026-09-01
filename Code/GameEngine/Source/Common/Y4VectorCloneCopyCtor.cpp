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
	Sub005C92F0(const Sub005C92F0 &other);

private:
	_STL::vector<ChainVictim005C92F0 *> m_items;
};

// ??0Sub005C92F0@@QAE@ABV0@@Z
Sub005C92F0::Sub005C92F0(const Sub005C92F0 &other)
{
	m_items.reserve(other.m_items.size());
	for (_STL::vector<ChainVictim005C92F0 *>::const_iterator it = other.m_items.begin();
		it != other.m_items.end(); ++it)
	{
		m_items.push_back((*it)->clone());
	}
}
