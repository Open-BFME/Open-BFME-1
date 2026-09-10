// cl: /DNDEBUG /MD /EHsc
// ?invokeFallback@Rva00479270Delegate@@QAEEXZ
// Retail RVA 0x00479270, 22 bytes. The adjacent 0x00479250 detach body proves
// the three-word {tag, delegate, owner} layout, but no named caller or vtable
// currently proves the original class or method spelling.

class Rva00479270Target
{
public:
	virtual void slot0() = 0;
	virtual unsigned char slot1() = 0;
};

class Rva00479270Delegate
{
public:
	unsigned char invokeFallback();

private:
	int m_tag;
	Rva00479270Target *m_delegate;
	Rva00479270Target *m_owner;
};

unsigned char Rva00479270Delegate::invokeFallback()
{
	if (m_delegate != 0)
		return m_delegate->slot1();
	else
	{
		typedef unsigned char (__fastcall *Slot1)(Rva00479270Target *);
		Rva00479270Target *owner = m_owner;
		Slot1 *vtable = *(Slot1 **)owner;
		return vtable[1](owner);
	}
}
