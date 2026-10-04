// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state-action body at 0x002BC540.

typedef int Int;

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

class Rva002BC470StateAction
{
public:
	void finish(void *argument);
};

// 0x0003F42C is a 5-byte ILT thunk (?j_0003f42c@@YAXXZ); the helper pin
// ?finish@Rva002BC470StateAction@@QAEXPAX@Z is defined nowhere, so call
// through the thunk's own name.
extern void j_0003f42c();

typedef void (Rva002BC470StateAction::*Rva002BC470FinishCall)(void *);

union Rva002BC470FinishPointer
{
	void (*entry)();
	Rva002BC470FinishCall member;
};

class Rva002BC540Sink
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void beginAction() = 0;
	virtual void unused018() = 0;
	virtual void unused01c() = 0;
	virtual void signalAction(Int code) = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void dispatch(void *argument) = 0;
};

class Rva002BC540StateAction
{
public:
	void run(void *first, void *second, unsigned char third);

private:
	unsigned char m_unreconstructed000[8];
	ObjectIsMobileBody *m_object;
	unsigned char m_unreconstructed00c[0x24];
	Rva002BC540Sink *m_sink;
	unsigned char m_unreconstructed034[0x42c];
	Int m_actionStarted;
};

void Rva002BC540StateAction::run(void *first, void *second, unsigned char third)
{
	if (first && m_object->isMobile())
	{
		Rva002BC470FinishPointer finishCall;
		finishCall.entry = j_0003f42c;
		(((Rva002BC470StateAction *)this)->*finishCall.member)(second);
		m_sink->beginAction();
		m_sink->dispatch(first);
		if (third)
			m_sink->signalAction(0x3f3);
		else
			m_sink->signalAction(0x3f2);
		m_actionStarted = 1;
	}
}
