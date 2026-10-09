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

	// ILT 0x0004557A routes to the matched 0x0054FB10 body; its AL result is unused here.
	bool applyLoginGadgets0054FB10();
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
			applyLoginGadgets0054FB10();
			s_updatingLoginGadgets = false;
		}
		if( control == m_control78 )
			applyLoginGadgets0054FB10();
		break;

	case 0x402D:
		if( m_control78 == 0 || m_control7C == 0 )
			break;
		if( control == m_control78 )
			applyLoginGadgets0054FB10();
		if( control == m_control74 )
			applyLoginGadgets0054FB10();
		break;

	case 0x4031:
		if( m_control78 == 0 || m_control7C == 0 )
			break;
		if( control == m_control7C )
			applyLoginGadgets0054FB10();
		break;
	}

	return 1;
}
