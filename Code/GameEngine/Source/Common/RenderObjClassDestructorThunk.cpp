// cl: /DNDEBUG /MD /EHsc

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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		if (--m_numRefs == 0) {
			Delete_This();
		}
	}

	int m_numRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/persist.h
class PersistClass
{
public:
	virtual ~PersistClass() {}

private:
	int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *m_prev;
	void *m_next;
};

class RenderObjClass : public PersistClass, public MultiListObjectClass
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
