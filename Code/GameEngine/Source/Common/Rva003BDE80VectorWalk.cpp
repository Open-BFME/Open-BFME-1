// Address-derived reconstruction of an indexed walk over a pointer span.

class Gen003BDE80Element
{
public:
	void process();
};

struct Rva003BDE80Span
{
	Gen003BDE80Element **m_begin;
	Gen003BDE80Element **m_end;

	unsigned size() const { return m_end - m_begin; }
	Gen003BDE80Element *operator[]( unsigned index ) const { return m_begin[ index ]; }
};

class Rva003BDE80Owner
{
public:
	void processAll();

private:
	char m_pad00[ 0x0C ];
	Rva003BDE80Span m_items;
};

void Rva003BDE80Owner::processAll()
{
	for( unsigned index = 0; index < m_items.size(); ++index )
		m_items[ index ]->process();
}

// cl: /DNDEBUG /MD /EHsc
