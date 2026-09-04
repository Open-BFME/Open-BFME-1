// ?d_003c6200@@YAXXZ
// cl: /DNDEBUG /MD /O2 /EHsc

class Rva003C6200Item
{
public:
	char m_pad00[ 0xA8 ];
	unsigned char m_enabled;
};

class Rva003C6200Global;
extern Rva003C6200Global *Glo012F4B98;

class Rva003C6200Global
{
};

extern void j_0004669b();

static void Rva003C6200VisitItem( Rva003C6200Item *item )
{
	typedef void (Rva003C6200Global::*Visit)( Rva003C6200Item * );
	union
	{
		void (*plain)();
		Visit member;
	} target;
	target.plain = j_0004669b;
	( Glo012F4B98->*target.member )( item );
}

class Rva003C6200Owner
{
public:
	void update( Rva003C6200Item *item, bool force );

private:
	char m_pad00[ 0x40 ];
	Rva003C6200Item *m_current;
	int m_count;
};

void Rva003C6200Owner::update( Rva003C6200Item *item, bool force )
{
	if( item == 0 )
	{
		if( m_current != 0 )
		{
			Rva003C6200VisitItem( item );
			m_current = 0;
			m_count = 0;
			return;
		}
	}
	else if( force || item->m_enabled )
	{
		if( m_current != item )
			m_count = 0;
		else
			++m_count;

		if( m_count == 0 )
			Rva003C6200VisitItem( item );
		m_current = item;
	}
}
