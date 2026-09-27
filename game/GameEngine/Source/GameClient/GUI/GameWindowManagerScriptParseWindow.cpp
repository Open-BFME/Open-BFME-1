// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x00487F80, 1328 bytes. Port of the Zero Hour parser with
// BFME's shared window record (0x012F253C), File scanString slot +0x24,
// and native StringBase layout. WinInstanceData uses the reference header;
// its accessed offsets are independently witnessed by name_oracle.
// createWindow and parseData are convention companions: visible static
// bodies let MSVC reproduce the private register arguments. Their ledger
// owners are unchanged. parseData's layout corrections also probe exact.

#define ASCIISTRING_H
#include "ascii_string.h"
#include "PreRTS.h"
#include "GameClient/Gadget.h"
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;

// Ledger names for the two GameWindow calls retail makes on every path
// (ZH winSetWindowId / winGetEditData positions; identities not yet proven).
class Rva00478C90Object { public: Int store( UnsignedInt value ); };
class Gen_004791e0 { public: Int m( void ); };

class Open2479440Record
{
public:
 GameWindow *field00;
 int field04,field08,field0c,field10,field14;
 void *field18,*field1c,*field20,*field24,*field28,*field2c;
 WinInstanceData *dword_30;
};

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva004874A0ManagerView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70();
	virtual GameWindow *s74( Open2479440Record *record );		// ZH winCreate position
	virtual int s78(GameWindow *window); virtual void s7C();
	virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8C();
	virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9C();
	virtual void sA0(); virtual void sA4(); virtual void sA8(); virtual void sAC();
	virtual void sB0(); virtual void sB4(); virtual void sB8(); virtual void sBC();
	virtual void sC0(); virtual void sC4(); virtual void sC8(); virtual void sCC();
	virtual void sD0(); virtual void sD4();
	virtual Int sD8( GameWindow *window, UnsignedInt msg,
		UnsignedInt data1, UnsignedInt data2 );	// ZH winSendInputMsg position
};

class GameTextInterface;
extern GameTextInterface *TheGameText;

class Rva004864E0GameTextView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24();
	virtual UnicodeString s28( const char *label, bool *exists );	// ZH fetch position
};

GameWindow *createGadget( char *type, void *data, Open2479440Record *record, GameWindow *source );

void GadgetButtonSetText( GameWindow *g, UnicodeString text );
void GadgetRadioSetText( GameWindow *g, UnicodeString text );
void GadgetCheckBoxSetText( GameWindow *g, UnicodeString text );
void GadgetStaticTextSetText( GameWindow *g, UnicodeString text );
void GadgetTextEntrySetText( GameWindow *g, UnicodeString text );

static AsciiString theSystemString;
static AsciiString theInputString;
static AsciiString theTooltipString;
static AsciiString theDrawString;

static GameWindow **stackPtr;
static GameWindow *windowStack[ 10 ];

static GameWindow *peekWindow( void )
{
	if( stackPtr == windowStack )
		return 0;
	return *( stackPtr - 1 );
}

// Convention companion only: its row stays with setWindowText_Thunk.cpp.
// ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z present-unmatched
static void setWindowText( GameWindow *window, AsciiString textLabel )
{
	if( textLabel.isEmpty() )
		return;

	UnicodeString theText, entryText;
	theText = ( (Rva004864E0GameTextView *)TheGameText )->s28( textLabel.str(), 0 );
	if( window->winGetStyle() & 0x00000001 )
		GadgetButtonSetText( window, theText );
	else if( window->winGetStyle() & 0x00000002 )
		GadgetRadioSetText( window, theText );
	else if( window->winGetStyle() & 0x00000004 )
		GadgetCheckBoxSetText( window, theText );
	else if( window->winGetStyle() & 0x00000080 )
		GadgetStaticTextSetText( window, theText );
	else if( window->winGetStyle() & 0x00000040 )
	{
		entryText.translate( textLabel );
		GadgetTextEntrySetText( window, entryText );
	}
	else
		window->winSetText( theText );
}

static GameWindow *createWindow( char *type, Int id, Open2479440Record *record, void *data )
{
	GameWindow *window, *parent;

	parent = peekWindow();

	if( !strcmp( type, "USER" ) )
	{
		window = ( (Rva004874A0ManagerView *)TheWindowManager )->s74( record );
		if( window )
		{
			record->dword_30->m_style |= 0x00000200;
			( (Rva00478C90Object *)window )->store( id );
		}
	}
	else if( !strcmp( type, "TABPANE" ) )
	{
		window = ( (Rva004874A0ManagerView *)TheWindowManager )->s74( record );
		if( window )
		{
			record->dword_30->m_style |= 0x00004000;
			window->winSetInstanceData( record->dword_30 );
			( (Rva00478C90Object *)window )->store( id );
		}
	}
	else
	{
		window = createGadget( type, data, record, 0 );
		if( window )
			( (Rva00478C90Object *)window )->store( id );
	}

	if( window )
	{
		GameWindowEditData *editData = (GameWindowEditData *)( (Gen_004791e0 *)window )->m();
		if( editData )
		{
			editData->systemCallbackString = theSystemString;
			editData->inputCallbackString = theInputString;
			editData->tooltipCallbackString = theTooltipString;
			editData->drawCallbackString = theDrawString;
		}
	}

	if( window )
		setWindowText( window, record->dword_30->m_textLabelString );

	if( window && parent )
		( (Rva004874A0ManagerView *)TheWindowManager )->sD8( parent, 0x16, id, 0 );

	return window;
}


// Native BFME StringBase inlines at this caller.
template<> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline void StringBase<char>::clear() { releaseBuffer(); }
template<> inline int StringBase<char>::compare(const char *s) const {
 int n = s ? strlen(s) : 0;
 int len = getLength(); const char *text = str();
 int common = len < n ? len : n;
 int c = memcmp(text,s,common); return c ? c : len-n;
}
class File;
class FileScan00487F80 { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual bool scanString(AsciiString &s);
};
class Display00487F80 { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28();
 virtual int getWidth(); virtual int getHeight();
};
extern Display00487F80 *display00487F80;
class HeaderTemplateManager { public: GameFont *getFontFromTemplate(AsciiString name); };
extern HeaderTemplateManager *TheHeaderTemplateManager;
void readUntilSemicolon(File*,char*,int);
extern "C" void *Rva00484F60GetDataTemplate(char*,unsigned int*);
bool parseScreenRect(int*,int*,int*,int*);
bool parseChildWindows(GameWindow*,File*,char*);
struct GameWindowParse { char *name; bool (*parse)(char*,WinInstanceData*,char*,void*); };
extern GameWindowParse gameWindowFieldList[];
static Open2479440Record windowRecord;
static unsigned int defTextColor;
static GameFont *defFont;
enum { WIN_BUFFER_LENGTH = 2048 };
static char *seps = " =;\n\r\t";
// Retail EntryData uses a flags word at +0x0c and is 0x28 bytes.
struct EntryData004850C0 { void *text,*sText,*constructText; unsigned int field0c; short maxTextLen; bool secretText; char tail[21]; };
struct LocalListboxData : ListboxData { char retailExtra[8]; };
static __declspec(noinline) Bool parseData( void **data, char *type, char *buffer )
{
  char *c;
  static EntryData004850C0 eData;
  static SliderData sData;
  static LocalListboxData lData;
  static TextData tData;
	static RadioButtonData rData;
	static ComboBoxData cData;

  if( !strcmp( type, "VERTSLIDER" ) || !strcmp( type, "HORZSLIDER" ) ) 
	{

    memset( &sData, 0, sizeof( SliderData ) );

	  c = strtok( buffer, " \t\n\r" );
    sData.minVal = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    sData.maxVal = atoi(c);

    *data = &sData;

  } 
	else if( !strcmp( type, "SCROLLLISTBOX" ) ) 
	{

    memset( &lData, 0, sizeof( LocalListboxData ) );

	  c = strtok( buffer, " \t\n\r" );
    lData.listLength = atoi(c);

//	  c = strtok( NULL, " \t\n\r" );
//    lData.entryHeight = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoScroll = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoPurge = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.scrollBar = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.multiSelect = atoi(c);

		c = strtok( NULL, " \t\n\r" );
		lData.forceSelect = atoi(c);
		
    *data = &lData;

  } 
	else if( !strcmp( type, "ENTRYFIELD" ) ) 
	{

    memset( &eData, 0, sizeof( EntryData004850C0 ) );

	  c = strtok( buffer, " \t\n\r" );
    eData.maxTextLen = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
//    if (c)
//      eData.entryWidth = atoi(c);
//    else
//      eData.entryWidth = -1;

		c = strtok( NULL, " \t\n\r" );
		if (c)
		{
			eData.secretText = atoi(c);

			if( eData.secretText != FALSE )
				eData.secretText = TRUE;
		}
		else
			eData.secretText = FALSE;

        eData.field0c = 0;
        c = strtok(NULL, " \t\n\r");
        if (c) {
            if (atoi(c) == 1) eData.field0c |= 0x20;
            if (atoi(c) == 2) eData.field0c |= 0x40;
            if (atoi(c) == 3) eData.field0c |= 0x10;
        }
    *data = &eData;

  } 
	else if( !strcmp( type, "STATICTEXT" ) ) 
	{

	  c = strtok( buffer, " \t\n\r" );
    tData.centered = atoi(c);
		
		if( tData.centered != FALSE )
			tData.centered = TRUE;

	  c = strtok( NULL, " \t\n\r" );

		/** @todo need to get a label from the translation manager, uncomment
		the following line and remove the WideChar assignment when
		we have it */
//		text = StringManagerFetch( c );
//		text = L"Need StrManager, Remove me!";
//		TheWindowManager->winStrcpy( tData.text, text );

		*data = &tData;

  }
	else if( !strcmp( type, "RADIOBUTTON" ) ) 
	{ 

		c = strtok( buffer, " \t\n\r" );
		rData.group = atoi(c);
/// @todo Colin: Why was this here???
//		if( tData.centered != FALSE )
//		{
//			tData.centered = TRUE;
//		}
		*data = &rData;
	}	
	else
    *data = NULL;

  return TRUE;

}  // end parseData
GameWindow *parseWindow( File *inFile, char *buffer )
{
	GameWindowParse *parse;
	GameWindow *window = NULL;
	
	WinInstanceData instData;
 windowRecord.field00 = peekWindow();
	char type[64];
	char token[ 256 ];
	char *c;
	void *data = NULL;
	ICoord2D parentSize;
	AsciiString asciibuf;

	//
	// reset our 'static globals' that house the current parsed window callback
	// definitions to empty
	//
	windowRecord.field18 = 0;
 windowRecord.field1c = 0;
 windowRecord.field20 = 0;
 windowRecord.field28 = 0;
 windowRecord.field24 = 0;
 windowRecord.field2c = 0;
	theSystemString.clear();
	theInputString.clear();
	theTooltipString.clear();
	theDrawString.clear();

	// get the size of the parent, or if no parent present the screen
	if( windowRecord.field00 )
	{
		windowRecord.field00->winGetSize( &parentSize.x, &parentSize.y );
	}  // end if
	else
	{
		parentSize.x = display00487F80->getWidth();
		parentSize.y = display00487F80->getHeight();
	}  // end else

	// Initialize the instance data to the defaults
	/// @todo need to support enabled/disabled/hilite text colors here
	instData.init();
	instData.m_enabledText.color = defTextColor;
	instData.m_enabledText.borderColor = defTextColor;
	instData.m_disabledText.color = defTextColor;
	instData.m_disabledText.borderColor = defTextColor;
	instData.m_hiliteText.color = defTextColor;
	instData.m_hiliteText.borderColor = defTextColor;

	/// @todo need real font support here
	instData.m_font = defFont;

	//
	// read the first few lines that are required to be first in a 
	// window definition file including position, size, type, and id
	//

	// window type
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );	
	c = strtok( buffer, seps );
	assert( strcmp( c, "WINDOWTYPE" ) == 0 );
	c = strtok( NULL, seps );  // get data to right of = sign
	strcpy( type, c );

	//
	// based on the window type get a pointer for any specific data
	// for the gadget controls needed
	//
	data = Rva00484F60GetDataTemplate( type, 0 );
	
	// position
	readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );	
	// Preserve retail's token spill from the former token/buffer parser ABI.
 char *volatile screenToken = strtok( buffer, seps );
 (void)&screenToken;
	assert( strcmp( screenToken, "SCREENRECT" ) == 0 );
	if( parseScreenRect( &windowRecord.field08, &windowRecord.field0c, &windowRecord.field10, &windowRecord.field14 ) == FALSE )
		goto cleanupAndExit;

	// parse all the field definitions
	while( TRUE ) 
	{

		// get token
		((FileScan00487F80*)inFile)->scanString(asciibuf);

		// parse field
		for( parse = gameWindowFieldList; parse->parse; parse++ ) 
		{

			if (asciibuf.compare(parse->name) == 0)
			{
				
				strcpy( token, asciibuf.str() );

				// eat '='
				((FileScan00487F80*)inFile)->scanString(asciibuf);

				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

				if (parse->parse( token, &instData, buffer, data ) == FALSE ) 
				{
					DEBUG_LOG(( "parseGameObject: Error parsing %s\n", parse->name ));
					goto cleanupAndExit;
				}

				break;
			}

		}  // end for

		if( parse->parse == NULL ) 
		{

			// If it's the END keyword
			if (asciibuf.compare("DATA") == 0)
			{

				// eat '='
				((FileScan00487F80*)inFile)->scanString(asciibuf);

				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

				if( parseData( &data, type, buffer ) == FALSE ) 
				{
					DEBUG_LOG(( "parseGameWindow: Error parsing %s\n", parse->name ));
					goto cleanupAndExit;
				}

			} 
			else if (asciibuf.compare("END") == 0)
			{
				// Check to see if we have a header template, if so, set the font equal to that.
				if(TheHeaderTemplateManager->getFontFromTemplate(instData.m_headerTemplateName))
					instData.m_font = TheHeaderTemplateManager->getFontFromTemplate(instData.m_headerTemplateName);

				// Create a window using the current description
				if( window == NULL )
					{ windowRecord.dword_30 = &instData; windowRecord.field04 = instData.getStatus(); window = createWindow(type,instData.m_id,&windowRecord,data); }

				
				goto cleanupAndExit;

			} 
			else if (asciibuf.compare("CHILD") == 0)
			{

				// Create a window using the current description
				{ windowRecord.dword_30 = &instData; windowRecord.field04 = instData.getStatus(); window = createWindow(type,instData.m_id,&windowRecord,data); }

				if (window == NULL)
					goto cleanupAndExit;

				// Parses the CHILD's window info.
				if( parseChildWindows( window, inFile, buffer ) == FALSE )
				{

					((Rva004874A0ManagerView*)TheWindowManager)->s78( window );
					window = NULL;
					goto cleanupAndExit;

				}  // end if

			} 
			else 
			{

				// Else it is unrecognized so eat associated data
				readUntilSemicolon( inFile, buffer, WIN_BUFFER_LENGTH );

			}

		}  // end if

	}  // end while( TRUE )

cleanupAndExit:

	//
	// this should be true since we should never set the text in
	// display strings in a instance data that is not inside a
	// window ... it's for sanity checking
	//
	// I am commenting this out to get tooltips working, If for
	// some reason we start having displayString problems... CLH
//	assert( instData.m_text == NULL && instData.m_tooltip == NULL );

	return window;

}  // end parseWindow
