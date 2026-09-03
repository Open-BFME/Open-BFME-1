// cl: /O2 /Ob0

struct Rva00595160Template
{
	char m_pad00[ 4 ];
	Rva00595160Template *m_nextOverride;
	char m_pad08[ 0xc8 ];
	unsigned int m_flags;
};

struct Rva00595160Argument
{
	char m_pad00[ 4 ];
	Rva00595160Template *m_template;
	char m_pad08[ 0x6c ];
	void *m_key;
};

struct Rva00595160Node
{
	Rva00595160Node *m_next;
	Rva00595160Node *m_previous;
	void *m_key;
	char m_pad0c[ 0x10 ];
};

struct Rva00595160List
{
	Rva00595160Node *m_head;
};

struct Rva00595160Slot
{
	Rva00595160Node *m_node;
	char m_pad04[ 0x14 ];
};

extern void j_000022bb();
extern void j_0000c117();
extern void bfmeDeallocate( void *, unsigned int );

typedef Rva00595160Template *(__fastcall *Rva00595160OverrideCall)(
	Rva00595160Template *);
typedef int (__cdecl *Rva00595160CheckCall)( void *, void * );

class Rva00595160
{
public:
	void update( Rva00595160Argument *argument );

	private:
	char m_pad00[ 4 ];
	Rva00595160List *m_list;
	Rva00595160Slot m_slots[ 18 ];
};

// ?update@Rva00595160@@QAEXPAVRva00595160Argument@@@Z
void Rva00595160::update( Rva00595160Argument *argument )
{
	Rva00595160Template *object = argument->m_template;
	if ( object != 0 && object->m_nextOverride != 0 )
	{
		Rva00595160OverrideCall overrideCall =
			(Rva00595160OverrideCall)j_000022bb;
		object = overrideCall( object->m_nextOverride );
	}

	if ( ( object->m_flags & 0x02000000 ) == 0 )
		return;

	Rva00595160Template *checkObject = argument->m_template;
	if ( checkObject != 0 && checkObject->m_nextOverride != 0 )
	{
		Rva00595160OverrideCall overrideCall =
			(Rva00595160OverrideCall)j_000022bb;
		checkObject = overrideCall( checkObject->m_nextOverride );
	}

	Rva00595160CheckCall check = (Rva00595160CheckCall)j_0000c117;
	if ( !check( checkObject, argument ) )
		return;

	void *key = argument->m_key;
	Rva00595160List *list = m_list;
	Rva00595160Node *node = list->m_head;
	while ( node != (Rva00595160Node *)list )
	{
		if ( key == node->m_key )
		{
			for ( int index = 0; index < 17; ++index )
			{
				if ( m_slots[ index ].m_node == node )
				{
					m_slots[ index ].m_node = (Rva00595160Node *)list;
					break;
				}
			}

			Rva00595160Node *next = node->m_next;
			Rva00595160Node *previous = node->m_previous;
			previous->m_next = next;
			next->m_previous = previous;

			bfmeDeallocate( node, 0x14 );
			return;
		}
		node = node->m_next;
	}
}
