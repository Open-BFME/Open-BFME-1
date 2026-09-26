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

#pragma comment(linker, "/alternatename:?invoke@S4Sink004135C0@@QAEXABVAsciiString@@_NHHH@Z=?j_000391c6@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@S4Sink004135C0@@QAEXXZ=?j_0001a64f@@YAXXZ")

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

#pragma comment(linker, "/alternatename:?testStatus@Object@@QBE_NH@Z=?j_000016a4@@YAXXZ")

class Rva001F6960
{
public:
	void apply(S4Sink004135C0 *, int);
};

#pragma comment(linker, "/alternatename:?apply@Rva001F6960@@QAEXPAVS4Sink004135C0@@H@Z=?j_0002e64a@@YAXXZ")

struct GlobalData
{
	char m_padding[0x218];
	int m_timeOfDay;
};

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
			sink->invoke(*name, false, 1, 0, 0);
			++name;
		}
		GlobalData *global = *(GlobalData **)0x012ed5c8;
		if (global->m_timeOfDay == 4)
			sink->invoke(moduleData->m_names[0], true, 1, 0, 0);
		((Rva001F6960 *)((char *)this - 0x10))->apply(sink, 0);
		m_needsRefresh = false;
		sink->finish();
	}

	if (!m_started)
	{
		if (object->testStatus(10))
		{
			m_started = true;
			for (int i = 0; i < 4; ++i)
			{
				if ((*(GlobalData **)0x012ed5c8)->m_timeOfDay == 4 && i == 3)
					sink->invoke(moduleData->m_names[i], true, 1, 0, 0);
				else if (i == 1 || i == 2)
					sink->invoke(moduleData->m_names[i], true, 1, 0, 0);
				else
					sink->invoke(moduleData->m_names[i], false, 1, 0, 0);
			}
			((Rva001F6960 *)((char *)this - 0x10))->apply(sink, 1);
			sink->finish();
			return UPDATE_SLEEP_NONE;
		}
	}

	_ReadWriteBarrier();

	if (m_started)
	{
		if (object->testStatus(10))
			return UPDATE_SLEEP_NONE;
		m_started = false;
		AsciiString *name = moduleData->m_names;
		for (int i = 0; i < 4; ++i)
		{
			sink->invoke(*name, false, 1, 0, 0);
			++name;
		}
		GlobalData *global = *(GlobalData **)0x012ed5c8;
		if (global->m_timeOfDay == 4)
			sink->invoke(moduleData->m_names[0], true, 1, 0, 0);
		((Rva001F6960 *)((char *)this - 0x10))->apply(sink, 0);
		sink->finish();
	}
	return UPDATE_SLEEP_NONE;
}
