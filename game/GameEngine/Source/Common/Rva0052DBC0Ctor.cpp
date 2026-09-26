class BfmeString52DBC0
{
public:
	BfmeString52DBC0( const BfmeString52DBC0 &other );

private:
	void *m_data;
};

class Rva0052DBC0
{
public:
	Rva0052DBC0( unsigned int value, const BfmeString52DBC0 &text, bool enabled );

private:
	bool m_enabled;
	BfmeString52DBC0 m_text;
	unsigned int m_value;
};

Rva0052DBC0::Rva0052DBC0( unsigned int value, const BfmeString52DBC0 &text, bool enabled )
	: m_enabled( enabled ), m_text( text ), m_value( value )
{
}
