// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/shims/functionlexicon /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Retail 0x0046A870 creates and annotates the script main window.

#include <list>

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

template <typename T> class StringBase
{
public:
	struct Data
	{
		int m_refCount;
		int m_length;
		T m_text[ 1 ];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase() {}
	void set( const StringBase<T> &other );
	void concat( const T *text, int length );

	Data *m_data;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

class UnicodeString;

class StringBaseG
{
	friend class UnicodeString;

	private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() { ((BFMERetailAsciiString *)this)->releaseBuffer(); }
	void concat( const char *text, int length )
	{
		((StringBase<char> *)this)->concat( text, length );
	}
	const char *str() const
	{
		return m_data ? (const char *)((const char *)m_data + 8) : (const char *)0x0107388b;
	}
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<UnsignedShort>( other ) {}
	~UnicodeString() { ((StringBaseG *)this)->releaseBuffer(); }
	void translate( const AsciiString &source );
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class Rva0046A870Manager;

class FunctionLexicon
{
public:
	enum TableIndex
	{
		TABLE_ANY = -1,
		TABLE_MAIN_WINDOW = 11
	};

	void *rva00105480( NameKeyType key, TableIndex index );

protected:
	void *findFunction( NameKeyType key, TableIndex index );

private:
	friend class Rva0046A870Manager;
};

class GameWindow;

struct Rva0046A870WindowDesc
{
	GameWindow *m_parent;
	UnsignedInt m_status;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	void *m_system;
	void *m_instanceData;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2C;
	int m_field30;
};

class GameWindow
{
public:
	int winSetText( UnicodeString text );

	unsigned char m_head[ 0x1f4 ];
	void *m_field1F4;
};

class Rva0046A870FoundWindow
{
public:
	unsigned char m_pad00[ 0x24c ];
	StringBase<char> m_name;
};

typedef std::list<GameWindow *> GameWindowList;

class WindowLayoutInfo
{
public:
	UnsignedInt m_version;
	void *m_init;
	void *m_update;
	void *m_shutdown;
	void *m_callback;
	AsciiString m_initName;
	AsciiString m_updateName;
	AsciiString m_shutdownName;
	AsciiString m_unknown20;
	AsciiString m_unknown24;
	GameWindowList m_windows;
};

#define GAME_WINDOW_MANAGER_SLOT(n) virtual void slot##n() = 0
class GameWindowManager
{
public:
	GAME_WINDOW_MANAGER_SLOT(00); GAME_WINDOW_MANAGER_SLOT(01); GAME_WINDOW_MANAGER_SLOT(02);
	GAME_WINDOW_MANAGER_SLOT(03); GAME_WINDOW_MANAGER_SLOT(04); GAME_WINDOW_MANAGER_SLOT(05);
	GAME_WINDOW_MANAGER_SLOT(06); GAME_WINDOW_MANAGER_SLOT(07); GAME_WINDOW_MANAGER_SLOT(08);
	GAME_WINDOW_MANAGER_SLOT(09); GAME_WINDOW_MANAGER_SLOT(10); GAME_WINDOW_MANAGER_SLOT(11);
	GAME_WINDOW_MANAGER_SLOT(12); GAME_WINDOW_MANAGER_SLOT(13); GAME_WINDOW_MANAGER_SLOT(14);
	GAME_WINDOW_MANAGER_SLOT(15); GAME_WINDOW_MANAGER_SLOT(16); GAME_WINDOW_MANAGER_SLOT(17);
	GAME_WINDOW_MANAGER_SLOT(18); GAME_WINDOW_MANAGER_SLOT(19); GAME_WINDOW_MANAGER_SLOT(20);
	GAME_WINDOW_MANAGER_SLOT(21); GAME_WINDOW_MANAGER_SLOT(22); GAME_WINDOW_MANAGER_SLOT(23);
	GAME_WINDOW_MANAGER_SLOT(24); GAME_WINDOW_MANAGER_SLOT(25); GAME_WINDOW_MANAGER_SLOT(26);
	GAME_WINDOW_MANAGER_SLOT(27); GAME_WINDOW_MANAGER_SLOT(28);
	virtual GameWindow *winCreate( Rva0046A870WindowDesc *desc ) = 0;
	GAME_WINDOW_MANAGER_SLOT(30); GAME_WINDOW_MANAGER_SLOT(31); GAME_WINDOW_MANAGER_SLOT(32);
	GAME_WINDOW_MANAGER_SLOT(33); GAME_WINDOW_MANAGER_SLOT(34); GAME_WINDOW_MANAGER_SLOT(35);
	GAME_WINDOW_MANAGER_SLOT(36); GAME_WINDOW_MANAGER_SLOT(37); GAME_WINDOW_MANAGER_SLOT(38);
	GAME_WINDOW_MANAGER_SLOT(39); GAME_WINDOW_MANAGER_SLOT(40); GAME_WINDOW_MANAGER_SLOT(41);
	GAME_WINDOW_MANAGER_SLOT(42); GAME_WINDOW_MANAGER_SLOT(43); GAME_WINDOW_MANAGER_SLOT(44);
	GAME_WINDOW_MANAGER_SLOT(45); GAME_WINDOW_MANAGER_SLOT(46); GAME_WINDOW_MANAGER_SLOT(47);
	GAME_WINDOW_MANAGER_SLOT(48); GAME_WINDOW_MANAGER_SLOT(49); GAME_WINDOW_MANAGER_SLOT(50);
	GAME_WINDOW_MANAGER_SLOT(51); GAME_WINDOW_MANAGER_SLOT(52);
	virtual void findWindowAtLevel( GameWindow *window, int level, int timeout,
		Rva0046A870FoundWindow **result ) = 0;
};
#undef GAME_WINDOW_MANAGER_SLOT

extern NameKeyGenerator *TheNameKeyGenerator;
extern FunctionLexicon *TheFunctionLexicon;
extern GameWindowManager *TheWindowManager;

#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00105480@FunctionLexicon@@QAEPAXW4NameKeyType@@W4TableIndex@1@@Z=?j_00015a28@@YAXXZ")
#pragma comment(linker, "/alternatename:?findFunction@FunctionLexicon@@IAEPAXW4NameKeyType@@W4TableIndex@1@@Z=?j_00025cd4@@YAXXZ")
#pragma comment(linker, "/alternatename:?winSetText@GameWindow@@QAEHVUnicodeString@@@Z=?j_00049c33@@YAXXZ")
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")
#pragma comment(linker, "/alternatename:??1?$StringBase@G@@QAE@XZ=?releaseBuffer@StringBaseG@@AAEXXZ")
#pragma comment(linker, "/alternatename:?push_back@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@std@@@std@@QAEXABQAVGameWindow@@@Z=?j_000452a0@@YAXXZ")

class Rva0046A870Manager
{
public:
	GameWindow *createMainWindow( const AsciiString &filename, WindowLayoutInfo *info );
};

// ?createMainWindow@Rva0046A870Manager@@QAEPAVGameWindow@@ABVAsciiString@@PAVWindowLayoutInfo@@@Z
GameWindow *Rva0046A870Manager::createMainWindow( const AsciiString &filename,
	WindowLayoutInfo *info )
{
	Rva0046A870WindowDesc desc;
	desc.m_parent = 0;
	desc.m_x = 0;
	desc.m_y = 0;
	desc.m_width = 0;
	desc.m_height = 0;
	desc.m_system = 0;
	desc.m_instanceData = 0;
	desc.m_field20 = 0;
	desc.m_field24 = 0;
	desc.m_field28 = 0;
	desc.m_field2C = 0;
	desc.m_field30 = 0;
	desc.m_status = 0x08000001;
	void *callback = TheFunctionLexicon->rva00105480(
		TheNameKeyGenerator->nameToKey( filename.str() ), FunctionLexicon::TABLE_ANY );
	Rva0046A870FoundWindow *result;
	desc.m_system = callback;

	if ( callback == 0 )
		return 0;

	GameWindow *window = TheWindowManager->winCreate( &desc );
	window->m_field1F4 = 0;

	result = 0;
	TheWindowManager->findWindowAtLevel( window, 0x1d, 0x7d0, &result );
	if ( result != (Rva0046A870FoundWindow *)window )
		return 0;

	StringBase<char> *storedName = &result->m_name;
	storedName->set( *(const StringBase<char> *)&filename );
	AsciiString name( filename );
	name.concat( (const char *)0x010f7284, 0xb );
	UnicodeString title;
	title.translate( name );
	window->GameWindow::winSetText( title );

	if ( info != 0 )
	{
		info->m_windows.push_back( window );
		NameKeyType key = TheNameKeyGenerator->nameToKey( filename.str() );
		void *function = TheFunctionLexicon->findFunction(
			key,
			FunctionLexicon::TABLE_MAIN_WINDOW );
		info->m_callback = function;
		if ( function == 0 )
			info->m_callback = (void *)0x00418f52;
	}

	return (GameWindow *)result;
}
