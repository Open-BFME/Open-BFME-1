// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail's global at 0x012F12CC is EA's DisplayStringManager; defined once in
// GameClient/DisplayStringManager.cpp.  The local view below only exists to spell
// the slots this TU calls, so its use casts.
class DisplayStringManager;

// The wide string base this ctor calls is retail's StringBase<unsigned short>
// copy constructor at 0x00888400, so the local view carries the defining name
// (the census had the old spelling as an alias of it). Both members below are
// declared only and are DEFINED out of line by
// game/Libraries/Source/string/StringBase.cpp, whose explicit instantiation
// `template class StringBase<wchar_t>;` (line 779) emits them as COMDATs:
// ??0?$StringBase@G@@AAE@ABV0@@Z (0x00888400, functions.csv row 1626) and
// ??1?$StringBase@G@@AAE@XZ (0x000160F9 -> 0x008881D0, row 6324). Declaring
// them here makes this TU reference both rather than define them. This is the
// same local declared-only template view as
// game/GameEngine/Source/Common/Rva0054D5A0Ctor.cpp: it is needed because
// string_base.h befriends only AsciiString and UnicodeString, and this TU's
// string class is neither. The derived class name is fixed by the ledger row
// for this ctor (functions.csv row 4638).
template <typename T> class StringBase
{
friend class Rva0048EC80UnicodeString;
private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	T *m_data;
};

class Rva0048EC80UnicodeString : private StringBase<unsigned short>
{
public:
	Rva0048EC80UnicodeString(const Rva0048EC80UnicodeString &other) :
		StringBase<unsigned short>(other) {}
	~Rva0048EC80UnicodeString() {}
};

struct Rva0048EC80Descriptor
{
	unsigned int field0;
	unsigned int field4;
};

class Rva0048EC80Resource
{
public:
	virtual void f0();
	virtual void setText(Rva0048EC80UnicodeString text);
	virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
	virtual void setDescriptor(unsigned int value);
	virtual void f7(); virtual void f8(); virtual void f9();
	virtual void finish(int first, int second);
};

class Rva0048EC80Manager
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8();
	virtual Rva0048EC80Resource *create(void);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva0048EC80ResourceOwner
{
public:
	Rva0048EC80ResourceOwner(const Rva0048EC80UnicodeString &text,
		Rva0048EC80Descriptor *descriptor, int identifier);
private:
	Rva0048EC80Descriptor *m_descriptor;
	Rva0048EC80Resource *m_resource;
	unsigned int m_unused;
	int m_identifier;
};

Rva0048EC80ResourceOwner::Rva0048EC80ResourceOwner(
	const Rva0048EC80UnicodeString &text, Rva0048EC80Descriptor *descriptor,
	int identifier)
{
	Rva0048EC80Descriptor *desc = descriptor;
	m_descriptor = desc;
	m_resource = 0;
	m_unused = 0;
	m_identifier = identifier;
	m_resource = ((Rva0048EC80Manager *)TheDisplayStringManager)->create();
	if (m_resource)
	{
		m_resource->setDescriptor(desc->field4);
		m_resource->setText(text);
		m_resource->finish(0, 0);
	}
}
