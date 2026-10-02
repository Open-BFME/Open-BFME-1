// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// 0x0093C310 (30 bytes) sat alone in an unclaimed .text gap among WW3D2 rows:
// 16-byte-aligned start after an int3 pad run, ret 8 followed by int3 padding,
// and no call, ILT stub, table slot, code immediate, pin or dir32 name at the
// address.  The constructor stores a DC, selects an object into it through
// the GDI32 import and keeps the object SelectObject returned.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.

extern "C" __declspec(dllimport) void *__stdcall SelectObject( void *dc, void *object );

class Rva0093C310Selection
{
public:
	Rva0093C310Selection( void *dc, void *object );

	void *m_dc;
	void *m_previous;
};

Rva0093C310Selection::Rva0093C310Selection( void *dc, void *object )
	: m_dc( dc )
{
	m_previous = SelectObject( dc, object );
}
