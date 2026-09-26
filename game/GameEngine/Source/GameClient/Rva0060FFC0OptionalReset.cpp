// cl: /DNDEBUG /MD /EHsc

class Glo012F706CType
{
};

class Rva0060FFC0Record
{
public:
	char m_pad00[ 4 ];
	void *m_value;
};

class Rva0060FFC0PositionTarget
{
};

class Rva0060FFC0ActionTarget
{
};

extern Glo012F706CType *g_bfmeGameCW;
extern void j_0004446d();
extern void j_0000f0fb();
extern void j_0001fd16();

class Rva0060FFC0Optional
{
public:
	void reset();

private:
	char m_pad00[ 4 ];
	void *m_field04;
	void *m_field08;
	void *m_field0c;
	void *m_field10;
	void *m_field14;
	void *m_field18;
	void *m_field1c;
	void *m_field20;
	char m_pad24[ 0x10 ];
};

void Rva0060FFC0Optional::reset()
{
	typedef Rva0060FFC0Record *(Glo012F706CType::*Lookup)(void *);
	union
	{
		void (*plain)();
		Lookup member;
	} lookup;
	typedef void (Rva0060FFC0PositionTarget::*GetPosition)(void *);
	union
	{
		void (*plain)();
		GetPosition member;
	} getPosition;
	typedef void (Rva0060FFC0ActionTarget::*Action)();
	union
	{
		void (*plain)();
		Action member;
	} action;
	Rva0060FFC0Record *record;

	lookup.plain = j_0004446d;
	record = (g_bfmeGameCW->*lookup.member)( &m_field04 );
	if( record != 0 )
		m_field14 = record->m_value;
	record = (g_bfmeGameCW->*lookup.member)( &m_field08 );
	if( record != 0 )
		m_field18 = record->m_value;
	record = (g_bfmeGameCW->*lookup.member)( &m_field0c );
	if( record != 0 )
		m_field1c = record->m_value;
	record = (g_bfmeGameCW->*lookup.member)( &m_field10 );
	if( record != 0 )
		m_field20 = record->m_value;

	getPosition.plain = j_0000f0fb;
	if( m_field14 != 0 )
		( ( (Rva0060FFC0PositionTarget *)m_field14 )->*getPosition.member )( &m_pad24[ 0x0c ] );
	action.plain = j_0001fd16;
	if( m_field1c != 0 )
		( ( (Rva0060FFC0PositionTarget *)m_field1c )->*getPosition.member )( &m_pad24[ 0 ] );
	( ( (Rva0060FFC0ActionTarget *)m_field1c )->*action.member )();
	( ( (Rva0060FFC0ActionTarget *)m_field20 )->*action.member )();
}
