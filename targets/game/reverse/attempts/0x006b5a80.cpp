// ?process006B5A80@Rva006B5A80AudioOwner@@QAEXPAURva006B5A80Record@@I@Z
// partial score=0.1182 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Retail 0x006B5A80 (1480 bytes, ret 8 at +0x5C5): refill one 0x40-byte
// buffered-stream slot up to a byte offset. The matched starter at 0x006B7E70
// (BufferedStreamStarter006B7E70.cpp) calls it through ILT 0x00029910 with the
// slot and its buffer size; its slot view gives +0x08 event, +0x14 buffer,
// +0x18 buffer size, +0x1C file, +0x30 write offset, +0x34 sample rate, +0x38
// bits per sample and +0x3C started. The two diagnostics name the +0x34/+0x38
// checks ("Sample rate mismatch" / "Bit depth mismatch"). The event's +0x60
// field takes setNextPlayPortion's values (2 decay, 3 done), matching Zero
// Hour's AudioEventRTS::m_portionToPlayNext; +0x08 is its event info, whose
// +0x3C m_control bit 0 is AC_LOOP. The owner and method identities are not
// proven, so both keep this body's address.

#include <string.h>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <typename T>
class StringBase;

class AsciiString;

// Retail's shared empty C string (0x0107388B), AsciiString::str()'s null fallback.
extern const char g_bfmeEmptyAscii[];

template <>
class StringBase<char>
{
	friend class AsciiString;

private:
	struct Header
	{
		Int ref_count;
		unsigned short length;
		unsigned short capacity;
	};

	~StringBase()
	{
		releaseBuffer();
	}

	void releaseBuffer();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	~AsciiString() {}

	const char *peek() const
	{
		return (const char *)(m_data + 1);
	}

	const char *str() const
	{
		return m_data ? peek() : g_bfmeEmptyAscii;
	}

	static const AsciiString TheEmptyString;
};

struct WaveInfo006B5A80
{
	Int format;
	void *data;
	UnsignedInt size;
	Int rate;
	Int bits;
	Int channels;
	UnsignedInt extra[3];
};

// Layout as the matched ??1BfmeRecordBQ@@QAE@XZ (OpenAudioFile.cpp) sees it.
class BfmeRecordBQ
{
public:
	AsciiString m_name;
	Int m_owner;
	WaveInfo006B5A80 m_waveInfo;
	char *m_file;
	Int m_accountingValue;
	Int m_openCount;
	Int m_stamp;
	Int m_bucket;
	unsigned char m_compressed;
	unsigned char m_active;
	unsigned char m_reserved;
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();

	BfmeRecordBQ *m_pointer;
};

class Rva006911A0Handle
{
public:
	Rva00690FF0Handle construct();

	Bool hasActiveRecord() const { return m_pointer && m_pointer->m_active; }
	Bool lacksUsableRecord() const { return !m_pointer || m_pointer->m_reserved; }
	Bool lacksSettledRecord() const { return !m_pointer || m_pointer->m_bucket < 2; }
	const AsciiString &recordName() const
	{
		return m_pointer ? m_pointer->m_name : AsciiString::TheEmptyString;
	}

	BfmeRecordBQ *m_pointer;
};

class Rva00691140Handle : public Rva006911A0Handle
{
public:
	Rva00691140Handle &operator=(const Rva00691140Handle &other);
};

class Rva006910F0Handle : public Rva00691140Handle
{
public:
	~Rva006910F0Handle();
};

// The +0x1C file reference (release at 0x00691080).
class Rva00691080
{
public:
	void go();

	const WaveInfo006B5A80 *info() const
	{
		return m_pointer ? &m_pointer->m_waveInfo : 0;
	}

	char *data() const
	{
		return m_pointer ? m_pointer->m_file : 0;
	}

	BfmeRecordBQ *m_pointer;
};

enum PortionToPlay
{
	PP_Attack,
	PP_Sound,
	PP_Decay,
	PP_Done
};

enum
{
	AC_LOOP = 0x1
};

struct AudioEventInfo006B5A80
{
	unsigned char m_bfme00[0x3c];
	Int m_control;
};

class AudioEventRTS
{
public:
	void setNextPlayPortion(PortionToPlay portion);
	PortionToPlay getNextPlayPortion() const { return m_portionToPlayNext; }
	const AudioEventInfo006B5A80 *getAudioEventInfo() const { return m_eventInfo; }
	const AsciiString &getEventName() const { return m_eventName; }

	unsigned char m_bfme00[0x08];
	AudioEventInfo006B5A80 *m_eventInfo;
	unsigned char m_bfme0C[0x14 - 0x0c];
	AsciiString m_eventName;
	unsigned char m_bfme18[0x48 - 0x18];
	Bool m_flag48;
	unsigned char m_bfme49[0x60 - 0x49];
	PortionToPlay m_portionToPlayNext;
};

// Retail 0x000B3BF0, reached through ILT 0x0000FA1F on the same event.
class RvaAudioEventFilenameForPortion
{
public:
	AsciiString getFilenameForPlayPortion();
};

struct Rva006B5A80Record
{
	unsigned char m_pad00[4];
	UnsignedInt m_request;
	AudioEventRTS *m_event;
	unsigned char m_pad0c[8];
	unsigned char *m_destination;
	UnsignedInt m_destinationLength;
	Rva00691080 m_source;
	Rva00691140Handle m_handle20;
	Rva00691140Handle m_handle24;
	Int m_sourceEnd;
	Int m_sourcePosition;
	UnsignedInt m_destinationPosition;
	Int m_sampleRate;
	Int m_bitsPerSample;
	Bool m_complete;
	unsigned char m_pad3d[3];
};

typedef char Rva006B5A80RecordMustBe40[(sizeof(Rva006B5A80Record) == 0x40) ? 1 : -1];

extern void j_0001dff2();
extern void j_0003aa6c();
extern void j_0003214b();

template <class M> inline M member006B5A80(void (*fn)())
{
	union { void (*f)(); M m; } u;
	u.f = fn;
	return u.m;
}

// The +0xB00 worker; both lookups are still dumps (0x00694130, 0x00693B90)
// and are called through their ILT entries.
class Rva006B5A80AudioWorker
{
public:
	Rva006910F0Handle openForEvent(AudioEventRTS **event, Int mode)
	{
		typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Fn)(AudioEventRTS **, Int);
		return (this->*member006B5A80<Fn>(j_0003aa6c))(event, mode);
	}

	Rva006910F0Handle openForName(const AsciiString *name, Int mode)
	{
		typedef Rva006910F0Handle (Rva006B5A80AudioWorker::*Fn)(const AsciiString *, Int);
		return (this->*member006B5A80<Fn>(j_0003214b))(name, mode);
	}
};

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual BfmeAwakenLog *v4c(Int value);
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
	virtual BfmeAwakenLog *v6c(Int first, Int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(Int kind);

#define REPORT(chain) (_bfme_debugReportingEnabled() && \
	(_bfme_debugRecordCallsite(1), TheBfmeAwakenDebug->v60(), \
	 TheBfmeAwakenDebug->v6c(0, 0) chain ->v4c(2), true))

class Rva006B5A80AudioOwner
{
public:
	void process006B5A80(Rva006B5A80Record *slot, UnsignedInt end);

private:
	void attach(Rva006B5A80Record *slot, Rva00690FF0Handle *file, Int mode)
	{
		typedef void (Rva006B5A80AudioOwner::*Fn)(Rva006B5A80Record *, Rva00690FF0Handle *, Int);
		(this->*member006B5A80<Fn>(j_0001dff2))(slot, file, mode);
	}

	unsigned char m_pad00[0xb00];
	Rva006B5A80AudioWorker *m_worker;
};

void Rva006B5A80AudioOwner::process006B5A80(Rva006B5A80Record *slot, UnsignedInt end)
{
	Int passes = 0;
	Int remaining;

	while ((remaining = end - slot->m_destinationPosition) != 0 && ++passes != 15)
	{

		if (slot->m_source.m_pointer == 0)
		{
			if (slot->m_event->getNextPlayPortion() == PP_Done)
			{
				memset(slot->m_destination + slot->m_destinationPosition, 0, remaining);
				slot->m_destinationPosition = end;
				if (end >= slot->m_destinationLength)
				{
					slot->m_complete = true;
					slot->m_destinationPosition = 0;
				}
			}
			else
			{
				if (slot->m_event->getNextPlayPortion() == PP_Decay)
				{
					Rva00691140Handle &decay = slot->m_handle24;
					if (decay.hasActiveRecord())
					{
						slot->m_event->m_flag48 = true;
						Rva00690FF0Handle file = decay.construct();
						attach(slot, &file, 1);
					}
					else if (!decay.m_pointer)
					{
						decay = m_worker->openForEvent(&slot->m_event, 2);
						if (decay.hasActiveRecord())
						{
							slot->m_event->m_flag48 = true;
							Rva00690FF0Handle file = decay.construct();
							attach(slot, &file, 1);
						}
					}
					else if (decay.lacksUsableRecord())
					{
						slot->m_event->setNextPlayPortion(PP_Done);
					}
					else if (decay.lacksSettledRecord())
					{
						decay = m_worker->openForName(&decay.recordName(), 2);
					}
				}
				else if (slot->m_event->getNextPlayPortion() != PP_Done)
				{
					Rva00691140Handle &sound = slot->m_handle20;
					if (sound.lacksUsableRecord())
					{
						sound = m_worker->openForEvent(&slot->m_event, 2);
					}
					else if (!sound.hasActiveRecord() && sound.lacksSettledRecord())
					{
						sound = m_worker->openForName(&sound.recordName(), 2);
					}
				}

				if (slot->m_handle20.hasActiveRecord())
				{
					switch (slot->m_event->getNextPlayPortion())
					{
						case PP_Decay:
							if (slot->m_source.m_pointer)
								break;
							if (!(slot->m_event->getAudioEventInfo()->m_control & AC_LOOP))
								break;
							// fall through
						default:
						{
							Rva00690FF0Handle file = slot->m_handle20.construct();
							attach(slot, &file, 0);
							break;
						}
						case PP_Done:
							break;
					}
				}

				if (slot->m_source.m_pointer)
				{
					const WaveInfo006B5A80 *info = slot->m_source.info();
					if (info->bits != slot->m_bitsPerSample)
					{
						REPORT(->v38("AUDIO: Bit depth mismatch. When two .wav files are played with no delay between them, they must both have the exact same bits/sample. (Error appears in AudioEvent '")
							->v38(slot->m_event->getEventName().str())
							->v38("'. .WAV is '")
							->v38(((RvaAudioEventFilenameForPortion *)slot->m_event)->getFilenameForPlayPortion().str())
							->v38("'"));
						slot->m_sourcePosition = slot->m_sourceEnd;
					}
					if (info->rate != slot->m_sampleRate)
					{
						REPORT(->v38("AUDIO: Sample rate mismatch. When two .wav files are played with no delay between them, they must both have the exact same samples/second. (Error appears in AudioEvent '")
							->v38(slot->m_event->getEventName().str())
							->v38("'. .WAV is '")
							->v38(((RvaAudioEventFilenameForPortion *)slot->m_event)->getFilenameForPlayPortion().str())
							->v38("'"));
						slot->m_sourcePosition = slot->m_sourceEnd;
					}
				}
			}
		}

		if (slot->m_source.m_pointer == 0)
			return;

		Int available = slot->m_sourceEnd - slot->m_sourcePosition;
		const Int &count = _STL::min(remaining, available);
		memcpy(slot->m_destination + slot->m_destinationPosition,
			slot->m_source.data() + slot->m_sourcePosition, count);

		if (remaining < available)
		{
			slot->m_sourcePosition += remaining;
			slot->m_destinationPosition = end;
			if (end >= slot->m_destinationLength)
			{
				slot->m_complete = true;
				slot->m_destinationPosition = 0;
			}
			return;
		}

		slot->m_sourcePosition += available;
		slot->m_destinationPosition += available;
		if (slot->m_destinationPosition >= slot->m_destinationLength)
		{
			slot->m_destinationPosition = 0;
			slot->m_complete = true;
		}
		slot->m_source.go();
	}

	if (passes == 15)
		slot->m_source.go();
}
