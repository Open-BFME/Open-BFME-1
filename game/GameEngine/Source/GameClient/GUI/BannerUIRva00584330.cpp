// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x00584330 (435 bytes, ret 4). Places a banner in the first of
// the two BannerUI banner slots that no movie entry occupies, and returns the
// slot or -1. The banner type name comes from a game logic callee (ILT
// 0x00033244, pinned as BfmeThingDVB::bfmeGoDVBc), falls back to BannerRohan,
// and is looked up in the banner type table at BannerUI+8. The slot's
// AddBanner call, the new movie entry, and the APT:BannerTimer%d text reset
// follow. The vector at +0x30 of 28-byte movie entries is what BannerUI.cpp
// models, so the class is BannerUI and the method keeps its address in the
// name. The callee fills the name string in place, so BannerName has no
// constructor stores of its own and EH tracking starts after the call. The
// table pointer of the lookup result is volatile because retail stores it to
// the frame and nothing reads it back.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const char *text );
	void __cdecl format( AsciiString fmt, ... );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

extern const unsigned short g_Rva01088AF4EmptyWideString[];

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

struct BfmeTaggedRecord
{
	int m_bfmeValue;
	unsigned int m_bfmeTag;
	char m_bfmeFields[ 0x14 ];
};

struct BfmeTaggedPair
{
	BfmeTaggedPair() {}
	BfmeTaggedPair( BfmeTaggedRecord *a ) { for ( int i = 0; i < 2; ++i ) m_bfmeRecords[ i ] = a; }

	BfmeTaggedRecord *m_bfmeRecords[ 2 ];
};

BfmeTaggedPair bfmeScanTaggedPair( BfmeTaggedRecord *first, BfmeTaggedRecord *last, BfmeTaggedPair found );

struct BannerMovieEntry
{
	BannerMovieEntry( int player ) : m_at00( false ), m_at08( player ), m_at0c( 0 ), m_at10( 0 ), m_at14( 0 ), m_at18( -1 ) {}

	bool m_at00;
	int m_id;
	int m_at08;
	void *m_at0c;
	int m_at10;
	int m_at14;
	int m_at18;
};

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		void push_back( const T &value );
		T *begin() { return m_start; }
		T *end() { return m_finish; }

		T *m_start;
		T *m_finish;
		T *m_capacity;
	};
}

struct BannerTypeValue
{
	AsciiString m_name;
	AsciiString m_label;
};

struct BannerTypeNode
{
	char m_pad00[ 8 ];
	BannerTypeValue m_value;
};

class BfmeThingDVB
{
public:
	void *bfmeGoDVBc( void *a, void *b );
};

struct BannerNameStorage
{
	void *m_data;
};

class BannerName : private BannerNameStorage
{
public:
	BannerName( BfmeThingDVB *logic, int player )
	{
		logic->bfmeGoDVBc( this, (void *)player );
	}
	~BannerName() { ( (AsciiString *)this )->~AsciiString(); }
	bool isEmpty( void ) const { return m_data == 0 || ((unsigned short *)m_data)[ 2 ] == 0; }
	AsciiString &ascii( void ) { return *(AsciiString *)this; }
};

// Retail spells this global `GameLogic *TheGameLogic` (?TheGameLogic@@3PAVGameLogic@@A),
// defined once in GameLogic.cpp. The only use casts it straight to the DVB
// view type, so no TU-local view is needed.
class GameLogic;
extern GameLogic *TheGameLogic;

void AddBanner( int id, const AsciiString &name, const AsciiString &label );

extern void j_00048bd0();

struct BannerTypeIterator
{
	BannerTypeNode *m_node;
	void *volatile m_table;
};

class BannerTypeLookup
{
};

typedef BannerTypeNode *(BannerTypeLookup::*FindTypeCall)( const AsciiString &key );

template <class F> static __forceinline F bannerCall( void ( *raw )() )
{
	union { void ( *raw )(); F typed; } call;
	call.raw = raw;
	return call.typed;
}

class BannerUI
{
public:
	int rva00584330( int player );

private:
	char m_pad00[ 8 ];
	char m_types[ 0x14 ];
	char m_pad1c[ 0x14 ];
	_STL::vector<BannerMovieEntry> m_movieEntries;
};

int BannerUI::rva00584330( int player )
{
	BannerMovieEntry entry( player );
	BfmeTaggedPair found;
	found = bfmeScanTaggedPair(
		(BfmeTaggedRecord *)m_movieEntries.begin(),
		(BfmeTaggedRecord *)m_movieEntries.end(),
		BfmeTaggedPair( 0 ) );

	int slot;
	for ( slot = 0; slot < 2; ++slot )
	{
		if ( found.m_bfmeRecords[ slot ] == 0 )
			goto done;
	}
	slot = 2;
done:
	entry.m_id = slot;
	if ( (unsigned int)slot >= 2 )
		return -1;

	BannerName type( (BfmeThingDVB *)TheGameLogic, player );
	if ( type.isEmpty() )
		type.ascii() = "BannerRohan";

	void *types = m_types;
	BannerTypeIterator it;
	it.m_node = ( ( (BannerTypeLookup *)types )->*bannerCall<FindTypeCall>( j_00048bd0 ) )( type.ascii() );
	it.m_table = types;
	if ( it.m_node == 0 )
		return -1;
	BannerTypeNode *node = it.m_node;
	BannerTypeValue *value = &node->m_value;
	entry.m_at0c = value;
	AddBanner( slot, value->m_name, value->m_label );
	m_movieEntries.push_back( entry );

	AsciiString text;
	text.format( AsciiString( "APT:BannerTimer%d" ), slot );
	g_theWindowManager->bfme_setAptText( text, UnicodeString( g_Rva01088AF4EmptyWideString ) );
	return slot;
}
