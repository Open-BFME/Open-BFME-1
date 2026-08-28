// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/NetCommandList.h"
#include "GameNetwork/NetworkUtil.h"

/**
 * Constructor.
 */
NetCommandList::NetCommandList() {
	m_first = NULL;
	m_last = NULL;
	m_lastMessageInserted = NULL;
}

/**
 * Destructor.
 */
NetCommandList::~NetCommandList() {
	reset();
}

/**
 * Append the given list of commands to this list.
 */
// ?appendList@NetCommandList@@QAEXPAV1@@Z present-unmatched
void NetCommandList::appendList(NetCommandList *list) {
	if (list == NULL) {
		return;
	}

	// Need to do it this way because of the reference counting that needs to happen in appendMessage.
	NetCommandRef *msg = list->getFirstMessage();
	NetCommandRef *next = NULL;
	while (msg != NULL) {
		next = msg->getNext();
		NetCommandRef *temp = addMessage(msg->getCommand());
		if (temp != NULL) {
			temp->setRelay(msg->getRelay());
		}

		msg = next;
	}
}

/**
 * Return the first message in this list.
 */
// ?getFirstMessage@NetCommandList@@QAEPAVNetCommandRef@@XZ present-unmatched
NetCommandRef *NetCommandList::getFirstMessage() {
	return m_first;
}

/**
 * Remove the given message from this list.
 */
void NetCommandList::removeMessage(NetCommandRef *msg) {
	// BFME's NetCommandRef is not a MemoryPoolObject, so it carries no vptr and
	// every field sits four bytes earlier than the reference header puts it:
	// m_msg at +0, m_next at +4, m_prev at +8. Retail walks the links at those
	// offsets; the accessors would emit +8 and +0xC. Same workaround findMessage
	// in this file already uses.
	struct NetCommandRefLayout
	{
		NetCommandMsg *command;
		NetCommandRefLayout *next;
		NetCommandRefLayout *prev;
	};
	NetCommandRefLayout *ref = (NetCommandRefLayout *)msg;

	if (m_lastMessageInserted == msg) {
		m_lastMessageInserted = (NetCommandRef *)ref->next;
	}

	if (ref->prev != NULL) {
		ref->prev->next = ref->next;
	}
	if (ref->next != NULL) {
		ref->next->prev = ref->prev;
	}

	if (msg == m_first) {
		m_first = (NetCommandRef *)ref->next;
	}
	if (msg == m_last) {
		m_last = (NetCommandRef *)ref->prev;
	}

	ref->next = NULL;
	ref->prev = NULL;
}

/**
 * Initialize the list.
 */
// ?init@NetCommandList@@QAEXXZ present-unmatched
void NetCommandList::init() {
	reset();
}

/**
 * Reset the contents of this list.
 */
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/NetCommandList_reset.cpp
// ?reset@NetCommandList@@QAEXXZ present-unmatched
void NetCommandList::reset() {
	NetCommandRef *temp = m_first;
	while (m_first != NULL) {
		temp = m_first->getNext();
		m_first->setNext(NULL);
		m_first->setPrev(NULL);
		m_first->deleteInstance();
		m_first = temp;
	}
	m_last = NULL;
	m_lastMessageInserted = NULL;
}

/**
 * Insert sorts msg.  Assumes that all the previous message inserts were done using this function.
 * The message is sorted in based first on command type, then player id, and then command id.
 */
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/NetCommandList_addMessage_Thunk.cpp
// ?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z present-unmatched
// Real body 0x00673200, 609 bytes, still claimed by NetCommandList_addMessage.asm.
// The 84 accessor uses below were emitting the reference's +4/+8/+0xC offsets and
// now go through the de-pooled layout, which is what removeMessage needed too --
// so this source is closer to right than it was even though it is not matched.
// It compiles to exactly 609 bytes and the first 37 are identical, but 79% of the
// body differs with only short matching runs: the blocks are laid out in a
// different order throughout, which is a structural difference rather than the
// allocator tie-break seen elsewhere. Worth re-deriving the branch structure from
// retail rather than transforming the reference further.
// BFME's NetCommandRef is not a MemoryPoolObject, so it carries no vptr and its
// fields sit four bytes lower than the reference header puts them: m_msg at +0,
// m_next at +4, m_prev at +8. The accessors would emit +4/+8/+0xC. removeMessage
// and findMessage in this file already walk the links through a local layout;
// addMessage does the same, through L().
struct NetCommandRefLayout
{
	NetCommandMsg *command;
	NetCommandRefLayout *next;
	NetCommandRefLayout *prev;
};
static inline NetCommandRefLayout *L(void *r) { return (NetCommandRefLayout *)r; }

NetCommandRef * NetCommandList::addMessage(NetCommandMsg *cmdMsg) {
	if (cmdMsg == NULL) {
		DEBUG_ASSERTCRASH(cmdMsg != NULL, ("NetCommandList::addMessage - command message was NULL"));
		return NULL;
	}

//	UnsignedInt id = cmdMsg->getID();

	NetCommandRef *msg = NEW_NETCOMMANDREF(cmdMsg);

	if (m_first == NULL) {
		// this is the first node, so we don't have to worry about ordering it.
		m_first = msg;
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (m_lastMessageInserted != NULL) {
		// Messages that are inserted in order should just be put in one right after the other.
		// So saving the placement of the last message inserted can give us a huge boost in
		// efficiency.
		NetCommandRef *theNext = ((NetCommandRef *)L(m_lastMessageInserted)->next);
		if ((L(m_lastMessageInserted)->command->getNetCommandType() == L(msg)->command->getNetCommandType()) &&
			(L(m_lastMessageInserted)->command->getPlayerID() == L(msg)->command->getPlayerID()) &&
			(L(m_lastMessageInserted)->command->getID() < L(msg)->command->getID()) &&
			((theNext == NULL) || ((L(theNext)->command->getNetCommandType() > L(msg)->command->getNetCommandType()) ||
			 (L(theNext)->command->getPlayerID() > L(msg)->command->getPlayerID()) ||
			 (L(theNext)->command->getID() > L(msg)->command->getID())))) {

			// Make sure this command isn't already in the list.
			if (isEqualCommandMsg(L(m_lastMessageInserted)->command, L(msg)->command)) {

				// This command is already in the list, don't duplicate it.
				msg->deleteInstance();
				msg = NULL;
				return NULL;
			}

			if (theNext == NULL) {
				// this means that m_lastMessageInserted == m_last, so m_last should point to the msg that is being inserted.
				L(msg)->next = L(((NetCommandRef *)L(m_lastMessageInserted)->next));
				L(msg)->prev = L(m_lastMessageInserted);
				L(m_lastMessageInserted)->next = L(msg);
				m_lastMessageInserted = msg;
				m_last = msg;
			} else {
				L(msg)->next = L(((NetCommandRef *)L(m_lastMessageInserted)->next));
				L(msg)->prev = L(m_lastMessageInserted);
				L(m_lastMessageInserted)->next = L(msg);
				L(msg)->next->prev = L(msg);
				m_lastMessageInserted = msg;
			}
			return msg;
		}
	}
	
	if (L(msg)->command->getNetCommandType() > L(m_last)->command->getNetCommandType()) {
		// easy optimization for a command that goes at the end of the list
		// since they are likely to be added in order.

		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_last)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			msg = NULL;
			return NULL;
		}

		L(msg)->prev = L(m_last);
		L(msg)->next = (NetCommandRefLayout *)NULL;
		L(m_last)->next = L(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}
	
	if (L(msg)->command->getNetCommandType() < L(m_first)->command->getNetCommandType()) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_first)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			msg = NULL;
			return NULL;
		}

		// The command goes at the head of the list.
		L(msg)->next = L(m_first);
		L(msg)->prev = (NetCommandRefLayout *)NULL;
		L(m_first)->prev = L(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}
	
	
	// Find the start of the command type we're looking for.
	NetCommandRef *tempmsg = m_first;
	while ((tempmsg != NULL) && (L(msg)->command->getNetCommandType() > L(tempmsg)->command->getNetCommandType())) {
		tempmsg = ((NetCommandRef *)L(tempmsg)->next);
	}

	if (tempmsg == NULL) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_last)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			msg = NULL;
			return NULL;
		}

		// message goes at the end of the list.
		L(msg)->prev = L(m_last);
		L(msg)->next = (NetCommandRefLayout *)NULL;
		L(m_last)->next = L(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	// Now find the player position.  munkee.
	while ((tempmsg != NULL) && (L(msg)->command->getNetCommandType() == L(tempmsg)->command->getNetCommandType()) && (L(msg)->command->getPlayerID() > L(tempmsg)->command->getPlayerID())) {
		tempmsg = ((NetCommandRef *)L(tempmsg)->next);
	}

	if (tempmsg == NULL) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_last)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			msg = NULL;
			return NULL;
		}

		// message goes at the end of the list.
		L(msg)->prev = L(m_last);
		L(msg)->next = (NetCommandRefLayout *)NULL;
		L(m_last)->next = L(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	// Find the position within the player's section based on the command ID.
	// If the command type doesn't require a command ID, sort by whatever it should be sorted by.
	while ((tempmsg != NULL) && (L(msg)->command->getNetCommandType() == L(tempmsg)->command->getNetCommandType()) && (L(msg)->command->getPlayerID() == L(tempmsg)->command->getPlayerID()) && (L(msg)->command->getSortNumber() > L(tempmsg)->command->getSortNumber())) {
		tempmsg = ((NetCommandRef *)L(tempmsg)->next);
	}

	if (tempmsg == NULL) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_last)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			msg = NULL;
			return NULL;
		}

		// This message goes at the end of the list.
		L(msg)->prev = L(m_last);
		L(msg)->next = (NetCommandRefLayout *)NULL;
		L(m_last)->next = L(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (tempmsg == m_first) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(m_first)->command, L(msg)->command)) {

			// This command is already in the list, don't duplicate it.
			msg->deleteInstance();
			return NULL;
		}

		// This message goes at the head of the list.
		L(msg)->next = L(m_first);
		L(msg)->prev = (NetCommandRefLayout *)NULL;
		L(m_first)->prev = L(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(L(tempmsg)->command, L(msg)->command)) {

		// This command is already in the list, don't duplicate it.
		msg->deleteInstance();
		msg = NULL;
		return NULL;
	}

	// Insert message before tempmsg.
	L(msg)->next = L(tempmsg);
	L(msg)->prev = L(((NetCommandRef *)L(tempmsg)->prev));
	L(msg)->prev->next = L(msg);
	L(tempmsg)->prev = L(msg);
	m_lastMessageInserted = msg;

	return msg;
}

// ?length@NetCommandList@@QAEHXZ present-unmatched
Int NetCommandList::length() {
	Int retval = 0;
	NetCommandRef *temp = m_first;
	while (temp != NULL) {
		++retval;
		temp = temp->getNext();
	}
	return retval;
}

/**
 * This is really inefficient, but we can probably get away with it because
 * there shouldn't be too many messages for any given frame.
 */
class NetCommandListEqualShim
{
public:
	Bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);
};

NetCommandRef * NetCommandList::findMessage(NetCommandMsg *msg) {
	struct NetCommandRefLayout
	{
		NetCommandMsg *command;
		NetCommandRefLayout *next;
	};

	NetCommandRefLayout *retval = *(NetCommandRefLayout **)((char *)this + 4);
	while (retval != NULL) {
		if (((NetCommandListEqualShim *)this)->isEqualCommandMsg(retval->command, msg) != FALSE)
			return (NetCommandRef *)retval;
		retval = retval->next;
	}
	return NULL;
}

NetCommandRef * NetCommandList::findMessage(UnsignedShort commandID, UnsignedByte playerID) {
	NetCommandRef *retval = m_first;
	while (retval != NULL) {
		if (DoesCommandRequireACommandID((*(NetCommandMsg **)retval)->getNetCommandType())) {
			if (((*(NetCommandMsg **)retval)->getID() == commandID) && ((*(NetCommandMsg **)retval)->getPlayerID() == playerID)) {
				return retval;
			}
		}
		retval = *(NetCommandRef **)((char *)retval + 4);
	}
	return NULL;
}

Bool NetCommandList::isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2) {
	if (DoesCommandRequireACommandID(msg1->getNetCommandType()) != DoesCommandRequireACommandID(msg2->getNetCommandType())) {
		return FALSE;
	}

	// At this point we know that the commands both do or do not require a command id.
	// Do or do not, there is no try.
	if (DoesCommandRequireACommandID(msg1->getNetCommandType())) {
		// Are the commands from the same player?
		if (msg1->getPlayerID() != msg2->getPlayerID()) {
			return FALSE;
		}

		// Do they have the same command ID?
		if (msg1->getID() != msg2->getID()) {
			return FALSE;
		}
		return TRUE;
	}

	// If we've gotten this far, we know that the commands do not require a command id.
	// So now our equality checking becomes type-specific.

	// Are they the same type?
	if (msg1->getNetCommandType() != msg2->getNetCommandType()) {
		return FALSE;
	}

	// Are they from the same player?
	if (msg1->getPlayerID() != msg2->getPlayerID()) {
		return FALSE;
	}

	// They are the same type and from the same player.
	// Time for the type specific stuff.
	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		NetAckStage1CommandMsg *ack1 = (NetAckStage1CommandMsg *)msg1;
		NetAckStage1CommandMsg *ack2 = (NetAckStage1CommandMsg *)msg2;
		
		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return FALSE;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return FALSE;
		}
		return TRUE;
	}

	// They are the same type and from the same player.
	// Time for the type specific stuff.
	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) {
		NetAckStage2CommandMsg *ack1 = (NetAckStage2CommandMsg *)msg1;
		NetAckStage2CommandMsg *ack2 = (NetAckStage2CommandMsg *)msg2;
		
		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return FALSE;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return FALSE;
		}
		return TRUE;
	}

	// They are the same type and from the same player.
	// Time for the type specific stuff.
	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ack1 = (NetAckBothCommandMsg *)msg1;
		NetAckBothCommandMsg *ack2 = (NetAckBothCommandMsg *)msg2;
		
		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return FALSE;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}
