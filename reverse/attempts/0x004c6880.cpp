// ?MessageBoxOkCancel@@YAPAVGameWindow@@VUnicodeString@@0P6AXXZ1@Z
// partial score=0.79 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "unicode_string.h"

class GameWindow;
typedef void (*GameWinMsgBoxFunc)(void);

struct FunctorSlot
{
	FunctorSlot(void (*callback)()) : m_callback(callback) {}
	void (*m_callback)();
};

class Open2Counted
{
public:
	Open2Counted() : m_refs(0) {}
	virtual ~Open2Counted();
	int m_refs;
};

class Rva010FDFACFunctorSlotWrapper : public Open2Counted
{
public:
	Rva010FDFACFunctorSlotWrapper(const FunctorSlot &slot) : m_callback(slot.m_callback) {}
	virtual ~Rva010FDFACFunctorSlotWrapper();
	virtual void invoke();
	void (*m_callback)();
};

class Open2Handle
{
public:
	Open2Handle(const FunctorSlot &slot) : m_held(new Rva010FDFACFunctorSlotWrapper(slot))
	{
		if(m_held != 0)
			++m_held->m_refs;
	}

	Open2Handle(const Open2Handle &other) : m_held(other.m_held)
	{
		if(m_held != 0)
			++m_held->m_refs;
	}

	~Open2Handle()
	{
		if(m_held != 0 && --m_held->m_refs <= 0)
			delete m_held;
	}

	Open2Counted *m_held;
};

class Bfme5RefCounted
{
public:
	virtual ~Bfme5RefCounted();
	int m_refs;
};

class Bfme5RefPtr
{
public:
	Bfme5RefPtr(const Bfme5RefPtr &other) : m_ptr(other.m_ptr)
	{
		if(m_ptr)
			++m_ptr->m_refs;
	}

	Bfme5RefCounted *m_ptr;
};

struct Bfme5RefPairValE
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairValE();
};

class Rva004C5D20 : public Bfme5RefPairValE
{
public:
	Rva004C5D20(Open2Handle first, Open2Handle second);
};

class Rva004C64E0
{
public:
	Rva004C64E0(Bfme5RefPairValE value);
	void *m_bfmeNode;
};

extern void j_0002e0b9();
extern void Rva008C5480();

#pragma warning(disable : 4716)

// ?MessageBoxOkCancel@@YAPAVGameWindow@@VUnicodeString@@0P6AXXZ1@Z
GameWindow *MessageBoxOkCancel(UnicodeString titleString, UnicodeString bodyString,
	GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback);

GameWindow *MessageBoxOkCancel(UnicodeString title, UnicodeString body,
	GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback)
{
	if(okCallback == 0)
		okCallback = Rva008C5480;
	if(cancelCallback == 0)
		cancelCallback = Rva008C5480;
	((void (__cdecl *)(int, const UnicodeString &, const UnicodeString &, Rva004C64E0))j_0002e0b9)(
		1, title, body, Rva004C64E0(Rva004C5D20(FunctorSlot(okCallback), FunctorSlot(cancelCallback))));
}
