// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// FieldParse callback for the "SubTitle" entry of the subtitle field table at
// 0x0112CDA0, the table parseSubtitle (0x0081D7C0, parseSubtitle.cpp) hands to
// INI::initFromINI. Its real name is not proven, so the address stays in it.

#include "../../Include/GameClient/Video.h"
// BFME's UnicodeString mirrors ascii_string.h's AsciiString: it derives from
// StringBase<unsigned short>, its default constructor stores the null buffer in
// place, its destructor is the base one (retail calls 0x008881D0 directly) and
// isEmpty() is expanded at the call site.
template <>
inline StringBase<unsigned short>::StringBase()
{
	m_data = 0;
}
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	~UnicodeString() {}
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
};
#include <string.h>

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *parseTable );
	int getLineNum( void ) const;
	const char *getNextTokenOrNull( const char *separators = 0 );
	const char *getNextSubToken( const char *expected );
	static int scanInt( const char *token );
	static int scanIndexList( const char *token, const char * const *nameList );

	AsciiString getFilename( void ) const
	{
		return m_filename;
	}

	const char *getSeps( void ) const { return m_seps; }
	const char *getSepsColon( void ) const { return m_sepsColon; }

	char m_prefix[ 4 ];
	AsciiString m_filename;
	char m_unknown008[ 0x414 - 8 ];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
};

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface() { }
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual SubtitleManager *getSubTitleMgrForVideo( const AsciiString &title ) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;
extern const FieldParse Rva0081D7C0FieldParseTable[];

class INIException
{
public:
	INIException( int argumentCount, const char *format, ... );
	INIException( const INIException &other );
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};



class SubtitleManager
{
public:
	void addSubtitle( const AsciiString &label, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame );
};

// What this body proves about the manager's second word: the "Label" field
// calls it as bool (const char *label, UnicodeString *text).
struct Rva0081DE40SubtitleManagerView
{
	void *m_createEntry;
	bool ( *m_fetchLabel )( const char *label, UnicodeString *text );
};

extern const char *const Rva012C5190SubtitleStyleNames[];
extern const char *const Rva012C51ACSubtitleAlignNames[];

enum
{
	SUBTITLE_FIELD_UNSET = 0x7fffffff,
	SUBTITLE_MAX_LINES = 15
};

// Parses Label/Color/Style/Align/Line/StartFrame/EndFrame and adds one
// subtitle to the video's manager. Copying store first lets text take its dead
// argument slot as retail does; the no-manager throw comes last (EH state 0xC).
void rva0081DE40ParseSubTitleEntry( INI *ini, void *, void *store, const void * )
{
	void *target = store;
	SubtitleManager *manager = TheVideoPlayer->getSubTitleMgrForVideo( ini->getFilename() );
	if ( manager != 0 && target != 0 )
	{
	UnicodeString text;
	unsigned int color = 0;
	int style = SUBTITLE_FIELD_UNSET;
	int align = SUBTITLE_FIELD_UNSET;
	int line = SUBTITLE_FIELD_UNSET;
	int startFrame = SUBTITLE_FIELD_UNSET;
	int endFrame = SUBTITLE_FIELD_UNSET;
	for ( const char *token = ini->getNextTokenOrNull( ini->getSepsColon() ); token != 0;
		token = ini->getNextTokenOrNull( ini->getSepsColon() ) )
	{
		if ( _strcmpi( token, "Label" ) == 0 && text.isEmpty() )
		{
			const char *label = ini->getNextTokenOrNull( ini->getSeps() );
			if ( label == 0 || !text.isEmpty() || !( (Rva0081DE40SubtitleManagerView *)manager )->m_fetchLabel( label, &text ) )
			{
				throw INIException( 8, "Invalid text label while parsing %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "Color" ) == 0 && color == 0 )
		{
			const char *names[ 3 ] = { "R", "G", "B" };
			for ( int i = 0; i < 3; ++i )
			{
				int value = INI::scanInt( ini->getNextSubToken( names[ i ] ) );
				if ( value < 0 || value > 255 )
				{
					throw INIException( 3, "color value %s=%i out of range (0..255) in %s on line %d",
						names[ i ], value, ini->getFilename(), ini->getLineNum() );
				}
				color = ( color << 8 ) | value;
			}
			color |= 0xff000000;
		}
		else if ( _strcmpi( token, "Style" ) == 0 && style == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle style type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			style = INI::scanIndexList( value, Rva012C5190SubtitleStyleNames );
		}
		else if ( _strcmpi( token, "Align" ) == 0 && align == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle alignment type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			align = INI::scanIndexList( value, Rva012C51ACSubtitleAlignNames );
		}
		else if ( _strcmpi( token, "Line" ) == 0 && line == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				line = INI::scanInt( value ) - 1;
				if ( line < 0 || line >= SUBTITLE_MAX_LINES )
				{
					throw INIException( 3, "Subtitle Line value %d out of range (%d..%d) in %s on line %d",
						line, 1, SUBTITLE_MAX_LINES, ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle line value for Line: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "StartFrame" ) == 0 && startFrame == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				startFrame = INI::scanInt( value );
				if ( startFrame < 0 )
				{
					throw INIException( 3, "Subtitle StartFrame must be greater than 0 in %s on line %d",
						ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle StartFrame value for StartFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "EndFrame" ) == 0 && endFrame == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				endFrame = INI::scanInt( value );
				if ( endFrame < 0 )
				{
					throw INIException( 3, "Subtitle EndFrame must be greater than 0 in %s on line %d",
						ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle EndFrame value for EndFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else
		{
			throw INIException( 3, "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend" );
		}
	}
	// The ledger types addSubtitle's first argument as AsciiString; retail
	// passes this UnicodeString.
	manager->addSubtitle( *(const AsciiString *)&text, color, style, align, line, startFrame, endFrame );
	}
	else
	{
		throw INIException( 9, "Could not locate SubTitleManager for %s", ini->getFilename() );
	}
}
