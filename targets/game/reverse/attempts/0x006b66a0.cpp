// ?d_006b66a0@@YAXXZ
// partial score=0.5434343434 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc- /D_STLP_USE_STATIC_LIB
//
// Retail 0x006B66A0 is the Miles audio-event dispatch reached by the
// 0x006B9500 request path.  The owner and record identities are retained by
// address because the retail callers prove the layout and ABI, but not a
// source-level name for this split BFME record.

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

extern float g_bfmeElapsedScale;
extern float g_Va0112E8B0;

class Rva006B66A0RefBase
{
public:
	virtual ~Rva006B66A0RefBase();

	long m_refCount;
	void addRef() { InterlockedIncrement(&m_refCount); }
	void releaseRef() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
};

class AudioEventRTS;

class Rva006B66A0AudioHolder
{
public:
	Rva006B66A0AudioHolder &operator=(
		const Rva006B66A0AudioHolder &other)
	{
		if (this != &other)
		{
			if (other.m_pointer != 0)
			{
				Rva006B66A0RefBase *ref =
					(Rva006B66A0RefBase *)((char *)other.m_pointer + 0x70);
				InterlockedIncrement(&ref->m_refCount);
			}

			if (m_pointer != 0)
			{
				Rva006B66A0RefBase *ref =
					(Rva006B66A0RefBase *)((char *)m_pointer + 0x70);
				if (InterlockedDecrement(&ref->m_refCount) <= 0)
					delete ref;
			}

			m_pointer = other.m_pointer;
		}
		return *this;
	}

	AudioEventRTS *m_pointer;
	AudioEventRTS *get() const { return m_pointer; }
};

struct Rva006B66A0AudioInfo
{
	unsigned char m_pad00[0x84];
	int m_soundType;
	int soundType() const { return m_soundType; }
};

class AudioEventRTS
{
public:
	void *m_vftable;
	void *m_filename;
	Rva006B66A0AudioInfo *m_eventInfo;
	unsigned char m_pad0c[0x1c];
	unsigned int m_timeOfDay;
	unsigned char m_pad2c[0x18];
	unsigned char m_flag44;
	unsigned char m_flag45;
	unsigned char m_flag46;
	unsigned char m_flag47;
	unsigned char m_pad48[0x0c];
	float m_delay;
	float delay() const { return m_delay; }
	bool negativeDelay() const { if (m_delay >= g_bfmeElapsedScale) return false; return true; }
	unsigned int timeOfDay() const { return m_timeOfDay; }
};

extern void j_000298e8();

class Rva006B66A0FileHandle
{
public:
    ~Rva006B66A0FileHandle() {
        typedef void (Rva006B66A0FileHandle::*Release)();
        union { void (*raw)(); Release method; } release;
        release.raw=j_000298e8;
        (this->*release.method)();
    }
	void *m_pointer;
};

struct Rva006B66A0Record
{
	void *m_value0;
	Rva006B66A0AudioHolder m_event;
	unsigned int m_state;
	Rva006B66A0FileHandle m_file;
	unsigned char m_flag10;
	unsigned char m_flag11;
	unsigned char m_flag12;
	unsigned char m_flag13;
	unsigned char m_flag14;
	unsigned char m_pad15[3];
	Rva006B66A0AudioHolder &event() { return m_event; }
	void setEvent(const Rva006B66A0AudioHolder &v) { m_event=v; }
};

struct Rva006B66A0Link
{
	Rva006B66A0Link *m_next;
	Rva006B66A0Link *m_prev;
	Rva006B66A0Record *m_value;
};

class Rva006B66A0Worker
{
};

extern void j_00001b77();
extern void j_0001079e();
extern void j_00011fcc();
extern void j_00015a69();
extern void j_00023f79();
extern void j_000298e8();
extern void j_0003aa6c();
extern void j_0004066f();
extern void j_000464ca();
extern void j_00046a33();

class Rva006B66A0AudioOwner
{
public:
	virtual void v00();
	bool rva006B66A0(Rva006B66A0AudioHolder *holder,
		int force, int allowLocal);

private:
	unsigned char m_pad04[0x48];
	Rva006B66A0Link *m_list;
	unsigned char m_pad50[0x63c - 0x50];
	unsigned int m_flags0[3];
	unsigned int m_flags1[3];
	unsigned char m_pad654[0xb00 - 0x654];
	Rva006B66A0Worker *m_worker;
};

bool Rva006B66A0AudioOwner::rva006B66A0(
	Rva006B66A0AudioHolder *holder, int force, int allowLocal)
{
	register Rva006B66A0Link *pos;
	register Rva006B66A0Link *node;
	register Rva006B66A0Link *prev;
	register Rva006B66A0AudioHolder *source = holder;
	register Rva006B66A0Record *record;

	typedef bool (Rva006B66A0AudioOwner::*CanPlay)(AudioEventRTS *);
	union { void (__cdecl *freeFunction)(); CanPlay memberFunction; } canPlay;
	canPlay.freeFunction = ::j_000464ca;

	typedef bool (AudioEventRTS::*HasMore)(void) const;
	union { void (__cdecl *freeFunction)(); HasMore memberFunction; } hasMore;
	hasMore.freeFunction = ::j_00011fcc;

	typedef void (AudioEventRTS::*Generate)(void);
	union { void (__cdecl *freeFunction)(); Generate memberFunction; } generate;
	generate.freeFunction = ::j_00046a33;

	typedef void (AudioEventRTS::*Advance)(void);
	union { void (__cdecl *freeFunction)(); Advance memberFunction; } advance;
	advance.freeFunction = ::j_0001079e;

	typedef void (AudioEventRTS::*Clamp)(float, float);
	union { void (__cdecl *freeFunction)(); Clamp memberFunction; } clamp;
	clamp.freeFunction = ::j_00001b77;

	if (!(this->*canPlay.memberFunction)(source->get()))
	{
		if (source->get()->m_delay < g_bfmeElapsedScale)
		{
			if ((source->get()->*hasMore.memberFunction)())
			{
				(source->get()->*generate.memberFunction)();
				if ((source->get()->*hasMore.memberFunction)())
				{
					(source->get()->*advance.memberFunction)();
					source->get()->m_flag44 = 1;
					(source->get()->*clamp.memberFunction)(34.3333321f,
						g_Va0112E8B0);
				}
			}
		}

		if (!(source->get()->m_delay >= g_bfmeElapsedScale) &&
			!(source->get()->*hasMore.memberFunction)())
			return false;
	}

	typedef Rva006B66A0Record *
		(Rva006B66A0AudioOwner::*Create)(void);
	union { void (__cdecl *freeFunction)(); Create memberFunction; } create;
	create.freeFunction = ::j_00023f79;

	{
		record = (this->*create.memberFunction)();
		record->m_event = *source;
		record->m_value0 = 0;

		if (force == 1)
		{
			record->m_event.m_pointer->m_flag47 = 0;
			record->m_flag14 = 1;
		}

		typedef unsigned int (AudioEventRTS::*GetSoundClass)(void) const;
		union
		{
			void (__cdecl *freeFunction)();
			GetSoundClass memberFunction;
		} getSoundClass;
		getSoundClass.freeFunction = ::j_00015a69;
		unsigned int soundClass =
			(source->get()->*getSoundClass.memberFunction)();
		if (m_flags0[source->get()->timeOfDay()] & soundClass)
			record->m_flag12 = 1;
		if (m_flags1[source->get()->timeOfDay()] & soundClass)
			record->m_flag13 = 1;

		if (source->get()->m_eventInfo->soundType() == 2)
		{
			typedef Rva006B66A0FileHandle
				(Rva006B66A0Worker::*Load)(Rva006B66A0AudioHolder *, int);
			union
			{
				void (__cdecl *freeFunction)();
				Load memberFunction;
			} load;
			load.freeFunction = ::j_0003aa6c;

			typedef void (Rva006B66A0FileHandle::*Assign)(
				const Rva006B66A0FileHandle &);
			union
			{
				void (__cdecl *freeFunction)();
				Assign memberFunction;
			} assign;
			assign.freeFunction = ::j_0004066f;

		int state = source->get()->m_delay >= g_bfmeElapsedScale ? 0 : 1;
			if (source->get()->m_delay < g_bfmeElapsedScale && !allowLocal)
				state = 2;

			(record->m_file.*assign.memberFunction)((m_worker->*load.memberFunction)(source,state));
		}
	}

	pos = m_list;
	node = (Rva006B66A0Link *)
		_STL::__new_alloc::allocate(0x0c);
	Rva006B66A0Record **value = &node->m_value;
	if (value)
		*value = record;
	prev = pos->m_prev;
	node->m_next = pos;
	node->m_prev = prev;
	prev->m_next = node;
	pos->m_prev = node;
	return true;
}
