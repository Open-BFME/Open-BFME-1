// cl: /O2 /Ob0

struct Rva0058D8E0Target
{
	char m_pad00[ 0x74 ];
	int  m_key;
};

struct Rva0058D8E0Node
{
	char m_pad00[ 8 ];
	int  m_key;
};

struct Rva0058D8E0Slot
{
	Rva0058D8E0Node *m_node;
	char              m_pad04[ 0x14 ];
};

void __cdecl rva0058D8E0Select( int index );

class Rva0058D8E0SlotLookup
{
public:
	void selectMatchingSlot( Rva0058D8E0Target *target );

private:
	char                 m_pad00[ 4 ];
	Rva0058D8E0Node     *m_end;
	Rva0058D8E0Slot      m_slots[ 17 ];
};

void Rva0058D8E0SlotLookup::selectMatchingSlot( Rva0058D8E0Target *target )
{
	for( int i = 0; i < 17; ++i )
	{
		Rva0058D8E0Node *node = m_slots[ i ].m_node;
		if( node != m_end )
		{
			int key = target->m_key;
			if( key == node->m_key )
			{
				rva0058D8E0Select( i );
				return;
			}
		}
	}
}
