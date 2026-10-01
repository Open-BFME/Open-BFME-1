// cl: /DNDEBUG /MD /EHsc

// Retail global at 0x012F19E8; canonical mangled spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A.  Only the null test and
// the clear below touch it here, so no TU-local view of the pointee is needed.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
extern void __cdecl j_0003f3e1();
extern void __cdecl d_00894a90();
extern void __cdecl j_0002b314();

typedef void (__stdcall *BfmeStdIntCall)( int );
typedef void (__cdecl *BfmeIntCall)( int );

class Gen00783F60_00466610
{
public:
	void gen00466610();

private:
	char m_padding[ 0xB8 ];
	unsigned char m_flags;
};

void Gen00783F60_00466610::gen00466610()
{
	if ( g_rva012F19E8WindowManager != 0 )
	{
		if ( (m_flags & 2) != 0 )
			(reinterpret_cast<BfmeStdIntCall>( j_0003f3e1 ))( 0 );
		(reinterpret_cast<BfmeIntCall>( d_00894a90 ))( 1 );
		j_0002b314();
		g_rva012F19E8WindowManager = 0;
	}
}
