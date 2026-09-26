// Address-derived reconstruction of a pointer-span scan for two enabled bytes.

struct Rva003BD830Item
{
	char m_pad00[ 0x1C ];
	bool m_first;
	char m_pad1D;
	bool m_second;
};

struct Rva003BD830Span
{
	Rva003BD830Item **m_begin;
	Rva003BD830Item **m_end;

	unsigned size() const { return m_end - m_begin; }
	Rva003BD830Item *operator[]( unsigned index ) const { return m_begin[ index ]; }
};

class Rva003BD830Owner
{
public:
	bool anyReady() const;

private:
	char m_pad00[ 0x0C ];
	Rva003BD830Span m_items;
};

bool Rva003BD830Owner::anyReady() const
{
	for( unsigned index = 0; index < m_items.size(); ++index )
	{
		Rva003BD830Item *item = m_items[ index ];
		if( item->m_first && item->m_second )
			return true;
	}
	return false;
}

// cl: /DNDEBUG /MD /EHsc
