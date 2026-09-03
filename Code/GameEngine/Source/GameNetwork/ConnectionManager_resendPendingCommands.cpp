// cl: /DNDEBUG /MD
// BFME's ConnectionManager pending-command resend loop.  The member and node
// layout are fixed by the retail loads at +0x12104, +0x00, +0x04 and +0x0c;
// the same loop is present in the released Zero Hour source.

class NetCommandMsg;

struct PendingCommandRef
{
	NetCommandMsg *message;
	PendingCommandRef *next;
	unsigned int reserved;
	unsigned char relay;
};

struct PendingCommandList
{
	void *reserved;
	PendingCommandRef *first;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	void resendPendingCommands();
	void sendLocalCommand(NetCommandMsg *message, unsigned char relay);

private:
	unsigned char m_unmodelled[0x12104];
	PendingCommandList *m_pendingCommands;
};

void ConnectionManager::resendPendingCommands()
{
	if (m_pendingCommands != 0)
	{
		PendingCommandRef *ref = m_pendingCommands->first;
		while (ref != 0)
		{
			sendLocalCommand(ref->message, ref->relay);
			ref = ref->next;
		}
	}
}
