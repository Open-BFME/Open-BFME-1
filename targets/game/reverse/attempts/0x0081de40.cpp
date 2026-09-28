// ?d_0081de40@@YAXXZ
// partial score=0.61 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Banked attempt for retail 0x0081DE40 (1590 B). Place next to parseSubtitle.cpp in
// game/GameEngine/Source/GameClient/ to compile (relative include as in that sibling).

// VideoPlayer::init passes the retail callback at 0x0081D7C0 to INI::load.
// The callback looks up a subtitle manager through TheVideoPlayer's virtual
// slot at +0x58, then fills it with the subtitle field table at 0x0112CDA0.
// The error text at 0x0112CF14 identifies the callback as parseSubtitle.

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



// The subtitle manager's first member after its vtable-less header is the
// label lookup callback the "Label" field uses to resolve localized text.
class Rva0081DE40SubtitleManager
{
public:
	void addSubtitle( const AsciiString &text, unsigned int color, int style, int align,
		int line, int startFrame, int endFrame );
	int m_unknown00;
	bool ( *m_fetchLabel )( const char *label, UnicodeString *text );
};

extern const char *const Rva012C5190SubtitleStyleNames[];
extern const char *const Rva012C51ACSubtitleAlignNames[];

enum
{
	SUBTITLE_FIELD_UNSET = 0x7fffffff,
	SUBTITLE_MAX_LINES = 15
};

// FieldParse callback for the "SubTitle" entry of the subtitle table at
// 0x0112CDA0 (see parseSubtitle.cpp): parses Label/Color/Style/Align/Line/
// StartFrame/EndFrame and adds one subtitle to the video's manager.
void rva0081DE40ParseSubTitleEntry( INI *ini, void *, void *store, const void * )
{
	Rva0081DE40SubtitleManager *manager =
		(Rva0081DE40SubtitleManager *)TheVideoPlayer->getSubTitleMgrForVideo( ini->getFilename() );
	if ( manager == 0 || store == 0 )
	{
		throw INIException( 9, "Could not locate SubTitleManager for %s", ini->getFilename() );
	}
	{
	UnicodeString text;
	unsigned int color = 0;
	int style = SUBTITLE_FIELD_UNSET;
	int align = SUBTITLE_FIELD_UNSET;
	int line = SUBTITLE_FIELD_UNSET;
	int startFrame = SUBTITLE_FIELD_UNSET;
	int endFrame = SUBTITLE_FIELD_UNSET;
	for ( const char *token = ini->getNextTokenOrNull( ini->m_sepsColon ); token != 0;
		token = ini->getNextTokenOrNull( ini->m_sepsColon ) )
	{
		if ( _stricmp( token, "Label" ) == 0 && text.isEmpty() )
		{
			const char *label = ini->getNextTokenOrNull( ini->m_seps );
			if ( label == 0 || !text.isEmpty() || !manager->m_fetchLabel( label, &text ) )
			{
				throw INIException( 8, "Invalid text label while parsing %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _stricmp( token, "Color" ) == 0 && color == 0 )
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
		else if ( _stricmp( token, "Style" ) == 0 && style == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->m_sepsColon );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle style type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			style = INI::scanIndexList( value, Rva012C5190SubtitleStyleNames );
		}
		else if ( _stricmp( token, "Align" ) == 0 && align == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->m_sepsColon );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle alignment type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			align = INI::scanIndexList( value, Rva012C51ACSubtitleAlignNames );
		}
		else if ( _stricmp( token, "Line" ) == 0 && line == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->m_sepsColon );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle line value for Line: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			line = INI::scanInt( value ) - 1;
			if ( line < 0 || line >= SUBTITLE_MAX_LINES )
			{
				throw INIException( 3, "Subtitle Line value %d out of range (%d..%d) in %s on line %d",
					line, 1, SUBTITLE_MAX_LINES, ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _stricmp( token, "StartFrame" ) == 0 && startFrame == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->m_sepsColon );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle StartFrame value for StartFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			startFrame = INI::scanInt( value );
			if ( startFrame < 0 )
			{
				throw INIException( 3, "Subtitle StartFrame must be greater than 0 in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _stricmp( token, "EndFrame" ) == 0 && endFrame == SUBTITLE_FIELD_UNSET )
		{
			const char *value = ini->getNextTokenOrNull( ini->m_sepsColon );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle EndFrame value for EndFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			endFrame = INI::scanInt( value );
			if ( endFrame < 0 )
			{
				throw INIException( 3, "Subtitle EndFrame must be greater than 0 in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else
		{
			throw INIException( 3, "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend" );
		}
	}
	manager->addSubtitle( *(const AsciiString *)&text, color, style, align, line, startFrame, endFrame );
	}
}
