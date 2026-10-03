// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// Two bases and one refcounted member.
//
// Both base vptrs are stored up front, the second through edi held at +8, and at
// the end the first base's own vptr is stored again by its inlined destructor --
// so the base at +8 has an out-of-line destructor and the one at 0 does not.
// Bases are destroyed in reverse declaration order, which is why the +8 one is
// called first.
//
// The member release is the guarded form with the clear inside the guard, and
// the decrement is a plain dec rather than an interlocked one. There is no null
// test before the virtual call because Delete_This is an ordinary virtual on a
// pointer already known good, not a delete expression.
// The primary base is RefCountClass: retail's final vptr store is 0x011135AC.
// Its second vtable slot routes to the deleting destructor at RVA 0x005F38E0.
// See targets/game/reverse/identity_evidence/005f38e0-refcount-destructor.md.
#include "refcount.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *m_prev;
	void *m_next;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~RenderObjClass();

private:
	unsigned char m_gap[0x88];
	RefCountClass *m_container;
};

// ??1RenderObjClass@@UAE@XZ
RenderObjClass::~RenderObjClass()
{
	if (m_container) {
		m_container->Release_Ref();
		m_container = 0;
	}
}
