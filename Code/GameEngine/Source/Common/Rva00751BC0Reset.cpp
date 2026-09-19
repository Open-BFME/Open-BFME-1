// Retail 0x00751BC0 clears the dword reached through its +0x27c pointer.
// No caller or type table proves a semantic owner, so the address stays in the names.

struct Rva00751BC0Object
{
	char m_pad[ 0x27c ];
	int *m_slot;
};

void __stdcall Rva00751BC0( Rva00751BC0Object *object )
{
	*object->m_slot = 0;
}
