// cl: /DNDEBUG /MD /EHsc
// ?_bfme_requestLadderRank@BFMENetworkBackend@@QAEXH@Z
// Retail 0x0065BE50, 183 bytes.

typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		unsigned short m_refCount;
		unsigned short m_numCharsAllocated;
		unsigned short m_length;
		unsigned short m_pad;
		T m_data[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}
};

struct BFMELadderHttpRecord
{
	void *backend;
	int unused;
	int profileID;
};

namespace _STL
{
	template <class T> struct less {};
	template <class T> class allocator {};
	template <class First, class Second> struct pair {};

	template <class Key, class Value, class Compare = less<Key>,
		class Allocator = allocator<pair<const Key, Value> > >
	class map
	{
	public:
		Value &operator[]( const Key &key );

	private:
		void *m_header;
		unsigned int m_size;
		unsigned int m_allocator;
	};
}

typedef _STL::map<int, BFMELadderHttpRecord *> BFMEHttpRequestMap;

class BFMENetworkBackend
{
public:
	void _bfme_requestLadderRank( int profileID );

private:
	char m_pad[0x5C];
	BFMEHttpRequestMap m_requests;
};

// ghttpCompletedCallback: param is at [esp+0x18], so GHTTPByteCount is 64-bit.
// Body at 0x0065BCC0 is not converted here.
typedef int (__cdecl *ghttpCompletedCallback)( int request, int result, char *buffer, __int64 bufferLen, void *param );

extern "C" int __cdecl ghttpGetA( const char *URL, int blocking, ghttpCompletedCallback completed, void *param );

int __cdecl bfmeLadderRankHttpComplete( int request, int result, char *buffer, __int64 bufferLen, void *param );

void BFMENetworkBackend::_bfme_requestLadderRank( int profileID )
{
	AsciiString url;
	url.format( (AsciiString)"http://lotrbfme.arenasdk.gamespy.com/ladderrank.sdk?ladderid=25909,25911&profileid=%d", profileID );
	int requestId = ghttpGetA( url.str(), 0, bfmeLadderRankHttpComplete, this );
	if ( requestId )
	{
		BFMELadderHttpRecord *rec = new BFMELadderHttpRecord;
		rec->backend = this;
		rec->profileID = profileID;
		m_requests[requestId] = rec;
	}
}
