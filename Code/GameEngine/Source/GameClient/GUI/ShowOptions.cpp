// cl: /DNDEBUG /MD
//
// Retail 0x0055E290: zero the 10 option-flag bytes, then open Options.apt
// unless the Options singleton at 0x012F4AD4 already exists.  The two
// incoming bytes are stored at 0x012F4AD1 / 0x012F4AD0 for the screen.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
extern void *g_obj12F4AD4;
extern unsigned char g_optByte12F4AD0;
extern unsigned char g_optByte12F4AD1;
extern unsigned char g_optFlag12F4AD8;
extern unsigned char g_optFlag12F4AD9;
extern unsigned char g_optFlag12F4ADA;
extern unsigned char g_optFlag12F4ADB;
extern unsigned char g_optFlag12F4ADC;
extern unsigned char g_optFlag12F4ADD;
extern unsigned char g_optFlag12F4ADE;
extern unsigned char g_optFlag12F4ADF;
extern unsigned char g_optFlag12F4AE0;
extern unsigned char g_optFlag12F4AE1;

// ?_bfme_showOptions@@YAXHH@Z
void _bfme_showOptions( int a, int b )
{
	g_optFlag12F4AD8 = 0;
	g_optFlag12F4AD9 = 0;
	g_optFlag12F4ADA = 0;
	g_optFlag12F4ADB = 0;
	g_optFlag12F4ADC = 0;
	g_optFlag12F4ADD = 0;
	g_optFlag12F4ADE = 0;
	g_optFlag12F4ADF = 0;
	g_optFlag12F4AE0 = 0;
	g_optFlag12F4AE1 = 0;
	if( g_obj12F4AD4 == 0 )
	{
		g_optByte12F4AD1 = (unsigned char)a;
		g_optByte12F4AD0 = (unsigned char)b;
		TheShell->push( AsciiString( "Options.apt" ), false );
	}
}
