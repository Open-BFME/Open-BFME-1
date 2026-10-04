// cl: /DNDEBUG /MD /EHsc
// Watchdog::reportWatchdog at retail 0x0010B8A0: Watchdog vtable slot 3,
// called from Thread_Function when the parent thread's heartbeat is older
// than the timeout. With debug reporting on it logs the parent thread id
// through the opaque singleton pointer cell (same sequence as the INI water-texture
// report), then rethrows to force the crash.

typedef unsigned int UnsignedInt;

class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);
		operator const char *() const { return m_buffer; }

	private:
		char m_buffer[512];
	};
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

// Existing owned pointer cell; the original singleton class type is unproven.
extern void *g_Rva00F36E5C;
bool __cdecl _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

class Watchdog
{
public:
	virtual ~Watchdog();
	virtual void Execute();
	virtual void Thread_Function();
	virtual void reportWatchdog();

private:
	char m_threadClass[0x4c];
	UnsignedInt m_parentThreadId;
};

void Watchdog::reportWatchdog()
{
	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot60();
		BfmeAwakenLog *log = reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot6C(0, 0);
		log->slot38(Debug::Format("Watchdog: Parent thread (ID %d) has stopped responding.\n\n"
			"I'm going to force a crash; please report it.", m_parentThreadId));
		log->slot4C(2);
	}
	throw;
}
