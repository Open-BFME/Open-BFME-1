// 6-slot aggregate managing subobjects with position and flag updates

struct Block3
{
	unsigned int m_dword[3];
};

struct Rva00409930Target
{
	char          m_lead[0x44];
	unsigned char m_flag;
	char          m_pad[3];
	Block3        m_pos;

	void setPos( const Block3 &pos )
	{
		m_pos = pos;
	}
};

class IInterface00409790
{
public:
	virtual void release( int arg ) = 0;
};

struct SubTarget00409790
{
	char m_pad[8];
	int  m_state;
};

struct Rva00409850SubObject
{
	char                m_pad0[4];
	unsigned char       m_active;
	char                m_pad1[7];
	int                 m_flag;
	char                m_pad2[8];
	Rva00409930Target  *m_target;
	char                m_trail[0x20];

	void method( unsigned char arg );
	// The retail names are not recovered; these synthetic identities retain
	// the independently proven receiver and neighboring boundaries.
	void rva_004097F0( unsigned char value );
	void rva_00409810( const Block3 &pos );
};

void Rva00409850SubObject::method( unsigned char arg )
{
	if ( arg )
	{
		if ( m_target )
		{
			((IInterface00409790 *)m_target)->release( 1 );
			m_target = 0;
		}
		m_active = 0;
	}
	else if ( m_active )
	{
		switch ( m_flag )
		{
		case 1:
			if ( m_target )
			{
				((SubTarget00409790 *)m_target)->m_state = 2;
			}
			m_active = 0;
			break;
		}
	}
}

void Rva00409850SubObject::rva_004097F0( unsigned char value )
{
	if ( m_flag == 1 && m_target )
	{
		m_target->m_flag = value;
	}
}

void Rva00409850SubObject::rva_00409810( const Block3 &pos )
{
	if ( m_flag == 1 && m_target )
	{
		m_target->setPos( pos );
	}
}

struct Rva00409930Slot
{
	char                  m_lead[0x8];
	Rva00409850SubObject  m_subObject;
};

class Rva00409930
{
public:
	void dispatchSlot( int index, unsigned char arg );
	void setTargetFlag( unsigned char value );
	void setPositions( const Block3 &pos );

	Rva00409930Slot m_slots[6];
};

void Rva00409930::dispatchSlot( int index, unsigned char arg )
{
	if ( index < 6 && index >= 1 )
	{
		m_slots[ index ].m_subObject.method( arg );
	}
}

void Rva00409930::setTargetFlag( unsigned char value )
{
	for ( int i = 0; i < 6; ++i )
	{
		if ( m_slots[i].m_subObject.m_flag == 1 && m_slots[i].m_subObject.m_target != 0 )
		{
			m_slots[i].m_subObject.m_target->m_flag = value;
		}
	}
}

void Rva00409930::setPositions( const Block3 &pos )
{
	for ( int i = 0; i < 6; ++i )
	{
		if ( m_slots[i].m_subObject.m_flag == 1 && m_slots[i].m_subObject.m_target != 0 )
		{
			m_slots[i].m_subObject.m_target->setPos( pos );
		}
	}
}
