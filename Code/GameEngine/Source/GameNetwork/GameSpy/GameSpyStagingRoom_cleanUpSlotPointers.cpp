// cl: /DNDEBUG /MD /EHsc
// readable body of ?cleanUpSlotPointers@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp

// GameSpyStagingRoom::cleanUpSlotPointers, retail 0x00637CE0. Eight calls to
// GameInfo::setSlotPointer, a name the ledger already has, handing each slot's
// own address back to the base.
//
// The slots are an array at +0x58 with a stride of 0x78, and the loop walks a
// pointer rather than indexing - the address is bumped by the stride each turn
// and the counter only drives the comparison.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	unsigned char m_unmodelled_00[ 0x78 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	void setSlotPointer( Int index, GameSlot *slot );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom : public GameInfo
{
public:
	void cleanUpSlotPointers( void );

private:
	// The full 0x58, not 0x58 minus a base: GameInfo is modelled with no data
	// here and MSVC gives an empty first base no bytes at all.
	unsigned char m_unmodelled_00[ 0x58 ];
	GameSlot m_slots[ 8 ];					// +0x58
};

// ?cleanUpSlotPointers@GameSpyStagingRoom@@QAEXXZ
void GameSpyStagingRoom::cleanUpSlotPointers( void )
{
	for( Int i = 0; i < 8; ++i )
		setSlotPointer( i, &m_slots[ i ] );
}
