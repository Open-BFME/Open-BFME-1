// ?finish@BfmeQuickMatchShutdownBody@@QAEXXZ
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: retail 0x005057C0, 90 bytes. Clears the pending-screen flag,
// virtual-calls slot +0x10 with true, tells TheShell the layout is done,
// then pushes the pending name if one was stored.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class WindowLayout;

class Shell
{
public:
	void shutdownComplete(WindowLayout *layout, bool hasPending);
	void push(AsciiString filename, bool shutdownImmediate);
};

extern char g_bfmeQuickMatchFlag;
extern const char *g_bfmeQuickMatchPending;
extern Shell * volatile TheShell;

class BfmeQuickMatchShutdownBody
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(bool);
	void finish(void);
};

struct BfmeQuickMatchVtable
{
	char m_slots[0x10];
	void (BfmeQuickMatchShutdownBody::*m_slot4)(bool);
};

void BfmeQuickMatchShutdownBody::finish(void)
{
	{
		BfmeQuickMatchVtable *vtable = *(BfmeQuickMatchVtable **)this;
		g_bfmeQuickMatchFlag = 0;
		(this->*(vtable->m_slot4))(true);
	}
	TheShell->shutdownComplete((WindowLayout *)this, g_bfmeQuickMatchPending != 0);
	if (g_bfmeQuickMatchPending)
		TheShell->push(AsciiString(g_bfmeQuickMatchPending), false);
	g_bfmeQuickMatchPending = 0;
}
