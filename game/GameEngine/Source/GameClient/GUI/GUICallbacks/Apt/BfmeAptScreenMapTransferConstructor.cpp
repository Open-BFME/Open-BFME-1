// ??0BfmeAptScreenMapTransfer@@QAE@PAX@Z
// partial score=0.86 date=2026-09-10
// cl: /DNDEBUG /MD /GX
// Scratch reconstruction of the APT FileTransfer screen constructor at
// retail 0x005104C0.  The named factory at 0x00510A10 allocates 0x58 bytes
// and calls this constructor; the vtable and the callback target identify it
// as BfmeAptScreenMapTransfer rather than the legacy MapTransferLoadScreen.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text )
		: StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class GameSlot
{
public:
	bool isHuman() const;
	UnicodeString getName() const;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot( int index ) const;
};

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function,
		int argumentCount, const void *argument1, const void *argument2,
		int unused1, int unused2, int unused3 );
	void bfme_setAptText( const AsciiString &name,
		const UnicodeString &text );
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

class Rva0050FE50Host
{
public:
	void bfmeProvide( int index, char *output, bool setting );
};

typedef void ( Rva0050FE50Host::*MapTransferCallback )(
	int, char *, bool );

typedef Rva0050FE50Host FunctorTargetSingle;
typedef MapTransferCallback FunctorMethodSingle;

struct FunctorBindingSingle
{
	FunctorBindingSingle( FunctorTargetSingle *target,
		FunctorMethodSingle method )
		: m_target( target ), m_method( method ) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_refCount( 0 ) {}
	virtual void functorSingleWrapperAnchor();
	unsigned int m_refCount;
};

class MapTransferColorFunctorWrapper : public FunctorSingleWrapperHead
{
public:
	MapTransferColorFunctorWrapper( const FunctorBindingSingle &binding )
		: m_binding( binding ) {}

	FunctorBindingSingle m_binding;
};

class Rva0050F920FunctorHolder
{
public:
	Rva0050F920FunctorHolder( FunctorBindingSingle binding )
	{
		m_ptr = new MapTransferColorFunctorWrapper( binding );
		if( m_ptr )
			m_ptr->m_refCount++;
	}

	Rva0050F920FunctorHolder( const Rva0050F920FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0050F920FunctorHolder()
	{
		FunctorSingleWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	MapTransferColorFunctorWrapper *m_ptr;
};

class _bfme_AptGameWindow
{
public:
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

	void *m_vtable;
	unsigned int m_unmodelled[ 12 ];
};

class BfmeAptScreenMapTransferBase
{
public:
	virtual ~BfmeAptScreenMapTransferBase();

	struct AptVector
	{
		void *begin;
		void *end;
		void *capacity;
		AptVector() : begin( 0 ), end( 0 ), capacity( 0 ) {}
	};
	struct AptVectorTwo
	{
		void *a;
		void *b;
		AptVectorTwo() : a( 0 ), b( 0 ) {}
	};
	struct AptVectorOne
	{
		void *a;
		AptVectorOne() : a( 0 ) {}
	};

	AptVector m_vec0;
	AptVector m_vec1;
	AptVector m_vec2;
	AptVectorTwo m_vec3a;
	AptVectorOne m_vec3b;
};

class BfmeAptScreenMapTransfer : public BfmeAptScreenMapTransferBase
{
public:
	virtual ~BfmeAptScreenMapTransfer();
	BfmeAptScreenMapTransfer( void *context );
	void processProgress( int playerId, int percentage, UnicodeString text );

private:
	GameInfo *m_game;
	int m_playerLookup[ 8 ];
};

extern WindowManager *g_theWindowManager;
extern GameTextInterface *TheGameText;
extern BfmeAptScreenMapTransfer *TheBfmeAptScreenMapTransfer;
extern const unsigned short BFMEEmptyString[];

BfmeAptScreenMapTransfer::BfmeAptScreenMapTransfer( void *context )
{
	*(void **)this = (void *)0x01104FF8;
	m_game = (GameInfo *)context;
	if( TheBfmeAptScreenMapTransfer )
		return;

	TheBfmeAptScreenMapTransfer = this;
	g_theWindowManager->unidentified_00015235(
		0x0B, "FileTransferPopUpOpen", 0, 0, 0, 0, 0, 0 );

	for( int *lookup = m_playerLookup;
		lookup != m_playerLookup + 8; ++lookup )
		*lookup = -1;

	int display = 0;
	for( int i = 0; i < 8; ++i )
	{
		const GameSlot *slot = ((GameInfo *)context)->getConstSlot( i );
		if( slot == 0 || !slot->isHuman() )
			continue;

		m_playerLookup[ i ] = display;
		AsciiString variableName;
		variableName.format( (AsciiString)"FileTransfer::PlayerName%d", display );
		g_theWindowManager->bfme_setAptText( variableName, slot->getName() );

		variableName.format( (AsciiString)"FileTransfer:PlayerColor:%d", display );
		MapTransferCallback callback =
			(MapTransferCallback)&Rva0050FE50Host::bfmeProvide;
		((_bfme_AptGameWindow *)this)->_bfme_showAptScreenWithArg(
			variableName, (void *)i,
			Rva0050F920FunctorHolder( FunctorBindingSingle(
				(Rva0050FE50Host *)this, callback ) ) );
		processProgress( display, 0, UnicodeString( BFMEEmptyString ) );
		++display;
	}

	for( ; display < 8; )
	{
		AsciiString variableName;
		variableName.format( (AsciiString)"FileTransfer::PlayerName%d", display );
		{
			UnicodeString blank( BFMEEmptyString );
			g_theWindowManager->bfme_setAptText( variableName, blank );
		}

		variableName.format( (AsciiString)"FileTransfer::Status%d", display );
		{
			UnicodeString blankStatus( BFMEEmptyString );
			g_theWindowManager->bfme_setAptText( variableName, blankStatus );
		}

		variableName.format( (AsciiString)"FileTransfer:PlayerColor:%d", display );
		MapTransferCallback callback =
			(MapTransferCallback)&Rva0050FE50Host::bfmeProvide;
		((_bfme_AptGameWindow *)this)->_bfme_showAptScreenWithArg(
			variableName, (void *)-1,
			Rva0050F920FunctorHolder( FunctorBindingSingle(
				(Rva0050FE50Host *)this, callback ) ) );
		++display;
	}

	{
		AsciiString name( "APT:FileTransferLoadingPlayerName" );
		g_theWindowManager->bfme_setAptText( name,
			TheGameText->fetch( "GUI:PlayerName" ) );
	}
	{
		AsciiString name( "APT:FileTransferLoadingProgress" );
		g_theWindowManager->bfme_setAptText( name,
			TheGameText->fetch( "GUI:Progress" ) );
	}
	{
		AsciiString name( "APT:FileTransferLoadingStatus" );
		g_theWindowManager->bfme_setAptText( name,
			TheGameText->fetch( "GUI:Status" ) );
	}
}
