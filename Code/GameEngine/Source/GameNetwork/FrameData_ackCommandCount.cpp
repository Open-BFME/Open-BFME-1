// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FrameData::getAckCommandCount, 0x006703D0, 47 bytes.
//
// Walks m_commandList and counts entries whose NetCommandMsg satisfies
// CommandRequiresAck. The ILT thunk at 0x0004207D is the only call site inside
// the loop; it lands on the predicate at 0x00682DB0. FrameDataManager's body at
// 0x006708C0 indexes the ring and forwards here.

typedef unsigned int UnsignedInt;
typedef int Int;

class NetCommandMsg;
Int CommandRequiresAck(NetCommandMsg *msg);

class NetCommandRef
{
public:
	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
};

class NetCommandList
{
public:
	void *m_vptr;
	NetCommandRef *m_first;							// this+0x04
};

// upstream layout: reference/shims/framedata/GameNetwork/FrameData.h
class FrameData
{
public:
	UnsignedInt getAckCommandCount();

private:
	UnsignedInt m_frameCommandCount;				// this+0x00
	UnsignedInt m_commandCount;						// this+0x04
	NetCommandList *m_commandList;					// this+0x08
	UnsignedInt m_lastFailedCC;						// this+0x0c
	UnsignedInt m_lastFailedFrameCC;				// this+0x10
};

// ?getAckCommandCount@FrameData@@QAEIXZ
UnsignedInt FrameData::getAckCommandCount()
{
	NetCommandList *list = m_commandList;
	if (list == 0)
		return 0;

	UnsignedInt count = 0;
	NetCommandRef *ref = list->m_first;
	while (ref != 0)
	{
		unsigned char requiresAck = (unsigned char)CommandRequiresAck(ref->m_msg);
		if (requiresAck)
			++count;
		ref = ref->m_next;
	}

	return count;
}
