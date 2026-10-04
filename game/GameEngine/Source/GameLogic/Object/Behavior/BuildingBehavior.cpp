// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BuildingBehavior::update uses the secondary UpdateModule receiver.

#include "ascii_string.h"

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &, bool, int, int, int);
	void finish();
};

// Retail calls the drawable's invoke/finish through the incremental-link
// thunks at ILT 0x000391C6 and ILT 0x0001A64F, so the callee is named
// directly and dispatched through a member pointer of the same signature.
extern void j_000391c6();
extern void j_0001a64f();

static __forceinline void sink_invoke(S4Sink004135C0 *sink, const AsciiString &name, bool a, int b, int c, int d)
{
	typedef void (S4Sink004135C0::*Invoke)(const AsciiString &, bool, int, int, int);
	union { void (*fn)(); Invoke call; } u = { j_000391c6 };
	(sink->*u.call)(name, a, b, c, d);
}

static __forceinline void sink_finish(S4Sink004135C0 *sink)
{
	typedef void (S4Sink004135C0::*Finish)();
	union { void (*fn)(); Finish call; } u = { j_0001a64f };
	(sink->*u.call)();
}

class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual S4Sink004135C0 *getDrawable();

	bool testStatus(int) const;
};

extern void j_000016a4();

static __forceinline bool object_test_status(const Object *object, int status)
{
	typedef bool (Object::*TestStatus)(int) const;
	union { void (*fn)(); TestStatus call; } u = { j_000016a4 };
	return (object->*u.call)(status);
}

class Rva001F6960
{
public:
	void apply(S4Sink004135C0 *, int);
};

extern void j_0002e64a();

static __forceinline void rva_apply(Rva001F6960 *self, S4Sink004135C0 *sink, int mode)
{
	typedef void (Rva001F6960::*Apply)(S4Sink004135C0 *, int);
	union { void (*fn)(); Apply call; } u = { j_0002e64a };
	(self->*u.call)(sink, mode);
}

// Retail spells this global `GlobalData *TheWritableGlobalData`; this TU only
// reads the time of day, so it keeps a local view of that field and casts.
class GlobalData;

struct LocalGlobalDataView
{
	char m_padding[0x218];
	int m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;

class BuildingBehaviorModuleData
{
private:
	char m_padding[8];

public:
	AsciiString m_names[4];
};

class BuildingBehavior
{
public:
	virtual UpdateSleepTime update();

private:
	char m_padding[0x0c];
	volatile bool m_started;
	bool m_needsRefresh;
};

UpdateSleepTime BuildingBehavior::update()
{
	register BuildingBehaviorModuleData *const moduleData =
		*(BuildingBehaviorModuleData **)((char *)this - 0x0c);
	Object *object = *(Object **)((char *)this - 8);
	if (object == 0)
		return UPDATE_SLEEP_FOREVER;
	if ((*(unsigned char *)((char *)object + 0x344) & 1) != 0)
		return UPDATE_SLEEP_FOREVER;

	S4Sink004135C0 *sink = object->getDrawable();
	if (sink == 0)
		return UPDATE_SLEEP_FOREVER;
	if ((*(unsigned char *)((char *)object + 0x118) & 0x14) != 0)
		return UPDATE_SLEEP_NONE;

	if (m_needsRefresh)
	{
		AsciiString *name = moduleData->m_names;
		for (int i = 0; i < 4; ++i)
		{
			sink_invoke(sink, *name, false, 1, 0, 0);
			++name;
		}
		LocalGlobalDataView *global = (LocalGlobalDataView *)TheWritableGlobalData;
		if (global->m_timeOfDay == 4)
			sink_invoke(sink, moduleData->m_names[0], true, 1, 0, 0);
		rva_apply((Rva001F6960 *)((char *)this - 0x10), sink, 0);
		m_needsRefresh = false;
		sink_finish(sink);
	}

	if (!m_started)
	{
		if (object_test_status(object, 10))
		{
			m_started = true;
			for (int i = 0; i < 4; ++i)
			{
				if (((LocalGlobalDataView *)TheWritableGlobalData)->m_timeOfDay == 4 && i == 3)
					sink_invoke(sink, moduleData->m_names[i], true, 1, 0, 0);
				else if (i == 1 || i == 2)
					sink_invoke(sink, moduleData->m_names[i], true, 1, 0, 0);
				else
					sink_invoke(sink, moduleData->m_names[i], false, 1, 0, 0);
			}
			rva_apply((Rva001F6960 *)((char *)this - 0x10), sink, 1);
			sink_finish(sink);
			return UPDATE_SLEEP_NONE;
		}
	}

	_ReadWriteBarrier();

	if (m_started)
	{
		if (object_test_status(object, 10))
			return UPDATE_SLEEP_NONE;
		m_started = false;
		AsciiString *name = moduleData->m_names;
		for (int i = 0; i < 4; ++i)
		{
			sink_invoke(sink, *name, false, 1, 0, 0);
			++name;
		}
		LocalGlobalDataView *global = (LocalGlobalDataView *)TheWritableGlobalData;
		if (global->m_timeOfDay == 4)
			sink_invoke(sink, moduleData->m_names[0], true, 1, 0, 0);
		rva_apply((Rva001F6960 *)((char *)this - 0x10), sink, 0);
		sink_finish(sink);
	}
	return UPDATE_SLEEP_NONE;
}
