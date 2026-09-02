// ?setCurrentFilename@BfmeAptScreenMapTransfer@@QAEXABVAsciiString@@@Z
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00510320: APT-era MapTransferLoadScreen::setCurrentFilename.
// Strips the last backslash-separated leaf from the incoming path and
// publishes it through WindowManager::bfme_setAptText under
// APT:FileTransferLoadingMapName.  this is unused.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void *data() const { return m_data; }
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const AsciiString &text );
};

extern WindowManager *g_theWindowManager;

class BfmeAptScreenMapTransfer
{
public:
	void setCurrentFilename( const AsciiString &filename );
};

// ?setCurrentFilename@BfmeAptScreenMapTransfer@@QAEXABVAsciiString@@@Z
void BfmeAptScreenMapTransfer::setCurrentFilename( const AsciiString &filename )
{
	void *data = filename.data();
	const char *start = (const char *)data + 8;
	unsigned int len = 0;
	if( data )
		goto has_data;
	start = (const char *)0x0107388B;
join:
	{
		const char *end = start + len;
		if( end != start )
		{
			do
			{
				--end;
				if( *end == '\\' )
					goto found;
			} while( end != start );
		}
		start = data ? (const char *)data + 8 : (const char *)0x0107388B;
		goto got_leaf;
found:
		start = end + 1;
got_leaf:
		AsciiString leaf( start );
		AsciiString key( "APT:FileTransferLoadingMapName" );
		g_theWindowManager->bfme_setAptText( key, leaf );
		return;
	}
has_data:
	len = *(unsigned short *)( (char *)data + 4 );
	goto join;
}
