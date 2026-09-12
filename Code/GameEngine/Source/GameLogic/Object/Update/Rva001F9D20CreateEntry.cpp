// DynamicPortalBehaviour Create-interface build-complete entry, RVA 0x001F9D20.
// Constructor installs vtable0x010A3844 at primary+0x20; slot1 selects this47B entry.
// ECX is the secondary interface pointer, so keep an RVA-qualified ABI view
// rather than claiming a primary-this decorated member name.

struct Rva001F9D20ObjectView
{
	unsigned char m_bfmeHead[0xc4];
	bool m_field0xc4;
};

extern void j_00026044(void);

class Rva001F9D20PrimaryView
{
public:
    __forceinline void run() {
        typedef void (Rva001F9D20PrimaryView::*Method)();
        union { void (*raw)(); Method member; } fn;
        fn.raw = j_00026044;
        (this->*fn.member)();
    }
	unsigned char m_bfmeHead[4];
	Rva001F9D20ObjectView *m_bfmeOwner;
	unsigned char m_bfmeGap[0x34];
	bool m_field0x3c;
};

class Rva001F9D20CreateEntry
{
public:
	virtual void invoke();
	unsigned char m_bfmePad[0x19];
	volatile bool m_field0x1d;
};

void Rva001F9D20CreateEntry::invoke()
{
	if (m_field0x1d)
	{
		m_field0x1d = false;
		Rva001F9D20PrimaryView *owner = reinterpret_cast<Rva001F9D20PrimaryView *>(
			reinterpret_cast<unsigned char *>(this) - 0x20);
		bool afterReset = *reinterpret_cast<volatile bool *>(
			reinterpret_cast<unsigned char *>(owner) + 0x3d);
		if (afterReset)
			return;
		if (owner->m_bfmeOwner->m_field0xc4 || owner->m_field0x3c)
			owner->run();
	}
}
