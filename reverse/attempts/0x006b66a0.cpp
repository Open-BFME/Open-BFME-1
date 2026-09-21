// ?d_006b66a0@@YAXXZ
// partial score=0.24 date=2026-09-18
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
};

struct Rva006B66A0AudioInfo
{
	unsigned char m_pad00[0x84];
	int m_soundType;
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
};

class Rva006B66A0FileHandle
{
public:
	void *m_pointer;
};

struct Rva006B66A0Record;

extern void j_000298e8();

class Rva006B66A0RecordRef
{
public:
	Rva006B66A0RecordRef(Rva006B66A0Record *pointer) : m_pointer(pointer) {}
	~Rva006B66A0RecordRef()
	{
		typedef void (Rva006B66A0RecordRef::*Release)(void);
		union
		{
			void (__cdecl *freeFunction)();
			Release memberFunction;
		} release;
		release.freeFunction = ::j_000298e8;
		(this->*release.memberFunction)();
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

	if (!(this->*canPlay.memberFunction)(source->m_pointer))
	{
		if (source->m_pointer->m_delay < g_bfmeElapsedScale)
		{
			if ((source->m_pointer->*hasMore.memberFunction)())
			{
				(source->m_pointer->*generate.memberFunction)();
				if ((source->m_pointer->*hasMore.memberFunction)())
				{
					(source->m_pointer->*advance.memberFunction)();
					source->m_pointer->m_flag44 = 1;
					(source->m_pointer->*clamp.memberFunction)(34.3333321f,
						g_Va0112E8B0);
				}
			}
		}

		if (source->m_pointer->m_delay < g_bfmeElapsedScale &&
			!(source->m_pointer->*hasMore.memberFunction)())
			return false;
	}

	typedef Rva006B66A0Record *
		(Rva006B66A0AudioOwner::*Create)(void);
	union { void (__cdecl *freeFunction)(); Create memberFunction; } create;
	create.freeFunction = ::j_00023f79;

	{
		record = (this->*create.memberFunction)();
		Rva006B66A0RecordRef recordRef(record);
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
			(source->m_pointer->*getSoundClass.memberFunction)();
		if (m_flags0[source->m_pointer->m_timeOfDay] & soundClass)
			record->m_flag12 = 1;
		if (m_flags1[source->m_pointer->m_timeOfDay] & soundClass)
			record->m_flag13 = 1;

		if (source->m_pointer->m_eventInfo->m_soundType == 2)
		{
			typedef Rva006B66A0FileHandle *
				(Rva006B66A0Worker::*Load)(Rva006B66A0RecordRef *,
				Rva006B66A0AudioHolder *, int);
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

		int state = source->m_pointer->m_delay <
			g_bfmeElapsedScale ? 1 : 0;
			if (source->m_pointer->m_delay < g_bfmeElapsedScale && !allowLocal)
				state = 2;

			Rva006B66A0FileHandle *opened =
				(m_worker->*load.memberFunction)(&recordRef, source, state);
			(record->m_file.*assign.memberFunction)(*opened);
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
