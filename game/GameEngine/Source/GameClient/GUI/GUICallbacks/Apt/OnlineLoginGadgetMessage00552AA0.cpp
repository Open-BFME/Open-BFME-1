// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00552AA0: BfmeAptScreenOnlineLogin vtable slot 4 (+0x10), the four-argument gadget-message
// virtual (ret 0x10). No source names the slot, so the method keeps its address-derived name.

#include "ascii_string.h"
#include "unicode_string.h"

// Retail inlines ~UnicodeString: temporaries are released by a direct call to
// StringBase<unsigned short>::releaseBuffer (0x008881D0), not the ??1UnicodeString stub.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

class GameWindow;

class Rva0054FF80
{
public:
	void call( AsciiString &lastEmail, AsciiString &lastName );
};

class BfmeAptScreenOnlineLogin
{
public:
	int rva00552aa0( void *arg0, unsigned int msg, void *control, void *arg3 );

	void _bfme_applyLoginGadgets();
	UnicodeString bfmeGetTextAt74() const;

private:
	unsigned char m_unmodelled[ 0x74 ];
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
};

int BfmeAptScreenOnlineLogin::rva00552aa0( void *arg0, unsigned int msg, void *control, void *arg3 )
{
	// Guards against re-entry while the cached-login refill updates the gadgets.
	static bool s_updatingLoginGadgets;

	switch( msg )
	{
	case 0x4025:
		if( s_updatingLoginGadgets )
			break;
		if( control == 0 )
			break;
		if( control == m_control74 )
		{
			AsciiString nickname( bfmeGetTextAt74() );
			AsciiString empty( AsciiString::TheEmptyString );

			s_updatingLoginGadgets = true;
			((Rva0054FF80 *)this)->call( nickname, empty );
			_bfme_applyLoginGadgets();
			s_updatingLoginGadgets = false;
		}
		if( control == m_control78 )
			_bfme_applyLoginGadgets();
		break;

	case 0x402D:
		if( m_control78 == 0 || m_control7C == 0 )
			break;
		if( control == m_control78 )
			_bfme_applyLoginGadgets();
		if( control == m_control74 )
			_bfme_applyLoginGadgets();
		break;

	case 0x4031:
		if( m_control78 == 0 || m_control7C == 0 )
			break;
		if( control == m_control7C )
			_bfme_applyLoginGadgets();
		break;
	}

	return 1;
}
