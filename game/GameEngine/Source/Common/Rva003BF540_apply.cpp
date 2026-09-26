extern void j_000048d1();

class BfmeOwnCZ
{
	public:
	char m_pad00[ 0x1E ];
	bool m_at1E;
	__forceinline void bfmeSetCZ( int value )
	{
		typedef void (BfmeOwnCZ::*Call)( int );
		union { void (*function)(); Call member; } route;
		route.function = j_000048d1;
		(this->*route.member)( value );
	}
};

struct Rva003BF540Span
{
	BfmeOwnCZ **m_begin;
	BfmeOwnCZ **m_end;

	unsigned int size() const { return m_end - m_begin; }
	BfmeOwnCZ *operator[]( unsigned int index ) const { return m_begin[ index ]; }
};

class Rva003BF540
{
public:
	void apply( bool on );

private:
	char m_pad00[ 0x0C ];
	Rva003BF540Span m_items;
};

void Rva003BF540::apply( bool on )
{
	int value = *reinterpret_cast<int *>( &on );
	for( unsigned int index = 0; index < m_items.size(); ++index )
	{
		if( m_items[ index ]->m_at1E )
			m_items[ index ]->bfmeSetCZ( value );
	}
}
