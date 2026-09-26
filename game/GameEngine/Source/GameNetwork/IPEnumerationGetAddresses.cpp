// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?getAddresses@IPEnumeration@@QAEPAVEnumeratedIP@@XZ
// Retail 0x00624C80.  BFME falls back to a loopback EnumeratedIP only when
// hostname resolution returns no hostent; normal host entries are then kept
// in ascending numeric order.

typedef unsigned short WORD;
typedef unsigned int UnsignedInt;

struct WSADATA
{
	WORD wVersion;
	unsigned char m_unmodelled_002[0x18e];
};

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

extern "C" __declspec(dllimport) int __stdcall WSAStartup( WORD version,
	WSADATA *data );
extern "C" __declspec(dllimport) int __stdcall WSACleanup( void );
extern "C" __declspec(dllimport) int __stdcall gethostname( char *name,
	int length );
extern "C" __declspec(dllimport) hostent *__stdcall gethostbyname(
	const char *name );
extern "C" __declspec(dllimport) unsigned long __stdcall ntohl(
	unsigned long value );

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );
};

class EnumeratedIP
{
public:
	EnumeratedIP();
	void setIPstring( AsciiString name );

	void setIP( UnsignedInt value ) { m_IP = value; }
	UnsignedInt getIP() const { return m_IP; }
	void setNext( EnumeratedIP *next ) { m_next = next; }
	EnumeratedIP *getNext() const { return m_next; }

private:
	AsciiString m_IPstring;
	UnsignedInt m_IP;
	EnumeratedIP *m_next;
};

class Rva00624C80IPEnumeration
{
public:
	EnumeratedIP *getAddresses();

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

// ?getAddresses@IPEnumeration@@QAEPAVEnumeratedIP@@XZ
EnumeratedIP *Rva00624C80IPEnumeration::getAddresses()
{
	if (m_IPlist != 0)
		return m_IPlist;

	if (!m_isWinsockInitialized)
	{
		WSADATA wsadata;
		int err = WSAStartup( 0x0202, &wsadata );
		if (err != 0)
			return 0;

		if ((unsigned char)wsadata.wVersion != 2 ||
			(unsigned char)(wsadata.wVersion >> 8) != 2)
		{
			WSACleanup();
			return 0;
		}
		m_isWinsockInitialized = true;
	}

	char hostname[256];
	if (gethostname( hostname, sizeof(hostname) ) != 0)
		return 0;

	hostent *hostEnt = gethostbyname( hostname );
	if (hostEnt == 0)
	{
		EnumeratedIP *newIP = new EnumeratedIP;
		newIP->setIPstring( AsciiString( "127.0.0.1" ) );
		newIP->setIP( 0x0100007f );
		m_IPlist = newIP;
		newIP->setNext( 0 );
		return m_IPlist;
	}

	if (hostEnt->h_length != 4)
		return 0;

	int numAddresses = 0;
	char *entry;
	while ((entry = hostEnt->h_addr_list[numAddresses++]) != 0)
	{
		EnumeratedIP *newIP = new EnumeratedIP;

		AsciiString str;
		str.format( AsciiString( "%d.%d.%d.%d" ),
			(unsigned char)entry[0], (unsigned char)entry[1],
			(unsigned char)entry[2], (unsigned char)entry[3] );

		UnsignedInt testIP = *((UnsignedInt *)entry);
		UnsignedInt ip = (UnsignedInt)ntohl( testIP );

		newIP->setIPstring( str );
		newIP->setIP( ip );

		if (!m_IPlist)
		{
			m_IPlist = newIP;
			newIP->setNext( 0 );
		}
		else if (newIP->getIP() < m_IPlist->getIP())
		{
			newIP->setNext( m_IPlist );
			m_IPlist = newIP;
		}
		else
		{
			EnumeratedIP *p = m_IPlist;
			while (p->getNext() &&
				p->getNext()->getIP() < newIP->getIP())
			{
				p = p->getNext();
			}
			newIP->setNext( p->getNext() );
			p->setNext( newIP );
		}
	}

	return m_IPlist;
}
