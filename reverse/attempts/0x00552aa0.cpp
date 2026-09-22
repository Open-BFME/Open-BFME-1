// ?rva00552aa0@BfmeAptScreenOnlineLogin@@QAEHPAXI00@Z
// partial score=0.22 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"
#include "unicode_string.h"

// Canonical ascii_string.cpp destructor body, visible for retail inlining.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class GameWindow;

extern UnicodeString GadgetComboBoxGetText( GameWindow *window );

// retail RVA 0x00552AA0, virtual slot 4 (+0x10) of BfmeAptScreenOnlineLogin's
// vtable (??_7BfmeAptScreenOnlineLogin@@6B@, tools/vtable_lookup.py), the same
// slot OnlineHome/OnlineChat/OnlineCustomMatch use for their four-argument
// gadget-message virtual (ret 0x10).  No source names this exact slot, so the
// method keeps its address-derived identity on the real, vtable-proven class.
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

// still-dump helper at 0x0054FF80, reached only through ILT thunk j_00026869;
// no pin exists yet, so it is called through the thunk's own compiled name.
extern "C" void j_00026869();

class HelperTarget;
typedef void ( HelperTarget::*HelperMethod )( AsciiString *, AsciiString * );

int BfmeAptScreenOnlineLogin::rva00552aa0( void *arg0, unsigned int msg, void *control, void *arg3 )
{
	static bool s_updatingLoginGadgets;

	if( msg == 0x4025 )
	{
		if( !s_updatingLoginGadgets )
		{
			void *changed = control;
			if( changed != 0 )
			{
				if( changed == m_control74 )
				{
					AsciiString nickname( bfmeGetTextAt74() );
					AsciiString empty( *(const AsciiString *)0x01336E50 );

					s_updatingLoginGadgets = true;

					union
					{
						void ( *raw )( void );
						HelperMethod member;
					} helper;
					helper.raw = (void ( * )( void ))j_00026869;
					( reinterpret_cast<HelperTarget *>( this )->*helper.member )( &empty, &nickname );

					_bfme_applyLoginGadgets();

					s_updatingLoginGadgets = false;
				}

				if( changed == m_control78 )
					_bfme_applyLoginGadgets();
			}
		}
	}
	else if( msg == 0x402D )
	{
		if( m_control78 != 0 && m_control7C != 0 )
		{
			if( control == m_control78 )
				_bfme_applyLoginGadgets();
			if( control == m_control74 )
				_bfme_applyLoginGadgets();
		}
	}
	else if( msg == 0x4031 )
	{
		if( m_control78 != 0 && m_control7C != 0 )
		{
			if( control == m_control7C )
				_bfme_applyLoginGadgets();
		}
	}

	return 1;
}
