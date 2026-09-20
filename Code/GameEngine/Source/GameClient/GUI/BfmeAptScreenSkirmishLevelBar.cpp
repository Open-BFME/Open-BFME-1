// ?levelBar@BfmeAptScreenSkirmish@@QAEXXZ
// Retail 0x0057C340. Formats four faction level-bar strings and icons.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	__forceinline StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	__forceinline AsciiString() { m_data = 0; }
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void set( const char *text, int length );
	void __cdecl format( AsciiString format, ... );
};

class BfmeAptScreenSkirmish;

struct LevelBarTextTarget
{
	void invoke( AsciiString, AsciiString, AsciiString );
};
typedef void (LevelBarTextTarget::*SetLevelText)( AsciiString, AsciiString, AsciiString );

struct LevelBarIconTarget
{
	void invoke( AsciiString, void * );
};
typedef void (LevelBarIconTarget::*SetLevelIcon)( AsciiString, void * );

extern void j_0001e812();
extern void j_00028c2c();
extern char g_bfmeSideNameA1294[];
extern char g_bfmeSideNameB1294[];
extern char g_bfmeSideNameC1294[];
extern char g_bfmeSideNameD1294[];

class BfmeAptScreenSkirmish
{
public:
	void levelBar();
};

#define LEVEL_BAR_FOR_SIDE( side, length, currentKey, nextKey, imageIndex ) \
	{ \
		sideName.set( side, length ); \
		next.format( AsciiString( currentKey ) ); \
		current.format( AsciiString( nextKey ) ); \
		union { void (*asFunction)(); SetLevelText asMember; } textCast; \
		textCast.asFunction = j_0001e812; \
		(reinterpret_cast<LevelBarTextTarget *>( this )->*textCast.asMember)( \
			sideName, next, current ); \
		union { void (*asFunction)(); SetLevelIcon asMember; } iconCast; \
		iconCast.asFunction = j_00028c2c; \
		(reinterpret_cast<LevelBarIconTarget *>( this )->*iconCast.asMember)( \
			sideName, ((void **)0x012B8058)[ imageIndex ] ); \
	}

void BfmeAptScreenSkirmish::levelBar()
{
	AsciiString sideName;
	AsciiString next;
	AsciiString current;
	LEVEL_BAR_FOR_SIDE( g_bfmeSideNameA1294, 6,
		"APT:CurrentLevelA", "APT:NextLevelA", 0 );
	LEVEL_BAR_FOR_SIDE( g_bfmeSideNameB1294, 5,
		"APT:CurrentLevelB", "APT:NextLevelB", 1 );
	LEVEL_BAR_FOR_SIDE( g_bfmeSideNameD1294, 8,
		"APT:CurrentLevelC", "APT:NextLevelC", 2 );
	LEVEL_BAR_FOR_SIDE( g_bfmeSideNameC1294, 6,
		"APT:CurrentLevelD", "APT:NextLevelD", 3 );
}
