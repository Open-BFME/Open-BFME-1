// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME7: BfmeThingCB message-box configure at retail 0x00522990, 658 B.
// Stores the two ref-counted button callbacks (release old, retain new, same
// shape as Rva005225F0Destructor.cpp), releases the previous window layout,
// and stores a title/text pair via BfmePalantirYX (BfmePlayerRankYX.cpp).

class WindowLayout;
void ReleaseWindowLayout(WindowLayout *layout);

class Rva522990RefCounted
{
public:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

struct Rva522990RefPtr
{
	Rva522990RefCounted *m_ptr;

	~Rva522990RefPtr()
	{
		if (m_ptr)
		{
			if (--m_ptr->m_refs <= 0)
				m_ptr->Delete_This(1);
		}
	}
};

class StringBaseNarrowYX
{
protected:
	StringBaseNarrowYX(const char *text);

	~StringBaseNarrowYX(void);

	char *m_bfmeNarrowYX;
};

class AsciiStringYX : public StringBaseNarrowYX
{
public:
	AsciiStringYX(const char *text) : StringBaseNarrowYX(text)
	{
	}

	~AsciiStringYX(void)
	{
	}
};

class StringBaseWideYX
{
public:
	bool isEmpty(void) const
	{
		return m_bfmeWideYX == 0 || *(unsigned short *)((char *)m_bfmeWideYX + 4) == 0;
	}

	int getLength(void) const
	{
		return m_bfmeWideYX ? *(unsigned short *)((char *)m_bfmeWideYX + 4) : 0;
	}

protected:
	StringBaseWideYX(void)
	{
		m_bfmeWideYX = 0;
	}

	StringBaseWideYX(const unsigned short *text);

	~StringBaseWideYX(void);

	unsigned short *m_bfmeWideYX;
};

class UnicodeStringYX : public StringBaseWideYX
{
public:
	UnicodeStringYX(void)
	{
	}

	UnicodeStringYX(const unsigned short *text) : StringBaseWideYX(text)
	{
	}

	~UnicodeStringYX(void)
	{
	}
};

class BfmePalantirYX
{
public:
	void bfmeStoreYX(const AsciiStringYX &key, const UnicodeStringYX &value);
	char m_pad[0x1af];
};

// The one retail global at 0x012F19E8 is the window manager.  This TU only
// needs the APT store entry and the m_pad byte, so it reaches the global
// through the BfmePalantirYX view above, cast at each use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;	///< retail [0x012F19E8]

class BfmeOne924G
{
public:
	void bfmeCall924G(void);
};

class BfmeThingCB
{
public:
	char m_pad00[0x34];
	int m_34;
	int m_38;
	Rva522990RefPtr m_3c;
	Rva522990RefPtr m_40;
	int m_44;
	unsigned char m_48;
	unsigned char m_49;
};

extern void *g_rva012F49D0;					// retail 0x012F49D0

static const unsigned short s_bfmeSpaceYX[2] = { L' ', 0 };

// ?Rva00522990ConfigureMessageBox@@YAXHABVUnicodeStringYX@@0URva522990RefPtr@@1@Z
void Rva00522990ConfigureMessageBox(int newState, const UnicodeStringYX &titleText,
	const UnicodeStringYX &bodyText, Rva522990RefPtr onOk, Rva522990RefPtr onCancel)
{
	if (g_rva012F49D0 == 0)
		return;

	if (static_cast<BfmeThingCB *>(g_rva012F49D0)->m_38 != 4)
		ReleaseWindowLayout(0);

	static_cast<BfmeThingCB *>(g_rva012F49D0)->m_38 = newState;

	Rva522990RefPtr *p3c = &static_cast<BfmeThingCB *>(g_rva012F49D0)->m_3c;
	if (p3c != &onOk)
	{
		if (onOk.m_ptr)
			onOk.m_ptr->m_refs++;
		Rva522990RefCounted *old3c = p3c->m_ptr;
		if (old3c)
		{
			if (--old3c->m_refs <= 0)
				old3c->Delete_This(1);
		}
		p3c->m_ptr = onOk.m_ptr;
	}

	Rva522990RefPtr *p40 = &static_cast<BfmeThingCB *>(g_rva012F49D0)->m_40;
	if (p40 != &onCancel)
	{
		if (onCancel.m_ptr)
			onCancel.m_ptr->m_refs++;
		Rva522990RefCounted *old40 = p40->m_ptr;
		if (old40)
		{
			if (--old40->m_refs <= 0)
				old40->Delete_This(1);
		}
		p40->m_ptr = onCancel.m_ptr;
	}

	static_cast<BfmeThingCB *>(g_rva012F49D0)->m_44 = -1;

	if (titleText.isEmpty())
	{
		((BfmePalantirYX *)g_rva012F19E8WindowManager)->bfmeStoreYX(AsciiStringYX("APT:MessageBoxGenericTitle"), UnicodeStringYX(s_bfmeSpaceYX));
	}
	else
	{
		((BfmePalantirYX *)g_rva012F19E8WindowManager)->bfmeStoreYX(AsciiStringYX("APT:MessageBoxGenericTitle"), titleText);
	}

	((BfmePalantirYX *)g_rva012F19E8WindowManager)->bfmeStoreYX(AsciiStringYX("APT:MessageBoxGenericText"), bodyText);

	static_cast<BfmeThingCB *>(g_rva012F49D0)->m_34 = 2;
	static_cast<BfmeThingCB *>(g_rva012F49D0)->m_49 = 0;
	static_cast<BfmeThingCB *>(g_rva012F49D0)->m_48 = bodyText.getLength() > 0x100;

	if (g_rva012F19E8WindowManager != 0 &&
		((BfmePalantirYX *)g_rva012F19E8WindowManager)->m_pad[0x1ae] == 0)
		((BfmeOne924G *)g_rva012F49D0)->bfmeCall924G();
}
