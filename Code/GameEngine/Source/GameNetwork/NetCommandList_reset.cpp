// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?reset@NetCommandList@@QAEXXZ: Code/GameEngine/Source/GameNetwork/NetCommandList.cpp

// NetCommandList::reset, 0x006731A0, 74 bytes.
//
// Split out of NetCommandList.cpp because it needs BFME's de-pooled
// NetCommandRef: m_next and m_prev sit at +0x04 and +0x08, four bytes below
// where the reference's MemoryPoolObject base puts them, and the reference's
// deleteInstance() is a virtual call where retail emits a plain destructor plus
// operator delete. That file models the class through the real header, so both
// come out wrong there and right here.
//
// The body is the reference's otherwise, including re-reading m_first for each
// of the two link clears rather than caching it.

typedef int Int;

void __cdecl operator delete(void *block) throw();

class NetCommandMsg;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandList.h
class NetCommandList
{
public:
	void reset();

	void *m_vptr;
	NetCommandRef *m_first;							// this+0x04
	NetCommandRef *m_last;							// this+0x08
	NetCommandRef *m_lastMessageInserted;			// this+0x0C
};

void NetCommandList::reset() {
	NetCommandRef *temp = m_first;
	while (m_first != 0) {
		temp = m_first->m_next;
		m_first->m_next = 0;
		m_first->m_prev = 0;
		delete m_first;
		m_first = temp;
	}
	m_last = 0;
	m_lastMessageInserted = 0;
}
