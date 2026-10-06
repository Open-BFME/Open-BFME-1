// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ?findHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
//
// Retail walks the std::list sentinel stored at manager+0.  A node links at
// +0x00 and stores its HeaderTemplate at +0x08.  HeaderTemplate's name is the
// inline AsciiString at +0x04.  The lookup compares the by-value query with
// that name through StringBase<char>::compare, then releases the automatic
// query on both the match and no-match exits.

extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
#pragma intrinsic(memcmp)

template <typename T> class StringBase
{
friend class AsciiString;

public:
	// Header-inline; its COMDAT is retail 0x0005FEB0.
	int compare( const StringBase<T> &str ) const;

// The shared StringBase bodies own the refcounted allocation; this TU keeps
// the actual data-bearing layout while using their declarations at the ABI.
private:
	StringBase( void );
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );

protected:

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

template <> inline int StringBase<char>::compare( const StringBase<char> &str ) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp( data, otherData, length < otherLength ? length : otherLength );
	return result ? result : length - otherLength;
}

class AsciiString : public StringBase<char>
{
public:
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
};

typedef char BfmeAsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

class GameFont;

class HeaderTemplate
{
public:
	GameFont *m_font;
	AsciiString m_name;
};

struct HeaderTemplateListNode
{
	HeaderTemplateListNode *m_next;
	unsigned int m_unused;
	HeaderTemplate *m_value;
};

class HeaderTemplateList
{
public:
	HeaderTemplateListNode *m_node;
};

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );

private:
	HeaderTemplateList m_headerTemplateList;
};

HeaderTemplate *HeaderTemplateManager::findHeaderTemplate( AsciiString name )
{
	HeaderTemplateListNode *head = m_headerTemplateList.m_node;
	for( HeaderTemplateListNode *it = head->m_next; it != head; it = it->m_next )
	{
		HeaderTemplate *header = it->m_value;
		if( header->m_name.compare( name ) == 0 )
			return header;
	}
	return 0;
}
