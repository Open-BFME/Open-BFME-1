// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MapTransferLoadScreen::~MapTransferLoadScreen at 0x00490E10.
//
// The class is a BFME layout of the LoadScreen hierarchy, not the smaller
// Generals header layout: the existing base subobject occupies 0x10 bytes, so
// the five MAX_SLOTS tables begin at +0x10.  Retail's vtable 0x010F9B60 is
// independently identified by its init/reset/progress slots as
// MapTransferLoadScreen, and this destructor's tail jump is the existing
// LoadScreen-family base destructor at ILT 0x0004634E (body 0x00490470).
//
// Rva00490470 is the address-derived spelling already pinned for that exact
// base destructor.  Its twelve-byte payload is represented here only to keep
// the proven +0x10 derived offset; the base destructor owns its cleanup.

class Rva00490470
{
public:
	virtual ~Rva00490470();

private:
	char m_basePayload[ 12 ];
};

class MapTransferLoadScreen : public Rva00490470
{
public:
	virtual ~MapTransferLoadScreen();

private:
	void *m_progressBars[ 8 ];
	void *m_playerNames[ 8 ];
	void *m_progressText[ 8 ];
	int m_playerLookup[ 8 ];
	int m_oldProgress[ 8 ];
	void *m_fileNameText;
	void *m_timeoutText;
};

MapTransferLoadScreen::~MapTransferLoadScreen()
{
	for ( int i = 0; i < 8; ++i )
	{
		m_progressBars[ i ] = 0;
		m_playerNames[ i ] = 0;
		m_progressText[ i ] = 0;
		m_playerLookup[ i ] = -1;
		m_oldProgress[ i ] = -1;
	}
	m_fileNameText = 0;
	m_timeoutText = 0;
}
