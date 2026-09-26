// cl: /DNDEBUG /MD /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

extern "C" unsigned int __cdecl strlen( const char *text );
#pragma intrinsic(strlen)

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( void ) : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const StringBase<T> &other );
	void set( const T *text, int length );

	struct Header;
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( void ) : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	void set( const char *text, int length )
	{
		StringBase<char>::set( text, length );
	}
	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}
};

typedef char AsciiStringSizeCheck[(sizeof(AsciiString) == 4) ? 1 : -1];

class GameFont;

class HeaderTemplate
{
public:
	HeaderTemplate( void );
	GameFont *m_font;
	AsciiString m_name;
	AsciiString m_fontName;
	int m_point;
	unsigned char m_bold;
};

typedef char HeaderTemplateSizeCheck[(sizeof(HeaderTemplate) == 20) ? 1 : -1];

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );
	HeaderTemplate *newHeaderTemplate( AsciiString name );

	// The owning table uses BFME's Font/Point/Bold offsets at +8/+C/+10.
	const void *getFieldParse( void ) const
	{
		return (const void *)0x010F9830;
	}

private:
	typedef std::list<HeaderTemplate *> HeaderTemplateList;
	HeaderTemplateList m_headerTemplateList;
};

extern HeaderTemplateManager *TheHeaderTemplateManager;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const void *fieldParse );
	static void parseHeaderTemplateDefinition( INI *ini );
};

// ?newHeaderTemplate@HeaderTemplateManager@@QAEPAVHeaderTemplate@@VAsciiString@@@Z
HeaderTemplate *HeaderTemplateManager::newHeaderTemplate( AsciiString name )
{
	HeaderTemplate *headerTemplate = new HeaderTemplate;
	if( !headerTemplate )
		return 0;

	headerTemplate->m_name = name;
	m_headerTemplateList.push_front( headerTemplate );
	return headerTemplate;
}

// ?parseHeaderTemplateDefinition@INI@@SAXPAV1@@Z
void INI::parseHeaderTemplateDefinition( INI *ini )
{
	AsciiString name;
	HeaderTemplate *headerTemplate = 0;
	const char *token = ini->getNextToken();
	name.set( token, token ? (int)strlen( token ) : 0 );
	headerTemplate = TheHeaderTemplateManager->findHeaderTemplate( name );
	if( headerTemplate == 0 )
		headerTemplate = TheHeaderTemplateManager->newHeaderTemplate( name );
	ini->initFromINI( headerTemplate, TheHeaderTemplateManager->getFieldParse() );
}
