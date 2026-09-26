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

extern Rva007F0060Allocator *g_Rva0130A5B0;

void Rva007F0060()
{
	if( g_Rva0130A5B0 )
	{
		g_Rva0130A5B0->m_release( g_Rva0130A5B0, 0 );
		g_Rva0130A5B0 = 0;
	}
}
