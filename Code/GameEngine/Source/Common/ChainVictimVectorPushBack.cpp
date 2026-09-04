// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Three inlined vector<ChainVictim005C92F0 *>::push_back bodies. The copy
// ctor at 0x005C92F0 already named the element and pinned this overflow ILT
// (0x00016AE5). Retail takes the pointer by value so the inlined const T&
// binds the incoming slot; placement-new supplies the null check on finish.

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
	void append( ChainVictim005C92F0 *value );

private:
	_STL::vector<ChainVictim005C92F0 *> m_items;
};

// ?append@Sub005C92F0@@QAEXPAVChainVictim005C92F0@@@Z
void Sub005C92F0::append( ChainVictim005C92F0 *value )
{
	m_items.push_back( value );
}
