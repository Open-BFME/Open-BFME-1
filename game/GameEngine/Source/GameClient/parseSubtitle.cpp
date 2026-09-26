// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// VideoPlayer::init passes the retail callback at 0x0081D7C0 to INI::load.
// The callback looks up a subtitle manager through TheVideoPlayer's virtual
// slot at +0x58, then fills it with the subtitle field table at 0x0112CDA0.
// The error text at 0x0112CF14 identifies the callback as parseSubtitle.

#include "../../Include/GameClient/Video.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *instance, const FieldParse *parseTable );
	int getLineNum( void ) const;

	AsciiString getFilename( void ) const
	{
		return m_filename;
	}

private:
	char m_prefix[ 4 ];
	AsciiString m_filename;
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


// ?parseSubtitle@@YAXPAVINI@@PAX1PBX@Z
void parseSubtitle( INI *ini, void *, void *, const void * )
{
	const void *subtitle = TheVideoPlayer->getSubTitleMgrForVideo( ini->getFilename() );
	if ( subtitle != 0 )
	{
		if ( ini->getNextToken( 0 ) != 0 )
		{
			ini->initFromINI( const_cast<void *>( subtitle ), Rva0081D7C0FieldParseTable );
		}
	}
	else
	{
		throw INIException( 8, "Could not get SubTitleMgr * for %s on line %d",
			ini->getFilename(), ini->getLineNum() );
	}
}
