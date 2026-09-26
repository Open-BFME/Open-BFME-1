// cl: /DNDEBUG /MD /EHsc
// NetCommandList::addMessage, retail RVA 0x00673200, 609 bytes.
// BFME's NetCommandRef is nonpooled; NetCommandMsg's sort virtual is slot +4.
// TU-local ABI declarations preserve the existing reference-header users.
// Identity: matched NetCommandList::appendList (0x00673580) and
// FrameData::addCommand (0x006702F0) both call this body through ILT 0x000051E6.
// Based on GeneralsMD/Code/GameEngine/Source/GameNetwork/NetCommandList.cpp,
// Copyright 2025 Electronic Arts Inc.; SPDX-License-Identifier: GPL-3.0-or-later.

#define NULL 0
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *) throw();

class NetCommandMsg
{
public:
    virtual ~NetCommandMsg();
    virtual int getSortNumber();
    unsigned int getPlayerID() { return m_playerID; }
    unsigned short getID() { return m_id; }
    int getNetCommandType() { return m_commandType; }
private:
    unsigned int m_timestamp;
    unsigned int m_executionFrame;
    unsigned int m_playerID;
    unsigned short m_id;
    int m_commandType;
    int m_referenceCount;
};

class NetCommandRef
{
public:
    NetCommandRef(NetCommandMsg *msg);
    ~NetCommandRef();
    NetCommandMsg *getCommand() { return m_msg; }
    NetCommandRef *getNext() { return m_next; }
    NetCommandRef *getPrev() { return m_prev; }
    void setNext(NetCommandRef *next) { m_next = next; }
    void setPrev(NetCommandRef *prev) { m_prev = prev; }
private:
    NetCommandMsg *m_msg;
    NetCommandRef *m_next;
    NetCommandRef *m_prev;
    unsigned char m_relay;
    unsigned int m_timeLastSent;
};

class NetCommandList
{
public:
    NetCommandRef *addMessage(NetCommandMsg *msg);
    bool isEqualCommandMsg(NetCommandMsg *first, NetCommandMsg *second);
private:
    void *m_vptr;
    NetCommandRef *m_first;
    NetCommandRef *m_last;
    NetCommandRef *m_lastMessageInserted;
};

NetCommandRef * NetCommandList::addMessage(NetCommandMsg *cmdMsg) {
	if (cmdMsg == NULL) {
		return NULL;
	}

	NetCommandRef *msg = new NetCommandRef(cmdMsg);

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
		NetCommandRef *theNext = m_lastMessageInserted->getNext();
		if ((m_lastMessageInserted->getCommand()->getNetCommandType() == msg->getCommand()->getNetCommandType()) &&
			(m_lastMessageInserted->getCommand()->getPlayerID() == msg->getCommand()->getPlayerID()) &&
			(m_lastMessageInserted->getCommand()->getID() < msg->getCommand()->getID()) &&
			((theNext == NULL) || ((theNext->getCommand()->getNetCommandType() > msg->getCommand()->getNetCommandType()) ||
			 (theNext->getCommand()->getPlayerID() > msg->getCommand()->getPlayerID()) ||
			 (theNext->getCommand()->getID() > msg->getCommand()->getID())))) {

			// Make sure this command isn't already in the list.
			if (isEqualCommandMsg(m_lastMessageInserted->getCommand(), msg->getCommand())) {

				// This command is already in the list, don't duplicate it.
				delete msg;
				msg = NULL;
				return NULL;
			}

			if (theNext == NULL) {
				// this means that m_lastMessageInserted == m_last, so m_last should point to the msg that is being inserted.
				msg->setNext(m_lastMessageInserted->getNext());
				msg->setPrev(m_lastMessageInserted);
				m_lastMessageInserted->setNext(msg);
				m_lastMessageInserted = msg;
				m_last = msg;
			} else {
				msg->setNext(m_lastMessageInserted->getNext());
				msg->setPrev(m_lastMessageInserted);
				m_lastMessageInserted->setNext(msg);
				msg->getNext()->setPrev(msg);
				m_lastMessageInserted = msg;
			}
			return msg;
		}
	}

	if (msg->getCommand()->getNetCommandType() > m_last->getCommand()->getNetCommandType()) {
		// easy optimization for a command that goes at the end of the list
		// since they are likely to be added in order.

		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(m_last->getCommand(), msg->getCommand())) {

			// This command is already in the list, don't duplicate it.
			delete msg;
			msg = NULL;
			return NULL;
		}

		msg->setPrev(m_last);
		msg->setNext(NULL);
		m_last->setNext(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (msg->getCommand()->getNetCommandType() < m_first->getCommand()->getNetCommandType()) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(m_first->getCommand(), msg->getCommand())) {

			// This command is already in the list, don't duplicate it.
			delete msg;
			msg = NULL;
			return NULL;
		}

		// The command goes at the head of the list.
		msg->setNext(m_first);
		msg->setPrev(NULL);
		m_first->setPrev(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}


	// BFME combines the three comparisons with OR in one traversal. Retain
	// this retail behavior instead of ZH's separate lexicographic passes.
	// Widening the signed sort operands preserves comparison semantics and
	// shapes MSVC 7.1 to call the incoming command's virtual first, as retail
	// does. The generated comparison remains a signed 32-bit cmp/jle.
	NetCommandRef *tempmsg = m_first;
	while ((tempmsg != NULL) &&
		((msg->getCommand()->getNetCommandType() > tempmsg->getCommand()->getNetCommandType()) ||
		 (msg->getCommand()->getPlayerID() > tempmsg->getCommand()->getPlayerID()) ||
		 ((__int64)msg->getCommand()->getSortNumber() > (__int64)tempmsg->getCommand()->getSortNumber()))) {
		tempmsg = tempmsg->getNext();
	}

	if (tempmsg == NULL) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(m_last->getCommand(), msg->getCommand())) {

			// This command is already in the list, don't duplicate it.
			delete msg;
			msg = NULL;
			return NULL;
		}

		// This message goes at the end of the list.
		msg->setPrev(m_last);
		msg->setNext(NULL);
		m_last->setNext(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (tempmsg == m_first) {
		// Make sure this command isn't already in the list.
		if (isEqualCommandMsg(m_first->getCommand(), msg->getCommand())) {

			// This command is already in the list, don't duplicate it.
			delete msg;
			return NULL;
		}

		// This message goes at the head of the list.
		msg->setNext(m_first);
		msg->setPrev(NULL);
		m_first->setPrev(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	// Make sure this command isn't already in the list.
	if (isEqualCommandMsg(tempmsg->getCommand(), msg->getCommand())) {

		// This command is already in the list, don't duplicate it.
		delete msg;
		msg = NULL;
		return NULL;
	}

	// Insert message before tempmsg.
	msg->setNext(tempmsg);
	msg->setPrev(tempmsg->getPrev());
	msg->getPrev()->setNext(msg);
	tempmsg->setPrev(msg);
	m_lastMessageInserted = msg;

	return msg;
}
