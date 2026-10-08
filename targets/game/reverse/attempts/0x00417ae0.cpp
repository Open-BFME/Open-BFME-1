// ?run@Rva00417AE0@@QAEXH@Z
// partial score=0.5546 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class BfmeHostQR { public: void Rva00417430AudioSelector(void *, int); };

class Rva00087750Ref
{
public:
	Rva00087750Ref(BfmeHostQR *owner, int selector) { owner->Rva00417430AudioSelector(this, selector); }
	Rva00087750Ref() : m_ptr(0) { }
	Rva00087750Ref(Rva00087750Counted *ptr) : m_ptr(ptr) { if (ptr) InterlockedIncrement(&ptr->m_refCount); }
	Rva00087750Ref(const Rva00087750Ref &rhs) : m_ptr(rhs.m_ptr)
	{
		if (m_ptr) InterlockedIncrement(&m_ptr->m_refCount);
	}

	__declspec(noinline) Rva00087750Ref &operator=(const Rva00087750Ref &rhs);

	~Rva00087750Ref()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva00087750Counted *m_ptr;
};

#include "ascii_string.h"
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
class Rva00417AE0Event
{
public:
    void *m_vtable;
    AsciiString m_filename;
    Rva00087750Ref m_info;
    int m_handle;
    int m_killHandle;
    AsciiString m_name;
};
extern Rva00417AE0Event BfmeTheEmptyAudioEvent;
class Rva00417AE0AudioClient
{
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7c();
    virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c();
    virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9c();
    virtual void sa0(); virtual void sa4(); virtual void sa8();
    virtual void resolve(const Rva00417AE0Event *event);
};
extern Rva00417AE0AudioClient *TheAudioClientUpdate;

class RefCountedThing {
public:
 virtual ~RefCountedThing();
 void Add_Ref() { InterlockedIncrement(&m_refCount); }
 void Release_Ref() { if (InterlockedDecrement(&m_refCount) <= 0) delete this; }
 long m_refCount;
};
class Rva000B5FD0Ref {
public:
 Rva000B5FD0Ref() : m_ptr(0) {}
 Rva000B5FD0Ref(const Rva000B5FD0Ref &other) : m_ptr(other.m_ptr) {
  if (m_ptr) m_ptr->Add_Ref();
 }
 ~Rva000B5FD0Ref() { if (m_ptr) m_ptr->Release_Ref(); }
 void assign(RefCountedThing *p);
 Rva000B5FD0Ref &operator=(const Rva000B5FD0Ref &other) {
  if (this != &other) {
   if (other.m_ptr) other.m_ptr->Add_Ref();
   if (m_ptr) m_ptr->Release_Ref();
   m_ptr = other.m_ptr;
  }
  return *this;
 }
 void clear() { if (m_ptr) { m_ptr->Release_Ref(); m_ptr = 0; } }
 RefCountedThing *m_ptr;
};
class Rva000B5450Thing : public RefCountedThing {
public:
 explicit Rva000B5450Thing(void *value);
 char m_rest[0xA4 - 8];
};
static __declspec(noinline) Rva000B5FD0Ref Rva00415C20()
{
 static Rva000B5FD0Ref singleton;
 if (!singleton.m_ptr) singleton.assign(new Rva000B5450Thing(0));
 return singleton;
}

class Rva00417430
{
public:
	// Returned holders use one hidden result pointer followed by the selector.
	__declspec(noinline) Rva00087750Ref call(int selector);
	__declspec(noinline) Rva00087750Ref select(int selector);
	const Rva00417AE0Event *lookup(int ordinal);
	const Rva00417AE0Event *getEvent(int ordinal)
	{
		const Rva00417AE0Event *value = lookup(ordinal);
		return value ? value : &BfmeTheEmptyAudioEvent;
	}
	void emit(int selector, bool onlyIfPermanent);

private:
	unsigned char m_head[0x10c];
	Rva00087750Counted *m_custom;
	unsigned char m_rest[0x30];
};

class Rva00417AudioSlot
{
public:
	unsigned char m_head[0x0c];
	Rva00087750Ref m_info;
	unsigned int m_handle;
};

// The base is a zero-offset ABI view; source inheritance is unproven.
class Rva00417AE0 : public Rva00417430
{
public:
	void run(int arg);

private:
	bool m_flagA;				// +0x140
	bool m_flagB;				// +0x141
	unsigned char m_unused142;			// +0x142
	bool m_flagC;				// +0x143
	Rva00417AudioSlot *m_first;		// +0x144
	Rva00417AudioSlot *m_second;		// +0x148
};

// ?run@Rva00417AE0@@QAEXH@Z present-unmatched
void Rva00417AE0::run(int arg)
{
	if (m_flagA && m_flagB && m_flagC)
	{
		bool changed = false;
		Rva00087750Ref first = call(arg);

		Rva00087750Ref firstSlot;
		if (m_first)
			firstSlot = m_first->m_info;

		if (first.m_ptr != firstSlot.m_ptr)
			changed = true;

		Rva00087750Ref second = select((int)arg);
		Rva00087750Ref secondSlot;
		if (m_second)
			secondSlot = m_second->m_info;

		if (second.m_ptr != secondSlot.m_ptr || changed)
			emit(arg, false);
	}
}


// ??4Rva00087750Ref@@QAEAAV0@ABV0@@Z
Rva00087750Ref &Rva00087750Ref::operator=(const Rva00087750Ref &rhs)
{
    if (this != &rhs)
    {
        if (rhs.m_ptr)
            InterlockedIncrement(&rhs.m_ptr->m_refCount);
        if (m_ptr)
            m_ptr->Release_Ref();
        m_ptr = rhs.m_ptr;
    }
    return *this;
}

// ?select@Rva00417430@@QAE?AVRva00087750Ref@@H@Z present-unmatched
Rva00087750Ref Rva00417430::select(int selector)
{
    const Rva00417AE0Event *event;
    switch (selector)
    {
    case 1: event = getEvent(0x5c); break;
    case 2: event = getEvent(0x5d); break;
    case 3: event = getEvent(0x5e); break;
    default: event = getEvent(0x5b); break;
    }
    if (!event->m_name.isEmpty())
    {
        if (!event->m_info.m_ptr) TheAudioClientUpdate->resolve(event);
        return event->m_info;
    }
    if (selector != 0 && selector != 3)
    {
        const Rva00417AE0Event *fallback = lookup(0x5b);
        event = fallback ? fallback : &BfmeTheEmptyAudioEvent;
        if (event->m_name.isNotEmpty())
        {
            if (!event->m_info.m_ptr) TheAudioClientUpdate->resolve(event);
            return event->m_info;
        }
    }
    return Rva00087750Ref();
}

// ?call@Rva00417430@@QAE?AVRva00087750Ref@@H@Z present-unmatched
Rva00087750Ref Rva00417430::call(int selector)
{
    if (selector != 3 && m_custom)
    {
        bool different = (void *)m_custom != (void *)Rva00415C20().m_ptr;
        if (different) return Rva00087750Ref(m_custom);
        return Rva00087750Ref();
    }
    const Rva00417AE0Event *event;
    switch (selector)
    {
    case 1: event = getEvent(0x58); break;
    case 2: event = getEvent(0x59); break;
    case 3: event = getEvent(0x5a); break;
    default: event = getEvent(0x57); break;
    }
    if (!event->m_name.isEmpty())
    {
        if (!event->m_info.m_ptr) TheAudioClientUpdate->resolve(event);
        return event->m_info;
    }
    if (selector != 0 && selector != 3)
    {
        const Rva00417AE0Event *fallback = lookup(0x57);
        event = fallback ? fallback : &BfmeTheEmptyAudioEvent;
        if (event->m_name.isNotEmpty())
        {
            if (!event->m_info.m_ptr) TheAudioClientUpdate->resolve(event);
            return event->m_info;
        }
    }
    return Rva00087750Ref();
}
