// cl: /O2 /Ob0 /EHsc

// Retail 0x006E9B70 is the complete body reached by slot 44 of the
// W3DDisplay vtable at 0x0111EDD0.  The original virtual spelling is not
// recovered, so the method remains address-derived rather than claiming a
// W3DDisplay operation name.  The body forwards the display's +0x164
// Render2DClass member to the independently matched Reset implementation.

// The BFME Render2DClass::Reset row uses the direct (nonvirtual) QAEX ABI at
// 0x00934820.  Keep this declaration local so the call emits that known
// callee without depending on the later vendored Render2D header layout.
class Render2DClass
{
public:
	void Reset(void);
};

class W3DDisplay
{
public:
	virtual void rva006E9B70(void);

private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_2DRender;
};

// ?rva006E9B70@W3DDisplay@@UAEXXZ
void W3DDisplay::rva006E9B70(void)
{
	m_2DRender->Reset();
}
