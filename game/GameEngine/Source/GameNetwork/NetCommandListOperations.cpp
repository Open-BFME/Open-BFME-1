// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?reset@NetCommandList@@QAEXXZ: game/GameEngine/Source/GameNetwork/NetCommandList.cpp
// readable body of ?appendList@NetCommandList@@QAEXPAV1@@Z: game/GameEngine/Source/GameNetwork/NetCommandList.cpp

// The pooled reference declarations shift the links and use virtual deletion;
// BFME's unpooled nodes require the ordinary destructor and operator delete.
void __cdecl operator delete(void *block) throw();

class NetCommandMsg;

class NetCommandRef
{
public:
    ~NetCommandRef();
    NetCommandMsg *m_msg;
    NetCommandRef *m_next;
    NetCommandRef *m_prev;
    unsigned char m_relay;
    unsigned int m_timeLastSent; // this+0x10
};

class NetCommandList
{
public:
    void reset();
    void appendList(NetCommandList *sourceList);
    NetCommandRef *addMessage(NetCommandMsg *message);

private:
    void *m_vptr;
    NetCommandRef *m_first;
    NetCommandRef *m_last;
    NetCommandRef *m_lastMessageInserted;
};

void NetCommandList::appendList(NetCommandList *sourceList)
{
    if (sourceList == 0)
        return;

    NetCommandRef *sourceRef = sourceList->m_first;
    while (sourceRef != 0)
    {
        NetCommandRef *nextSourceRef = sourceRef->m_next;
        NetCommandRef *appendedRef = addMessage(sourceRef->m_msg);
        if (appendedRef != 0)
            appendedRef->m_relay = sourceRef->m_relay;
        sourceRef = nextSourceRef;
    }
}

void NetCommandList::reset() {
	NetCommandRef *nextRef = m_first;
	while (m_first != 0) {
		nextRef = m_first->m_next;
		m_first->m_next = 0;
		m_first->m_prev = 0;
		delete m_first;
		m_first = nextRef;
	}
	m_last = 0;
	m_lastMessageInserted = 0;
}
