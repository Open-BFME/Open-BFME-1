// ?process006B5A80@Rva006B5A80AudioOwner@@QAEXPAURva006B5A80Record@@I@Z
// partial score=0.5 date=2026-09-21
// ?process006B5A80@Rva006B5A80AudioOwner@@QAEXPAURva006B5A80Record@@I@Z
// Fresh retry: use the landed BfmeRecordBQ file layout and handle contracts.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;

class BFMERetailAsciiString
{
public:
	char *m_data;
	void releaseBuffer(void);
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
	char *m_eventNameData(void) const;
};

class BfmeRecordBQ
{
public:
	BFMERetailAsciiString m_name;
	int m_owner;
	int m_slots[9];
	char *m_file;
	int m_accountingValue;
	int m_openCount;
	int m_stamp;
	int m_bucket;
	Bool m_compressed;
	Bool m_active;
	Bool m_reserved;
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
	BfmeRecordBQ *m_pointer;
};

struct Rva006B5A80Source
{
	BfmeRecordBQ *m_pointer;
};

struct Rva006B5A80Record
{
	unsigned char m_pad00[4];
	unsigned int m_request;
	AudioEventRTS *m_event;
	unsigned char m_pad0c[8];
	unsigned char *m_destination;
	unsigned int m_destinationLength;
	Rva006B5A80Source m_source;
	Rva006910F0Handle m_handle20;
	Rva006910F0Handle m_handle24;
	unsigned int m_sourceEnd;
	unsigned int m_sourcePosition;
	unsigned int m_destinationPosition;
	unsigned int m_sourceLimit;
	unsigned int m_sourceStart;
	Bool m_complete;
	unsigned char m_pad3d[3];
};

typedef char Rva006B5A80RecordMustBe40[(sizeof(Rva006B5A80Record) == 0x40) ? 1 : -1];

class Rva006B5A80AudioWorker
{
};

class Rva006B5A80AudioOwner
{
public:
	void process006B5A80(Rva006B5A80Record *, unsigned int);

private:
	unsigned char m_pad00[0xb00];
	Rva006B5A80AudioWorker *m_worker;
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
	virtual void v60(); virtual void v64(); virtual void v68();
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

static Rva006910F0Handle open_event(Rva006B5A80AudioWorker *worker,
	AudioEventRTS *event, int portion)
{
	typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Open)(
		AudioEventRTS *, int);
	union { void (*freeOpen)(void); Open memberOpen; } call;
	call.freeOpen = ::j_0003aa6c;
	return (worker->*call.memberOpen)(event, portion);
}

static Rva006910F0Handle open_name(Rva006B5A80AudioWorker *worker,
	const BFMERetailAsciiString &name, int portion)
{
	typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Open)(
		const BFMERetailAsciiString &, int);
	union { void (*freeOpen)(void); Open memberOpen; } call;
	call.freeOpen = ::j_0003214b;
	return (worker->*call.memberOpen)(name, portion);
}

static Rva00690FF0Handle make_active(BfmeRecordBQ *record)
{
	typedef Rva00690FF0Handle (BfmeRecordBQ::*Construct)(void);
	union { void (*freeConstruct)(void); Construct memberConstruct; } call;
	call.freeConstruct = ::j_000334b0;
	return (record->*call.memberConstruct)();
}

static void assign_handle(Rva006910F0Handle *destination,
	const Rva006910F0Handle &source)
{
	typedef Rva006910F0Handle &(Rva006910F0Handle::*Assign)(
		const Rva006910F0Handle &);
	union { void (*freeAssign)(void); Assign memberAssign; } call;
	call.freeAssign = ::j_0004066f;
	(destination->*call.memberAssign)(source);
}

static void dispatch_handle(Rva006B5A80AudioOwner *owner,
	Rva006B5A80Record *record, Rva00690FF0Handle *handle, int state)
{
	typedef void (Rva006B5A80AudioOwner::*Dispatch)(
		Rva006B5A80Record *, Rva00690FF0Handle *, int);
	union { void (*freeDispatch)(void); Dispatch memberDispatch; } call;
	call.freeDispatch = ::j_0001dff2;
	(owner->*call.memberDispatch)(record, handle, state);
}

static void release_source(Rva006B5A80Source *source)
{
	call: {
		typedef void (Rva006B5A80Source::*Release)(void);
		union { void (*freeRelease)(void); Release memberRelease; } call;
		call.freeRelease = ::j_000311bf;
		(source->*call.memberRelease)();
	}
}

static BFMERetailAsciiString empty_name(void)
{
	return *(BFMERetailAsciiString *)0x01336e50;
}

static void log_state(Rva006B5A80Record *record, unsigned int state,
	unsigned int position, const char *message)
{
	if (!_bfme_debugReportingEnabled())
		return;
	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->v60();
	BfmeAwakenLog *log = TheBfmeAwakenDebug->v6c(0, 0);
	log = log->v38(message);
	BFMERetailAsciiString eventName =
		*(BFMERetailAsciiString *)((char *)record->m_event + 0x14);
	log = log->v38(eventName.m_data != 0 ? eventName.m_data + 8 :
		(const char *)0x0107388b);
	BFMERetailAsciiString filename = record->m_event->getFilenameForPlayPortion();
	log = log->v38(filename.m_data != 0 ? filename.m_data + 8 :
		(const char *)0x0107388b);
	log->v4c((int)(state + position));
	filename.releaseBuffer();
	eventName.releaseBuffer();
}

void Rva006B5A80AudioOwner::process006B5A80(
	Rva006B5A80Record *record, unsigned int position)
{
	volatile unsigned char localPad[0x28];
	localPad[0] = 0;
	Rva006B5A80Record *r = record;
	unsigned int pass = 1;
	unsigned int remaining = position - r->m_destinationPosition;
	if (remaining == 0 || pass == 15)
		return;

	AudioEventRTS *event = r->m_event;
	if (r->m_source.m_pointer == 0)
	{
		if (event->m_portionAt60 == 3)
		{
			for (unsigned int i = 0; i < remaining; ++i)
				r->m_destination[r->m_destinationPosition + i] = 0;
			r->m_destinationPosition = position;
			if (position >= r->m_destinationLength)
			{
				r->m_complete = 1;
				r->m_destinationPosition = 0;
			}
		}
		else if (event->m_portionAt60 == 2)
		{
			Rva006910F0Handle *current = &r->m_handle24;
			if (current->m_pointer == 0 || !current->m_pointer->m_active)
			{
				Rva006910F0Handle opened = open_event(m_worker, event, 2);
				assign_handle(current, opened);
			}
			if (current->m_pointer != 0)
			{
				event->m_flag48 = 1;
				Rva00690FF0Handle active = make_active(current->m_pointer);
				dispatch_handle(this, r, &active, 1);
			}
		}
	}

	if (r->m_handle24.m_pointer != 0 && r->m_handle24.m_pointer->m_reserved)
		event->setNextPlayPortion(3);

	if (event->m_portionAt60 != 3)
	{
		Rva006910F0Handle *current = &r->m_handle20;
		if (current->m_pointer != 0 && current->m_pointer->m_reserved)
		{
			Rva006910F0Handle opened = open_event(m_worker, event, 2);
			assign_handle(current, opened);
		}
		else if (current->m_pointer == 0 || !current->m_pointer->m_active)
		{
			if (current->m_pointer == 0 || current->m_pointer->m_bucket < 2)
			{
				const BFMERetailAsciiString &name = current->m_pointer
					? *(BFMERetailAsciiString *)current->m_pointer
					: *(BFMERetailAsciiString *)0x01336e50;
				Rva006910F0Handle opened = open_name(m_worker, name, 2);
				assign_handle(current, opened);
			}
		}
		if (current->m_pointer != 0 && current->m_pointer->m_active)
		{
			int state = event->m_portionAt60 - 2;
			if (state != 0)
				--state;
			if (r->m_source.m_pointer == 0 && event->m_portionAt60 != 0)
			{
				Rva00690FF0Handle active = make_active(current->m_pointer);
				dispatch_handle(this, r, &active, 6);
			}
		}
	}

	if (r->m_source.m_pointer == 0)
		return;

	if (r->m_source.m_pointer->m_slots[6] != r->m_sourceStart)
		log_state(r, pass, position, (const char *)0x0111c4f0);
	r->m_sourcePosition = r->m_sourceEnd;
	if (r->m_source.m_pointer->m_slots[5] != r->m_sourceLimit)
		log_state(r, pass, position, (const char *)0x0111c410);

	while (r->m_source.m_pointer != 0 &&
		r->m_sourcePosition < r->m_sourceEnd && remaining != 0)
	{
		unsigned int available = r->m_sourceEnd - r->m_sourcePosition;
		unsigned int count = available < remaining ? available : remaining;
		unsigned char *source = (unsigned char *)
			(r->m_source.m_pointer->m_file);
		for (unsigned int i = 0; i < count; ++i)
			r->m_destination[r->m_destinationPosition + i] =
				source[r->m_sourcePosition + i];
		r->m_sourcePosition += count;
		r->m_destinationPosition += count;
		remaining -= count;
		if (r->m_destinationPosition >= r->m_destinationLength)
		{
			r->m_destinationPosition = 0;
			r->m_complete = 1;
		}
		if (remaining >= available)
		{
			release_source(&r->m_source);
			++pass;
			if (pass == 15)
				break;
		}
	}
}
