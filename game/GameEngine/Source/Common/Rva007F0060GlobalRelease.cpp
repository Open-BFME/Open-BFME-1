// Address-derived EA FESL allocator teardown helper.
//
// The retail body at RVA 0x007F0060 null-checks the process-wide allocator
// interface, invokes its third vtable slot with a zero argument, and clears
// the global.  The interface uses the SDK's stdcall vtable ABI: the object
// pointer is the first stack argument, followed by the slot argument.

struct Rva007F0060Allocator
{
	void *m_v0;
	void *m_v1;
	void (__cdecl *m_release)( Rva007F0060Allocator *, int );
};

struct Rva007F00B0Allocator;
extern Rva007F00B0Allocator *g_Rva0130A5B0;

void Rva007F0060()
{
	Rva007F0060Allocator *allocator =
		reinterpret_cast<Rva007F0060Allocator *>( g_Rva0130A5B0 );
	if( allocator )
	{
		allocator->m_release( allocator, 0 );
		g_Rva0130A5B0 = 0;
	}
}
