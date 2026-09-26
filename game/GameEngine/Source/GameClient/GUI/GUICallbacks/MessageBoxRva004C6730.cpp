// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x004C6730 (259 bytes), reached through MessageBoxOk ILT 0x0004A340.
// Keep the body address-derived: the existing thunk owns the public symbol.
// Callback wrapper vtable 0x010FDFAC and default callback 0x008C5480 are shared
// with the verified YesNo/OkCancel builders. The single holder constructor at
// 0x004C6430 consumes its reference by value; 0x00522D20 consumes the outer
// holder with button mode zero. Native temporary lifetimes own both releases.
#include "unicode_string.h"

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
		if(m_held != 0 && (m_held->m_refs = m_held->m_refs - 1) <= 0)
			delete m_held;
	}

	Open2Counted *m_held;
};

class Bfme5RefPtr
{
public:
	Bfme5RefPtr(Open2Handle other) : m_ptr(other.m_held)
	{
		if(m_ptr)
			++m_ptr->m_refs;
	}

	Bfme5RefPtr(const Bfme5RefPtr &other) : m_ptr(other.m_ptr)
	{
		if(m_ptr)
			++m_ptr->m_refs;
	}

	~Bfme5RefPtr()
	{
		if(m_ptr && (m_ptr->m_refs = m_ptr->m_refs - 1) <= 0)
			delete m_ptr;
	}

	Open2Counted *m_ptr;
};

class Rva004C6430
{
public:
	Rva004C6430(Bfme5RefPtr value);
	~Rva004C6430();
	void *m_node;
};

extern void j_0002e0b9();
extern void Rva008C5480();

void Rva004C6730(UnicodeString title, UnicodeString body, GameWinMsgBoxFunc callback)
{
	if(!callback)
		callback = Rva008C5480;
	((void (__cdecl *)(int, const UnicodeString &, const UnicodeString &, Rva004C6430))j_0002e0b9)(
		0, title, body, Bfme5RefPtr(Open2Handle(FunctorSlot(callback))));
}
