// ?process006B5A80@Rva006B5A80AudioOwner@@QAEXPAURva006B5A80Record@@I@Z
// partial score=0.25 date=2026-09-17
// ?process006B5A80@Rva006B5A80AudioOwner@@QAEXPAURva006B5A80Record@@I@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x006B5A80 is an anonymous two-argument audio handle-state worker.
// The callers prove the 0x40-byte record and the manager's +0xB00 worker
// pointer, but do not prove a public class or method name.  Keep both names
// address-qualified until a caller or vtable supplies that identity.

typedef unsigned char Bool;

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
	char *m_data;
};

class AudioEventRTS
{
public:
	unsigned char m_pad00[0x48];
	Bool m_flag48;
	unsigned char m_pad49[0x17];
	int m_portionAt60;
	void setNextPlayPortion(int portion);
	BFMERetailAsciiString getFilenameForPlayPortion(void);
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();
	void *m_pointer;
};

class Rva006910F0Handle
{
public:
	~Rva006910F0Handle();
	void *m_pointer;
};

class Rva006911A0Handle
{
public:
	BFMERetailAsciiString construct(void);
	void *m_pointer;
};

struct Rva006B5A80Record
{
	void *m_pad00;
	unsigned char m_pad04[4];
	AudioEventRTS *m_event;
	unsigned char m_pad0c[8];
	unsigned char *m_destination;
	unsigned int m_destinationLength;
	void *m_source;
	Rva006910F0Handle m_handle20;
	Rva006911A0Handle m_handle24;
	unsigned int m_sourceEnd;
	unsigned int m_sourcePosition;
	unsigned int m_destinationPosition;
	unsigned int m_sourceLimit;
	unsigned int m_sourceStart;
	Bool m_complete;
	unsigned char m_pad3d[3];
};

typedef char Rva006B5A80RecordMustBe40[(sizeof(Rva006B5A80Record) == 0x40) ? 1 : -1];

class Rva006B5A80AudioOwner
{
public:
	void process006B5A80(Rva006B5A80Record *record, unsigned int position);

	private:
	unsigned char m_pad00[0xb00];
	void *m_worker;
};

class Rva006B5A80AudioWorker
{
};

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int, int);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int);

extern void j_0000fa1f(void);
extern void j_0001dff2(void);
extern void j_00023911(void);
extern void j_000298e8(void);
extern void j_000311bf(void);
extern void j_0003214b(void);
extern void j_000334b0(void);
extern void j_000351b6(void);
extern void j_0003aa6c(void);
extern void j_0004066f(void);

static Rva006910F0Handle *as_handle(void *storage)
{
	return (Rva006910F0Handle *)storage;
}

static void release_source(void *storage)
{
	typedef void (Rva00690FF0Handle::*Release)(void);
	union
	{
		void (*freeRelease)(void);
		Release memberRelease;
	} call;
	call.freeRelease = ::j_000311bf;
	(((Rva00690FF0Handle *)storage)->*call.memberRelease)();
}

static Rva006910F0Handle make_event_handle(
	Rva006B5A80AudioWorker *worker, AudioEventRTS *event, int portion)
{
	typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Open)(
		AudioEventRTS *, int);
	union
	{
		void (*freeOpen)(void);
		Open memberOpen;
	} call;
	call.freeOpen = ::j_0003aa6c;
	return (worker->*call.memberOpen)(event, portion);
}

static Rva006910F0Handle make_named_handle(
	Rva006B5A80AudioWorker *worker, const BFMERetailAsciiString &name,
		int portion)
{
	typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Open)(
		const BFMERetailAsciiString &, int);
	union
	{
		void (*freeOpen)(void);
		Open memberOpen;
	} call;
	call.freeOpen = ::j_0003214b;
	return (worker->*call.memberOpen)(name, portion);
}

static Rva00690FF0Handle construct_handle(Rva006911A0Handle *handle)
{
	typedef Rva00690FF0Handle (Rva006911A0Handle::*Construct)(void);
	union
	{
		void (*freeConstruct)(void);
		Construct memberConstruct;
	} call;
	call.freeConstruct = ::j_000334b0;
	return (handle->*call.memberConstruct)();
}

static void assign_handle(Rva006910F0Handle *destination,
	const Rva006910F0Handle &source)
{
	typedef Rva006910F0Handle &(Rva006910F0Handle::*Assign)(
		const Rva006910F0Handle &);
	union
	{
		void (*freeAssign)(void);
		Assign memberAssign;
	} call;
	call.freeAssign = ::j_0004066f;
	(destination->*call.memberAssign)(source);
}

static void dispatch_handle(Rva006B5A80AudioOwner *owner,
	Rva006B5A80Record *record, Rva00690FF0Handle *handle, int state)
{
	typedef void (Rva006B5A80AudioOwner::*Dispatch)(
		Rva006B5A80Record *, Rva00690FF0Handle *, int);
	union
	{
		void (*freeDispatch)(void);
		Dispatch memberDispatch;
	} call;
	call.freeDispatch = ::j_0001dff2;
	(owner->*call.memberDispatch)(record, handle, state);
}

static void log_handle_state(Rva006B5A80Record *record, unsigned int state,
	unsigned int position)
{
	if (!_bfme_debugReportingEnabled())
		return;
	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->v60();
	BfmeAwakenLog *log = TheBfmeAwakenDebug->v6c(0, 0);
	BFMERetailAsciiString filename = record->m_event->getFilenameForPlayPortion();
	log = log->v38((const char *)0x0111c4f0);
	log = log->v38(filename.m_data != 0 ? filename.m_data + 8 :
		(const char *)0x0107388b);
	log = log->v38((const char *)0x0111c4dc);
	log = log->v38((const char *)0x01076c28);
	log->v4c((int)(state + position));
	filename.releaseBuffer();
}

void Rva006B5A80AudioOwner::process006B5A80(
	Rva006B5A80Record *record, unsigned int position)
{
	volatile unsigned char localPad[0x28];
	localPad[0] = 0;
	unsigned int pass = 1;
	unsigned int remaining = position - record->m_destinationPosition;
	if (remaining == 0 || pass == 15)
		return;

	AudioEventRTS *event = record->m_event;
	if (record->m_source == 0)
	{
		if (event->m_portionAt60 == 3)
		{
			unsigned int count = remaining;
			unsigned int i;
			for (i = 0; i < count; ++i)
				record->m_destination[record->m_destinationPosition + i] = 0;
			record->m_destinationPosition = position;
			if (position >= record->m_destinationLength)
			{
				record->m_complete = 1;
				record->m_destinationPosition = 0;
			}
		}
		else
		{
			Rva006910F0Handle *current = as_handle(&record->m_handle24);
			if (current->m_pointer == 0 ||
				*(Bool *)((char *)current->m_pointer + 0x41) == 0)
			{
				Rva006910F0Handle opened = make_event_handle(
					(Rva006B5A80AudioWorker *)m_worker, event, 2);
				assign_handle(current, opened);
			}
			if (current->m_pointer != 0)
			{
				event->m_flag48 = 1;
				Rva00690FF0Handle active = construct_handle(
					(Rva006911A0Handle *)current);
				dispatch_handle(this, record, &active, 1);
			}
		}
	}

	if (record->m_handle20.m_pointer != 0 &&
		*(Bool *)((char *)record->m_handle20.m_pointer + 0x42) != 0)
	{
		typedef void (AudioEventRTS::*SetPortion)(int);
		union
		{
			void (*freeSetPortion)(void);
			SetPortion memberSetPortion;
		} setPortion;
		setPortion.freeSetPortion = ::j_00023911;
		(event->*setPortion.memberSetPortion)(3);
	}

	while (record->m_source != 0 &&
		record->m_sourcePosition < record->m_sourceEnd &&
		remaining != 0)
	{
		unsigned int available = record->m_sourceEnd - record->m_sourcePosition;
		unsigned int count = available < remaining ? available : remaining;
		unsigned char *source = (unsigned char *)
			((char *)record->m_source + 0x2c);
		unsigned int i;
		for (i = 0; i < count; ++i)
			record->m_destination[record->m_destinationPosition + i] =
				source[record->m_sourcePosition + i];
		record->m_sourcePosition += count;
		record->m_destinationPosition += count;
		remaining -= count;
		if (record->m_destinationPosition >= record->m_destinationLength)
		{
			record->m_destinationPosition = 0;
			record->m_complete = 1;
		}
		record->m_source = record->m_source;
		release_source(&record->m_source);
		++pass;
		if (pass == 15)
			break;
	}

	log_handle_state(record, pass, position);
}
