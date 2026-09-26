// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern char g_bfmeJpegSingleMessage;
extern char g_bfmeJpegExtendedMessage;

class WindowManager
{
public:
	void bfme_hideBackground( bool hide );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2 = 0, int unused1 = 0,
		int unused2 = 0, int unused3 = 0 );

private:
	char m_bfmePrefix[ 0x1B8 ];
	int m_bfmePendingBackgroundKind;
	int m_bfmeRememberedBackgroundKind;
	int m_bfmeBackgroundMovie;
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
					message = &g_bfmeJpegSingleMessage;
				else
					message = &g_bfmeJpegExtendedMessage;
				unidentified_00015235(
					m_bfmeBackgroundMovie, "HideInGameBackground", 1,
					message, 0, 0, 0, 0 );
				m_bfmeRememberedBackgroundKind = 2;
				break;
			}

		case 1:
			{
				const char *message;
				if( hide )
					message = &g_bfmeJpegSingleMessage;
				else
					message = &g_bfmeJpegExtendedMessage;
				unidentified_00015235(
					m_bfmeBackgroundMovie, "HideFrontEndBackground", 1,
					message, 0, 0, 0, 0 );
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
