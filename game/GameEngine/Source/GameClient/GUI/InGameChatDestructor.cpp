// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00511F50: virtual destructor of the InGameChat.apt screen.
// Resets both vtables, unregisters AptInGameChat::InitGadgets when this is
// the published singleton, then destroys the two 0x10-byte slots at +0x270
// and +0x280 before the APT window base.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x250 ];
};

void _bfme_closeAptScreen( const AsciiString &name );

class InGameChatSlot
{
public:
	~InGameChatSlot();

private:
	char m_unmodelled[ 0x10 ];
};

extern const void *BfmeAptScreenInGameChatVftable[];
extern const void *BfmeAptScreenInGameChatSecondaryVftable[];
class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;

class AptInGameChat : public _bfme_AptGameWindow
{
public:
	virtual ~AptInGameChat();

private:
	char m_pad[ 0x1C ];
	InGameChatSlot m_slot0;
	InGameChatSlot m_slot1;
};

// ??1AptInGameChat@@UAE@XZ
AptInGameChat::~AptInGameChat()
{
	*(const void ***)( this ) = BfmeAptScreenInGameChatVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenInGameChatSecondaryVftable;

	if( reinterpret_cast<void * &>(g_Rva005127A0InGameChat) == this )
	{
		{
			AsciiString name( "AptInGameChat::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		reinterpret_cast<void * &>(g_Rva005127A0InGameChat) = 0;
	}
}
