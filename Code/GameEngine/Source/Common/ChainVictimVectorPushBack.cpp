// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Three inlined vector<ChainVictim005C92F0 *>::push_back bodies. The copy
// ctor at 0x005C92F0 already named the element and pinned this overflow ILT
// (0x00016AE5). 0x005C9140 binds the incoming pointer slot directly;
// 0x005C9CC0 copies it to a local first (52B); 0x005CAF80 is the same
// local-plus-vector-ref spelling at owner+0xC0 (61B). Placement-new
// supplies the null check on finish.

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

class Rva005C9CC0
{
public:
	void append( ChainVictim005C92F0 *value );

private:
	_STL::vector<ChainVictim005C92F0 *> m_items;
};

class Rva005CAF80
{
public:
	void append( ChainVictim005C92F0 *value );

private:
	char m_head[ 0xC0 ];
	_STL::vector<ChainVictim005C92F0 *> m_items;
};

// ?append@Sub005C92F0@@QAEXPAVChainVictim005C92F0@@@Z
void Sub005C92F0::append( ChainVictim005C92F0 *value )
{
	m_items.push_back( value );
}

// ?append@Rva005C9CC0@@QAEXPAVChainVictim005C92F0@@@Z
void Rva005C9CC0::append( ChainVictim005C92F0 *value )
{
	ChainVictim005C92F0 *item = value;
	m_items.push_back( item );
}

// ?append@Rva005CAF80@@QAEXPAVChainVictim005C92F0@@@Z
void Rva005CAF80::append( ChainVictim005C92F0 *value )
{
	ChainVictim005C92F0 *item = value;
	_STL::vector<ChainVictim005C92F0 *> &items = m_items;
	items.push_back( item );
}
