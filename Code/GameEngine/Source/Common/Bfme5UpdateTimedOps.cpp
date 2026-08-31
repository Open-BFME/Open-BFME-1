// Open-BFME5: the 64-byte timed-operation pump at 0x0007B990.
//
// Retail keeps the list head in a global, calls the head node's update method,
// and, when bit 1 requests removal, advances the global and deletes that node
// through its virtual deleting destructor. An empty list clears bit 2 before
// the returned flags are reduced to bits 0 and 2.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class BfmeErr1042
{
public:
	BfmeErr1042();
	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1042[];
__declspec(noreturn) void __stdcall bfmeFatal1042(BfmeErr1042 *e, char *m);
extern float g_bfmeMillisecondsToSeconds;

class BfmeTimedOperation
{
public:
	virtual ~BfmeTimedOperation(void);
	virtual unsigned int update(float elapsedSeconds, bool firstCall);
};

class BfmeTimedOpNode
{
public:
	virtual ~BfmeTimedOpNode(void);
	unsigned int update(void);                         // retail 0x0007B8E0
	BfmeTimedOpNode *m_next;                           // +0x04
	BfmeTimedOperation *m_operation;                   // +0x08
	bool m_started;                                    // +0x0c
	char m_pad[3];
	unsigned int m_startTime;                          // +0x10
};

extern BfmeTimedOpNode *g_bfmeTimedOpHead;           // retail 0x012ED584

unsigned int BfmeTimedOpNode::update(void)
{
	bool firstCall = false;
	unsigned int now = timeGetTime();

	if (!m_started)
	{
		m_startTime = now;
		firstCall = true;
		m_started = true;
	}

	float elapsedSeconds = now * g_bfmeMillisecondsToSeconds
		- m_startTime * g_bfmeMillisecondsToSeconds;
	BfmeTimedOperation *operation = m_operation;

	if (operation == 0)
	{
		BfmeErr1042 e;
		bfmeFatal1042(&e, g_bfmeMsg1042);
	}

	return operation->update(elapsedSeconds, firstCall);
}

// ?_bfme_updateTimedOps@@YAIXZ
unsigned int _bfme_updateTimedOps(void)
{
	unsigned int flags = 0;

	if (g_bfmeTimedOpHead != 0)
	{
		flags = g_bfmeTimedOpHead->update();

		if (flags & 2)
		{
			BfmeTimedOpNode *head = g_bfmeTimedOpHead;
			g_bfmeTimedOpHead = head->m_next;
			delete head;

			if (g_bfmeTimedOpHead == 0)
				flags &= 4;
		}
	}

	return flags & 5;
}
