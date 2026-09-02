// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0050FFC0: APT-era MapTransferLoadScreen::processProgress.  Writes
// FileTransfer::Status%d through bfme_setAptText and drives SetBarTo on
// movie 0xB.  Lookup table at this+0x38; by-value UnicodeString is the
// status line.

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ... );

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, int unused1, int unused2,
		int unused3 );
};

extern WindowManager *g_theWindowManager;

class BfmeAptScreenMapTransfer
{
public:
	void processProgress( int playerId, int percentage, UnicodeString text );

private:
	char m_head[ 0x38 ];
	int m_playerLookup[ 8 ];
};

// ?processProgress@BfmeAptScreenMapTransfer@@QAEXHHVUnicodeString@@@Z
void BfmeAptScreenMapTransfer::processProgress(
	int playerId, int percentage, UnicodeString text )
{
	if( playerId < 0 || playerId >= 8 )
		return;

	int slot = m_playerLookup[ playerId ];
	if( slot == -1 )
		return;

	AsciiString variableName;
	variableName.format( (AsciiString)"FileTransfer::Status%d", slot );
	g_theWindowManager->bfme_setAptText( variableName, text );

	char slotText[ 64 ];
	char percentText[ 64 ];
	sprintf( slotText, "%d", slot );
	sprintf( percentText, "%d", percentage );
	g_theWindowManager->unidentified_00015235(
		0x0B, "SetBarTo", 2, slotText, percentText, 0, 0, 0 );
}
