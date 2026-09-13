// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00510320..0x005103E1 (exclusive end 0x005103E2), 194 bytes.
// This is the APT-era BfmeAptScreenMapTransfer filename display, distinct
// from the legacy MapTransferLoadScreen method at 0x00491FA0.
//
// The former generated row's identity is established by the named
// doFileTransfer caller at 0x0066CE60 and the sibling APT transfer methods.
// StringInlineData preserves the BFME eight-byte string header locally; the
// source below is the real leaf scan and APT text update, not a byte lift.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	StringInlineData<char> *data() const { return m_data; }
	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
	unsigned int getLength() const
	{
		return m_data ? (unsigned short)m_data->m_length : 0;
	}
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

void BfmeAptScreenMapTransfer::setCurrentFilename( const AsciiString &filename )
{
	const char *start = filename.str();
	unsigned int len = filename.getLength();
	StringInlineData<char> *data = filename.data();
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
}
