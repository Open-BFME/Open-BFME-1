// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// ??0GameSpyStagingRoom@@QAE@ABV0@@Z
// retail 0x004FA490, 395 bytes. Compiler-generated copy constructor: base
// GameInfo subobject copy-constructed first (thunk 0002DD26), then the
// GameSpyStagingRoom-owned members copied in declaration order, matching the
// matched default constructor's layout (GameSpyStagingRoom_ctor.cpp) for the
// slots/m_gameName/m_id/m_transport/m_localName prefix. The AsciiString copy
// ctor calls here (offsets 0x424, 0x444, 0x448) all resolve to the same
// tiny StringBase<char> copy ctor (0x00887B60): the task brief's callee label
// "GameSpyGroupRoom" for that address is one of hundreds of ICF aliases
// listed in reverse/symbols.csv for that address, not evidence the callee
// does anything but copy one AsciiString handle.
//
// The raw dword/byte copies between 0x428 and 0x468 reveal the true POD tail
// is wider than ZH's header (StagingRoomGameInfo.h): retail copies SIX dwords
// between m_localName and m_ladderIP where ZH's m_requiresPassword/
// m_allowObservers/m_version/m_exeCRC/m_iniCRC/m_isQM account for only four
// dwords plus two bytes, and copies FIVE dwords after m_ladderPort where ZH's
// m_reportedNum{Players,MaxPlayers,Observers} account for only three -- BFME
// widened this record on both sides, consistent with the same-shaped
// widening already proven for BuddyRequest and GameSpyGroupRoom (see
// AsciiUnicodePairCopyCtor.cpp). The two extra fields on each side have no
// provable name; they are declared with address-derived names and evidence
// left here rather than invented ZH identifiers.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

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
	AsciiString( const AsciiString &o ) : StringBase<char>( o ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &o ) : StringBase<unsigned short>( o ) {}
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot();
	GameSlot( const GameSlot &other );
	~GameSlot();
	virtual void reset();

private:
	unsigned char m_body[0x3C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	GameInfo( const GameInfo &other );
	~GameInfo();
	virtual Int bfmeVtableSlot0();
	virtual Int bfmeVtableSlot1();
	virtual void reset();

	void setSlotPointer( Int index, GameSlot *slot );

private:
	// The matched GameInfo constructor fixes the BFME base at 0x58 bytes.
	unsigned char m_body[0x54];
};

class GameSpyGameSlot : public GameSlot
{
public:
	GameSpyGameSlot();
	GameSpyGameSlot( const GameSpyGameSlot &other );

private:
	// The array constructor and cleanUpSlotPointers independently fix this stride.
	unsigned char m_body[0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
// The copy constructor's own byte offsets are the evidence for this layout
// (see file header comment); fields past m_localName and past m_ladderPort
// are wider than the ZH header by two dwords each, address-derived here.
class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	// No explicit copy ctor: the implicit, compiler-synthesized one is the
	// match (retail uses the standard MSVC array-copy-construct-with-cleanup
	// helper for m_slots, which only the implicit copy ctor emits).
	virtual void reset();

private:
	GameSpyGameSlot m_slots[8];
	UnicodeString m_gameName;
	Int m_id;
	void *m_transport;
	AsciiString m_localName;
	unsigned char m_requiresPassword;
	unsigned char m_allowObservers;
	UnsignedInt m_version;
	UnsignedInt m_exeCRC;
	UnsignedInt m_iniCRC;
	UnsignedInt m_isQM;
	unsigned char m_bfme43C;
	Int m_qmLadderType;
	AsciiString m_ladderIP;
	AsciiString m_pingStr;
	Int m_pingInt;
	UnsignedShort m_ladderPort;
	Int m_reportedNumPlayers;
	Int m_reportedMaxPlayers;
	Int m_reportedNumObservers;
	Int m_bfme460;
	Int m_bfme464;
};

// Force emission of the implicit copy constructor without heap-allocating
// (placement new keeps this a pure construct, no operator new/delete needed).
void *operator new( unsigned int, void *p ) { return p; }

void bfme_forceGameSpyStagingRoomCopyCtor( void *dest, const GameSpyStagingRoom &src )
{
	new ( dest ) GameSpyStagingRoom( src );
}
