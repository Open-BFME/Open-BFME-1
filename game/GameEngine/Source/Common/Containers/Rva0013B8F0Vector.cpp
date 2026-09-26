// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Seven STLport operations over an observed 20-byte element. The original
// class is unknown: other unrelated 20-byte records had incorrectly shared
// the ModuleInfo::Nugget name. The address preserves this family's identity.
// The first three words are opaque; string +0x0C and retained pointer +0x10
// are witnessed by assignment 0x0075EEF0 and destructor 0x0013B8F0.
// Construction 0x00768B60 copies the string through StringBase<char> and
// retains the source pointer. Destruction uses its observed +0x24 subobject.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>

#include "ascii_string.h"
#include <vector>

class Rva0013B8F0RefCountView
{
public:
	virtual void deleteThroughSlot0(int freeIt);		// vtable slot 0

	void addRef(void) { ++m_referenceCount; }
	void releaseRef(void)
	{
		--m_referenceCount;
		if (m_referenceCount <= 0)
			deleteThroughSlot0(1);
	}

	int m_referenceCount;
};

// Partial codegen view: retail adjusts the receiver by +0x24 to reach the
// observed reference-count subobject. Original class composition is unknown.
class Rva0013B8F0TargetView
{
public:
	char m_unknown00[0x24];
	Rva0013B8F0RefCountView m_refCount24;				// +0x24
};

class Rva0013B8F0ReferenceView
{
public:
	Rva0013B8F0ReferenceView(const Rva0013B8F0ReferenceView &other)
		: m_target(other.m_target)
	{
		if (m_target)
			m_target->m_refCount24.addRef();
	}
	Rva0013B8F0ReferenceView &operator=(const Rva0013B8F0ReferenceView &other)
	{
		if (this != &other)
		{
			if (other.m_target)
				other.m_target->m_refCount24.addRef();
			if (m_target)
				m_target->m_refCount24.releaseRef();
			m_target = other.m_target;
		}
		return *this;
	}

	Rva0013B8F0TargetView *m_target;
};

struct Rva0013B8F0Element
{
	int m_word00, m_word04, m_word08;
	AsciiString m_string0C;
	Rva0013B8F0ReferenceView m_reference10;
	~Rva0013B8F0Element(); // actual thiscall body 0x0013B8F0
};

// These two retail copies are STLport destroy-range helpers over the same
// observed 20-byte record.  Their calls enter the element destructor through
// ILT 0x0002F487; the original class identity remains address-qualified.
void Rva0013C0E0Destroy(Rva0013B8F0Element *first,
	Rva0013B8F0Element *last)
{
	while (first != last)
	{
		first->~Rva0013B8F0Element();
		++first;
	}
}

void Rva0013C170Destroy(Rva0013B8F0Element *first,
	Rva0013B8F0Element *last)
{
	while (first != last)
	{
		first->~Rva0013B8F0Element();
		++first;
	}
}

// Explicit instantiation owns the vector and element operations without
// adding a synthetic caller just to make the compiler emit them.
template _STL::vector<Rva0013B8F0Element> &
_STL::vector<Rva0013B8F0Element>::operator=(
	const _STL::vector<Rva0013B8F0Element> &);
