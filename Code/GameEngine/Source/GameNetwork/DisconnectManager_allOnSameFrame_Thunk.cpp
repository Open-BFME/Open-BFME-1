// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?allOnSameFrame@DisconnectManager@@IAE_NPAVConnectionManager@@@Z: Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp
// Lift the DisconnectManager::allOnSameFrame naked dump to clean C++.
//
// Zero Hour's DisconnectManager.cpp body with two extra conditions BFME adds to
// the guard, both on the connection manager and both keyed by the untranslated
// slot. Neither has a ZH name, so they carry _bfme_ ones describing only what
// their bodies do: the first reads a per-slot state word at conMgr+0x12080 and
// answers whether it lies between 1 and 3, and the second answers true for the
// local slot at conMgr+0x12028. The loop skips the slot when the first is true
// or the second is false.
//
// translatedSlotPosition is inlined, and its -1 case folds into the continue --
// retail never materialises the -1, it jumps straight to the next iteration.
//
// getLocalPlayerID is called twice, once for the translation and once for the
// frame comparison, exactly as ZH writes it.
//
// Retail pins the layout: the received flags are a byte array at this+0x250 and
// the frames an Int array at this+0x230, which the compiler walks with a running
// pointer rather than re-indexing.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID(void);					///< ILT thunk at 0x0004A291
	Bool isPlayerConnected(Int slot);					///< ILT thunk at 0x0001514A

	// Shape only. Reads the per-slot state word at this+0x12080 and answers
	// whether it is between 1 and 3, with further checks against the local slot
	// at this+0x12028.
	Bool _bfme_slotStateInRange(Int slot);				///< ILT thunk at 0x000486B2

	// Shape only. Answers true immediately for the local slot at this+0x12028.
	Bool _bfme_slotIsLocalOrLive(Int slot);				///< ILT thunk at 0x0001F136
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
protected:
	Bool allOnSameFrame(ConnectionManager *conMgr);

	Bool isPlayerInGame(Int slot, ConnectionManager *conMgr);	///< ILT thunk at 0x0003A648

	Int translatedSlotPosition(Int slot, Int localSlot)
	{
		if (slot < localSlot)
			return slot;
		if (slot == localSlot)
			return -1;
		return slot - 1;
	}

private:
	unsigned char m_unreconstructed_00[0x230];
	Int m_disconnectFrames[MAX_SLOTS];					///< retail this+0x230
	Bool m_disconnectFramesReceived[MAX_SLOTS];			///< retail this+0x250
};

// ?allOnSameFrame@DisconnectManager@@IAE_NPAVConnectionManager@@@Z
Bool DisconnectManager::allOnSameFrame(ConnectionManager *conMgr) {
	Bool retval = true;
	for (Int i = 0; (i < MAX_SLOTS) && (retval == true); ++i) {
		Int transSlot = translatedSlotPosition(i, conMgr->getLocalPlayerID());
		if (transSlot == -1) {
			continue;
		}
		if ((conMgr->isPlayerConnected(i) == true) && (isPlayerInGame(transSlot, conMgr) == true)
				&& (conMgr->_bfme_slotStateInRange(i) == false) && conMgr->_bfme_slotIsLocalOrLive(i)) {
			// ok, i is someone who is in the game and hasn't timed out yet or been voted out.
			if (m_disconnectFramesReceived[i] == false) {
				// we don't know what frame they are on yet.
				retval = false;
			}
			if ((m_disconnectFramesReceived[i] == true) && (m_disconnectFrames[conMgr->getLocalPlayerID()] != m_disconnectFrames[i])) {
				// We know their frame, but they aren't on the same frame as us.
				retval = false;
			}
		}
	}
	return retval;
}
