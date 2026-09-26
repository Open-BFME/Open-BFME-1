// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ?findHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
//
// Retail walks the std::list sentinel stored at manager+0.  A node links at
// +0x00 and stores its HeaderTemplate at +0x08.  HeaderTemplate's name is the
// inline AsciiString at +0x04.  The lookup compares the by-value query's
// ushort length/data with that name, then releases the automatic query on
// both the match and no-match exits.

template <typename T> class StringBase
{
friend class AsciiString;

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

extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
#pragma intrinsic(memcmp)

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	int compare( const AsciiString &other ) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherText = other.m_data ? other.m_data->data : (const char *)0x0107388B;
		int thisLength = m_data ? m_data->length : 0;
		const char *thisText = m_data ? m_data->data : (const char *)0x0107388B;
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp( thisText, otherText, length );
		if( result != 0 )
			return result;
		return thisLength - otherLength;
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
