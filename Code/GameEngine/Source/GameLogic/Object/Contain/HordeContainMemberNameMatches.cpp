// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the horde-container test that asks whether one member's slot
// carries a given name, retail 0x00242630.
//
// The member's id at Object+0x74 goes through the same index map at this+0x120
// that BfmeConv776 already pins -- the map lookup at 0x0001F91F taking the
// address of the key and returning the address of the value -- and the value it
// yields indexes the sixteen-byte slot table at this+0x12c. Only the slot's
// first word is read, and that word is what the search matches on.
//
// The search walks the owner's pointer vector at owner+0x224..owner+0x228 and
// stops at the FIRST entry whose key matches: retail's `je` leaves the loop for
// the name compare and the compare's failure exit is the same `xor al, al` the
// exhausted loop falls into, so a key match that fails the name test does not
// resume the walk.
//
// Like the release hook next door the function has no frame; the key temp the
// map lookup needs lives in the incoming member parameter's own stack slot,
// which is free because the parameter has already been consumed.

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int bfmeCompare( const AsciiString &other ) const;		///< ILT thunk at 0x000220C5

private:
	void *m_bfmeData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[ 0x74 ];
	void *m_bfmeId;										///< retail this+0x74
};

class BfmeHordeRosterEntry
{
public:
	void *m_bfmeKey;									///< retail this+0x00
	AsciiString m_bfmeName;								///< retail this+0x04
	char m_bfmeTail[ 8 ];
};

class BfmeHordeRosterOwner
{
public:
	char m_bfmeHead[ 0x224 ];
	BfmeHordeRosterEntry **m_bfmeBegin;					///< retail this+0x224
	BfmeHordeRosterEntry **m_bfmeEnd;					///< retail this+0x228
};

class BfmeHordeSlot
{
public:
	void *m_bfmeKey;									///< retail this+0x00
	char m_bfmeTail[ 0xc ];
};

// the index map BfmeConv776 pins at 0x0001F91F
class BfmeSubDSU
{
public:
	void **bfmeTwoDSU( void **what );
};

class BfmeHordeContainRoster
{
public:
	Bool bfmeMemberNameMatches( Object *member, const AsciiString &name );

private:
	char m_bfmeHead[ 4 ];
	BfmeHordeRosterOwner *m_bfmeOwner;					///< retail this+0x04
	char m_bfmeGap[ 0x120 - 0x08 ];
	BfmeSubDSU m_bfmeIndices;							///< retail this+0x120
	char m_bfmeGap2[ 0x12c - 0x124 ];
	BfmeHordeSlot *m_bfmeSlots;							///< retail this+0x12c
};

// ?bfmeMemberNameMatches@BfmeHordeContainRoster@@QAE_NPAVObject@@ABVAsciiString@@@Z
Bool BfmeHordeContainRoster::bfmeMemberNameMatches( Object *member, const AsciiString &name )
{
	void *key = member->m_bfmeId;
	void *slotKey = m_bfmeSlots[ (unsigned int)*m_bfmeIndices.bfmeTwoDSU( &key ) ].m_bfmeKey;

	BfmeHordeRosterOwner *owner = m_bfmeOwner;

	for ( BfmeHordeRosterEntry **cursor = owner->m_bfmeBegin; cursor != owner->m_bfmeEnd; ++cursor )
	{
		BfmeHordeRosterEntry *entry = *cursor;

		if ( slotKey == entry->m_bfmeKey )
		{
			if ( entry->m_bfmeName.bfmeCompare( name ) == 0 )
				return true;

			break;
		}
	}

	return false;
}
