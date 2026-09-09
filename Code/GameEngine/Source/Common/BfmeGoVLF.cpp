// cl: /DNDEBUG /DWIN32 /MD /EHsc-
//
// The owned-subsystem constructor at retail 0x00596970 passes thunk 0x0000FDDA
// to its callback field.  That thunk reaches this dispatcher at 0x005892D0.

typedef void (__cdecl *BfmeGoVLFCallback)( int value );

class Glo012F4B98Type
{
public:
	char m_pad[ 0x508 ];
	BfmeGoVLFCallback m_callback;
	char m_flag;
};

extern Glo012F4B98Type *Glo012F4B98;

// ?bfmeGoVLF@@YAXXZ
void bfmeGoVLF()
{
	BfmeGoVLFCallback *slot = &Glo012F4B98->m_callback;
	BfmeGoVLFCallback callback = *slot;
	if( callback != 0 )
	{
		callback( Glo012F4B98->m_flag != 0 );
		*slot = 0;
	}
}
