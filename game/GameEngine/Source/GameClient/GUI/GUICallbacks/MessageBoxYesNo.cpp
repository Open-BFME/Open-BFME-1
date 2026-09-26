// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

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

struct Bfme5RefPairVal
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairVal();
};

class Rva004C5C30 : public Bfme5RefPairVal
{
public:
	Rva004C5C30(Open2Handle first, Open2Handle second);
};

class Rva004C6370
{
public:
	Rva004C6370(Bfme5RefPairVal value);
	Rva004C6370(const Rva004C6370 &other) throw() : m_bfmeNode(other.m_bfmeNode)
	{
		if(m_bfmeNode)
			++((Open2Counted *)m_bfmeNode)->m_refs;
	}
	~Rva004C6370();
	void *m_bfmeNode;
};

extern void j_0002e0b9();
extern void Rva008C5480();

#pragma warning(disable : 4716)

// ?MessageBoxYesNo@@YAPAVGameWindow@@VUnicodeString@@0P6AXXZ1@Z
GameWindow *MessageBoxYesNo(UnicodeString titleString, UnicodeString bodyString,
	GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback);

GameWindow *MessageBoxYesNo(UnicodeString title, UnicodeString body,
	GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback)
{
	if(yesCallback == 0)
		yesCallback = Rva008C5480;
	if(noCallback == 0)
		noCallback = Rva008C5480;
	((void (__cdecl *)(int, const UnicodeString &, const UnicodeString &, Rva004C6370))j_0002e0b9)(
		2, title, body, Rva004C5C30(FunctorSlot(yesCallback), FunctorSlot(noCallback)));
}
