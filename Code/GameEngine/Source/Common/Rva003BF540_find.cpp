// cl: /DNDEBUG /MD /EHsc
//
// Rva003BF540::find, retail 0x003BD7D0, 74 bytes.
//
// Keyed pointer-span lookup over [+0x0C,+0x10). Each node is asked match(id)
// (ILT 0x00032420 -> 0x003A43C0). The bool temporary is load-bearing: without
// it MSVC folds the begin pointer into ecx and mirrors the post-call size
// temp (ecx vs edx) plus the success-path reload (edx vs eax).

class Gen003BD7D0Node
{
public:
	bool match( int id );
};

struct Rva003BF540Span
{
	Gen003BD7D0Node **m_begin;
	Gen003BD7D0Node **m_end;

	unsigned size() const { return m_end - m_begin; }
	Gen003BD7D0Node *operator[]( unsigned index ) const { return m_begin[ index ]; }
};

class Rva003BF540
{
public:
	Gen003BD7D0Node *find( int id );

private:
	char m_pad00[ 0x0C ];
	Rva003BF540Span m_items;
};

// ?find@Rva003BF540@@QAEPAVGen003BD7D0Node@@H@Z
Gen003BD7D0Node *Rva003BF540::find( int id )
{
	for( unsigned index = 0; index < m_items.size(); ++index )
	{
		Gen003BD7D0Node **slots = m_items.m_begin;
		bool hit = slots[ index ]->match( id );
		if( hit )
			return m_items.m_begin[ index ];
	}
	return 0;
}
