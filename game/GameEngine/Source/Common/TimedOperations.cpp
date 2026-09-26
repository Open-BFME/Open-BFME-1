// Open-BFME5: the 64-byte timed-operation pump at 0x0007B990.
//
// Retail keeps the list head in a global, calls the head node's update method,
// and, when bit 1 requests removal, advances the global and deletes that node
// through its virtual deleting destructor. An empty list clears bit 2 before
// the returned flags are reduced to bits 0 and 2.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class FatalErrorContext
{
public:
	FatalErrorContext();
	char m_fields[0xc];
};

extern char g_missingTimedOperationMessage[];
__declspec(noreturn) void __stdcall reportFatalError(FatalErrorContext *context, char *message);
extern float g_millisecondsToSeconds;

class TimedOperation
{
public:
	virtual ~TimedOperation(void);
	virtual unsigned int update(float elapsedSeconds, bool firstCall);
};

class TimedOperationNode
{
public:
	virtual ~TimedOperationNode(void);
	unsigned int update(void);                         // retail 0x0007B8E0
	TimedOperationNode *m_next;                        // +0x04
	TimedOperation *m_operation;                       // +0x08
	bool m_started;                                    // +0x0c
	char m_pad[3];
	unsigned int m_startTime;                          // +0x10
};

extern TimedOperationNode *g_timedOperationHead;     // retail 0x012ED584

unsigned int TimedOperationNode::update(void)
{
	bool firstCall = false;
	unsigned int now = timeGetTime();

	if (!m_started)
	{
		m_startTime = now;
		firstCall = true;
		m_started = true;
	}

	float elapsedSeconds = now * g_millisecondsToSeconds
		- m_startTime * g_millisecondsToSeconds;
	TimedOperation *operation = m_operation;

	if (operation == 0)
	{
		FatalErrorContext context;
		reportFatalError(&context, g_missingTimedOperationMessage);
	}

	return operation->update(elapsedSeconds, firstCall);
}

// ?updateTimedOperations@@YAIXZ
unsigned int updateTimedOperations(void)
{
	unsigned int flags = 0;

	if (g_timedOperationHead != 0)
	{
		flags = g_timedOperationHead->update();

		if (flags & 2)
		{
			TimedOperationNode *head = g_timedOperationHead;
			g_timedOperationHead = head->m_next;
			delete head;

			if (g_timedOperationHead == 0)
				flags &= 4;
		}
	}

	return flags & 5;
}
