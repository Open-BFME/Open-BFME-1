// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two unclaimed COM helper bodies.  Each sat alone in a .text gap no
// ledger row covered: 16-byte-aligned start after an int3 pad run, ret N
// followed by int3 padding, and no call, ILT stub, table slot, code immediate,
// pin or dir32 name at the address.
//
// 0x009586D0 has the shape of comip.h's `_com_ptr_t(int null)` (store null,
// then _com_issue_error(E_POINTER) when the argument is non-zero), and
// 0x00958B40 that of comutil.h's `_bstr_t(const _bstr_t &)` (copy the data
// pointer, then InterlockedIncrement its count at +8).  Both sit among the
// matched WOLBrowser _bstr_t / _com_ptr_t rows, but nothing calls either one
// and neither the interface nor the class is witnessed by a reference, so the
// shapes are not identity proof.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

void __stdcall _com_issue_error( long error );
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *value );

class Rva009586D0NullablePointer
{
public:
	Rva009586D0NullablePointer( int null );

	void *m_pointer;
};

Rva009586D0NullablePointer::Rva009586D0NullablePointer( int null )
	: m_pointer( 0 )
{
	if ( null != 0 )
		_com_issue_error( 0x80004003L );
}

struct Rva00958B40Data
{
	void *m_lead[ 2 ];
	long  m_refs;
};

class Rva00958B40Handle
{
public:
	Rva00958B40Handle( const Rva00958B40Handle &other );

	Rva00958B40Data *m_data;
};

Rva00958B40Handle::Rva00958B40Handle( const Rva00958B40Handle &other )
	: m_data( other.m_data )
{
	if ( m_data != 0 )
		InterlockedIncrement( &m_data->m_refs );
}
