// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern void __cdecl Rva0088EAD0( void* );

class Rva00889DD0Node
{
public:
	Rva00889DD0Node* next;
	int m_pad4;
	int value;
};

class Rva00889DD0Class
{
public:
	char pad0[16];
	Rva00889DD0Node* head;

	void d_00889dd0( int val );
};

void Rva00889DD0Class::d_00889dd0( int val )
{
	if ( !val )
	{
		return;
	}

	for ( Rva00889DD0Node** ptr = &head; *ptr != 0; ptr = &(*ptr)->next )
	{
		if ( (*ptr)->value == val )
		{
			Rva00889DD0Node* toDelete = *ptr;
			*ptr = toDelete->next;
			Rva0088EAD0( toDelete );
			return;
		}
	}
}
