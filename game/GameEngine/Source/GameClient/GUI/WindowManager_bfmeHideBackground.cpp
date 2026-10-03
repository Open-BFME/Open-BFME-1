// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern const char g_rva01080FC0[2];
extern char g_bfmeJpegExtendedMessage;

class WindowManager
{
public:
	void bfme_hideBackground( bool hide );

private:
	char m_bfmePrefix[ 0x1B8 ];
	int m_bfmePendingBackgroundKind;
	int m_bfmeRememberedBackgroundKind;
	int m_bfmeBackgroundMovie;
};

// The APT/level-path builder this body reaches (retail 0x004675F0) is a member
// of the level-path builder class; BfmeLevelAN is this TU's view of the
// pointee, as in BfmeConv924.cpp.  The cast at the use is pointer-size
// neutral.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8);
};

void WindowManager::bfme_hideBackground( bool hide )
{
	if( this )
	{
		switch( m_bfmePendingBackgroundKind )
		{
		case 2:
			{
				const char *message;
				if( hide )
					message = g_rva01080FC0;
				else
					message = &g_bfmeJpegExtendedMessage;
				((BfmeLevelAN *)this)->bfmeBuildAN(
					(unsigned int)m_bfmeBackgroundMovie,
					(int)"HideInGameBackground", 1, (int)message, 0, 0, 0, 0);
				m_bfmeRememberedBackgroundKind = 2;
				break;
			}

		case 1:
			{
				const char *message;
				if( hide )
					message = g_rva01080FC0;
				else
					message = &g_bfmeJpegExtendedMessage;
				((BfmeLevelAN *)this)->bfmeBuildAN(
					(unsigned int)m_bfmeBackgroundMovie,
					(int)"HideFrontEndBackground", 1, (int)message, 0, 0, 0, 0);
				m_bfmeRememberedBackgroundKind = 1;
				break;
			}

		case 0:
			if( !hide )
				break;
			if( !m_bfmeRememberedBackgroundKind )
				break;
			m_bfmePendingBackgroundKind = m_bfmeRememberedBackgroundKind;
			m_bfmeRememberedBackgroundKind = 0;
			bfme_hideBackground( true );
			break;
		}
		m_bfmePendingBackgroundKind = 0;
	}
}
